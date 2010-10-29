#define QY_MODULE     0x3
#include "QinYiCommon.h"

#define MAX_CMD_BUFF_LEN  1024

#define ANY_SIZE  1

typedef struct tag_nob //net object
{
    U16   type;   
    U16   StartTime;
    U16   Timeout;
    U16   nPort;
    int   cmdLen;
    U16 * pCmdCurPtr;
    U16 * pBufEnd;
    int  (*pFnxCmdDone)(int ret);          
    U16   CmdBuf [ANY_SIZE]; 
}NOB, * LPNOB; 

typedef void * HCMD;

 
void QyAppendCmdItem(HCMD  hcmd, U16 *strParam);
void PostToSystemNob(void * nob);
void QyAsnchTaskEntry(void);
void QyAsnchCheckEntry(void);
void ClearAsynNob(void);



int g_CmdType;


int QyAppendTime(LPNOB  pNob)
{
    if( pNob )
    {
        MYTIME syst;
        GetDateTime(&syst);
        kal_wsprintf((U16 *)pNob->pCmdCurPtr, "`%d%02d%02d%02d%02d%02d", syst.nYear, syst.nMonth, syst.nDay, syst.nHour, syst.nMin, syst.nSec); 
        pNob->pCmdCurPtr += 15;
        return 14;
    }
    return 0;
}


HCMD QyInitialComamnd(int cmd, int req, int maxlen)
{
    LPNOB  pNob = NULL;
    U16 * pCmdBuf;
    maxlen = ( maxlen ==0 )? MAX_CMD_BUFF_LEN : ( (maxlen +4 ) & (~4)); 

    pNob = (LPNOB)QyMalloc(sizeof( NOB ) + maxlen);

    if( pNob == NULL) 
        return 0;

    memset(pNob, 0, (sizeof( NOB ) + maxlen));
    
    pNob->pBufEnd = (U16 *)((U8 *)pNob->CmdBuf+maxlen);
    
    pCmdBuf = (U16 *)pNob->CmdBuf;
    kal_wsprintf(pCmdBuf+9, "%4d`%02d00", cmd, req); 
    pNob->pCmdCurPtr = pCmdBuf + 18;

    QyAppendCmdItem(pNob, g_SettingProf->user_info.name);
    QyAppendTime(pNob);

    return pNob;
}

void QyAppendItem(HCMD hcmd, U16 *strParam, U16 spit)
{
    LPNOB  pNob = (LPNOB)hcmd;
    if(pNob && pNob->pCmdCurPtr )
    {
        kal_wsprintf((U16 *)(pNob->pCmdCurPtr), "%c%w",spit, strParam); 
        pNob->pCmdCurPtr += kal_wstrlen(strParam) + 1;
    }    
}

void QyAppendCmdItem(HCMD hcmd, U16 *strParam)
{
    QyAppendItem(hcmd,strParam, L'`');
}


void QyAppendParmItem(HCMD hcmd,U16 *strParm)
{
    QyAppendItem(hcmd,strParm, L'\t');
}

void QyAppendCmdInt(HCMD hcmd,int val, U16 spit)
{
    LPNOB  pNob = (LPNOB)hcmd;
    if(pNob && pNob->pCmdCurPtr )
    {
        kal_wsprintf((U16 *)(pNob->pCmdCurPtr), "%c%08d",spit, val); 
        pNob->pCmdCurPtr = pNob->pCmdCurPtr + kal_wstrlen(pNob->pCmdCurPtr);
    }    
}

void QyAppendCmdHex(HCMD hcmd,int val, U16 spit)
{
    LPNOB  pNob = (LPNOB)hcmd;
    if(pNob && pNob->pCmdCurPtr )
    {
        kal_wsprintf((U16 *)(pNob->pCmdCurPtr), "%c%08x",spit, val); 
        pNob->pCmdCurPtr = pNob->pCmdCurPtr + kal_wstrlen(pNob->pCmdCurPtr);
    }    
}



void QyWrapPackage(HCMD hcmd)
{
    LPNOB  pNob = (LPNOB)hcmd;
    if(pNob && pNob->pCmdCurPtr )
    {
        U16 * cmdbuf = (U16 *)pNob->CmdBuf;
        int len = (pNob->pCmdCurPtr - pNob->CmdBuf + 1 - 8 )*2;
        kal_wsprintf(pNob->CmdBuf,"%08X", len);

        cmdbuf[8] = L'`';
        kal_wsprintf(pNob->pCmdCurPtr,"`\n");
        pNob->cmdLen = (pNob->pCmdCurPtr - pNob->CmdBuf + 2 )*2;
        //ASSERT( pNob->cmdLen < (pNob->pBufEnd - pNob->CmdBuf)*2)
    }         
}


int QySendPackage(HCMD hcmd, int (*f)(int ret), int bBinary )
{
    int ret = 0;
    LPNOB  pNob = (LPNOB)hcmd;
    if(pNob && pNob->pCmdCurPtr && g_SettingProf )
    {
        int port = bBinary > 0 ? g_SettingProf->Host_port + 1 : g_SettingProf->Host_port;
        pNob->nPort = port;
        pNob->pFnxCmdDone = f;
        pNob->type = g_CmdType;
        PostToSystemNob(pNob);
	}
    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////
int QyNobSendDone(int ret);
int Qy_soc_socket_notify(void *inMsg, int Msg);
int g_SocTimerRet = 0;
int mtk_soc_socket_notify(void *inMsg);
void ClearNobQueue(void * nob);
LPNOB  g_OnGoningNob;

void ResetQyProtocol()
{
    StopTimer(SOCKET_TIMEOUT_TIMER);
    soc_close(g_qy_socket_id);
    if( g_OnGoningNob ) 
    {
		ClearNobQueue(g_OnGoningNob);
        QyFree(g_OnGoningNob);
    }
    g_OnGoningNob = NULL;
    StartTimer(ASYN_TASK,10,QyAsnchTaskEntry);
}


void qy_soc_timeout(void)
{
    QyNobSendDone(g_SocTimerRet);
}

int SendNob(LPNOB pNob)
{
    int ret = 0;
    if( g_OnGoningNob )
        return -1;
    if(pNob && pNob->pCmdCurPtr && g_SettingProf )
    {
        ret = MtkSocketConnect(g_SettingProf->Host_ip, pNob->nPort, 10, Qy_soc_socket_notify); 

        //return 0 is error, 1 is OK
        if( ret  ) 
        {
            g_OnGoningNob = pNob;
        }
        else
            pNob->pFnxCmdDone(NET_ESTAB_FAIL);
	}
    return ret;
}

int QyNobSendDone(int ret)
{
	int retv = 0;
    kal_prompt_trace(MOD_MMI,"QyNobSendDone %d", ret);
    if( g_OnGoningNob && g_OnGoningNob->pFnxCmdDone)
    {
        retv = g_OnGoningNob->pFnxCmdDone(ret);
        if( ret <= NET_CLOSE )
        {
            ResetQyProtocol();
        }
    }
	return retv;
}

    
int Qy_soc_socket_notify(void *inMsg, int msg)
{
    app_soc_notify_ind_struct *soc_notify = (app_soc_notify_ind_struct*) inMsg;

	if( soc_notify ) 
		kal_prompt_trace(MOD_MMI,"Qy_soc_socket_notify %d, %d", soc_notify->event_type,msg);
	else
		kal_prompt_trace(MOD_MMI,"Qy_soc_socket_notify %d", msg);
    
    switch (msg)
    {
    case SOC_WRITE:
        //soc_send(....);
        break;
    case SOC_READ:
        kal_prompt_trace(MOD_MMI,"SOC_READ");
        if( QyNobSendDone(NET_DATA_IN) > 0 )
        {
            ResetQyProtocol();
        }
            
        g_SocTimerRet = 0;
        /*soc_recv(g_qy_socket_id, g_paBuffer, 256, 0);
        mmi_scan_display_popup((UI_string_type) g_paBuffer, MMI_EVENT_INFO);*/
        break;
    case SOC_CONNECT:
        kal_prompt_trace(MOD_MMI,"SOC_CONNECT %d", soc_notify->result);
        if( g_OnGoningNob && g_OnGoningNob->CmdBuf )
        {
            soc_send(g_qy_socket_id,g_OnGoningNob->CmdBuf,g_OnGoningNob->cmdLen, 0);
            g_SocTimerRet = NET_DATA_TIMOUT;
            StartTimer(SOCKET_TIMEOUT_TIMER,6000,qy_soc_timeout);
        }
        else
        {
            //QyNobSendDone(1);
        }
        
        break;
    case SOC_CLOSE:
        kal_prompt_trace(MOD_MMI,"SOC_CLOSE %d", g_qy_socket_id);
        soc_close(g_qy_socket_id);
        StopTimer(SOCKET_TIMEOUT_TIMER);
        g_SocTimerRet = 0;
        QyNobSendDone(NET_CLOSE);
        break;
	case SOC_WOULDBLOCK|SOC_EXT_MSG:
        g_SocTimerRet = NET_DATA_TIMOUT;
		StartTimer(SOCKET_TIMEOUT_TIMER,3*60000,qy_soc_timeout);
		break;

    }
    return 0;
}

#ifndef MMI_ON_HARDWARE_P
extern void soc_init_win32(void);
#endif

int QySocketConnect( U8 * pIp, int port, int(*fnxCb)(void*))
{
    kal_uint8 val = 1;
    kal_int32 nwt_acount_id;
    kal_int8 ret;
    kal_uint8 *addr ;
    // kal_uint8 addr[4] = {10, 0, 0, 172};
    sockaddr_struct server_ip_addr;

    nwt_acount_id = 10;//
    if( pIp == NULL )
        return ERR_INVLD_PARMA;
    
    addr = pIp;// {218,246,21,43};//{125, 91, 4, 144};//{202,108,33,60};//  //202.108.33.60 //
    
    /*初始化Soc*/
#ifndef MMI_ON_HARDWARE_P
    soc_init_win32();
#endif 
    
    kal_prompt_trace(MOD_MMI,"QySocketConnect (accound id = %d)...",nwt_acount_id);
    /* 创建Socket */
    g_qy_socket_id = soc_create(SOC_PF_INET, SOC_SOCK_STREAM, 0, MOD_MMI, nwt_acount_id);
    if (g_qy_socket_id >= 0)
    {
        int ret;
        kal_prompt_trace(MOD_MMI,"soc_create ok!!");
        val = 1;
        ret = soc_setsockopt(g_qy_socket_id, SOC_NBIO, &val, sizeof(val));
        if ( ret < 0)
        {
            kal_prompt_trace(MOD_MMI,"Set socket to nonblock mode1 error %d!!", ret);
            return 0;
        }
        
        val = SOC_READ | SOC_WRITE | SOC_CLOSE | SOC_CONNECT;
        if (soc_setsockopt(g_qy_socket_id, SOC_ASYNC, &val, sizeof(val)) < 0)
        {
            kal_prompt_trace(MOD_MMI, "Set socket to nonblock mode2 error !!");
            return 0;
        }
    }  
    else
    {
        kal_prompt_trace(MOD_MMI,"Create socket error %d!!", g_qy_socket_id);
    }
    
    /*连接Socket*/
    server_ip_addr.sock_type = SOC_SOCK_STREAM;
    server_ip_addr.addr_len = 4;
    server_ip_addr.port = port;
    memcpy(server_ip_addr.addr, addr, 4);
    ret = soc_connect(g_qy_socket_id, &server_ip_addr);
    kal_prompt_trace(MOD_MMI,"soc_connect %d (%d.%d.%d.%d:%d)", ret,addr[0],addr[1],addr[2],addr[3],server_ip_addr.port);
   
    if (ret == SOC_SUCCESS)
    {    
        kal_prompt_trace(MOD_MMI,"soc_connect success start sent!!");
        StartTimer(SOCKET_TIMEOUT_TIMER,150000,qy_soc_timeout);
    }
    else if (ret == SOC_WOULDBLOCK)
    {
        kal_prompt_trace(MOD_MMI,"soc_connect success with SOC_WOULDBLOCK!!");
        SetProtocolEventHandler(fnxCb, RES_SOC_MSG(MSG_ID_APP_SOC_NOTIFY_IND));
        StartTimer(SOCKET_TIMEOUT_TIMER,150000,qy_soc_timeout);
        kal_prompt_trace(MOD_MMI,"Set Protocl message handle %d!!",RES_SOC_MSG(MSG_ID_APP_SOC_NOTIFY_IND));
    }
    else
    {
        kal_prompt_trace(MOD_MMI,"soc_connect failure [error =%d]!!!", ret);
        soc_close(g_qy_socket_id);
        return 0;
    }

    kal_prompt_trace(MOD_MMI,"fly till timer coming", ret);
    
    return 1 ;
    
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
    
int QyGetAckLen(void)
{
    int len = 0;
    U16 buff[8];
    if( soc_recv(g_qy_socket_id, buff, 16, 0) )
    {
        mmi_ucs2tox((S8*)buff, &len,NULL);    
    }
    return len;
}

int QyGetAckData(void * buff,  int len)
{
    return soc_recv(g_qy_socket_id, buff, len, 0);
}

U16 * GetNextField(U16 * buff, int len)
{
    U16 * ptr = (U16 *)buff;
    if( buff == NULL) return NULL;  
    
    while(*ptr )
    {
		if( *ptr == L'\n' ) 
			return NULL;
        ptr++;
    }
    return ++ptr;
}

U16 * GetFeild(void * buff, int len, int idx)
{
    int i;
    U16 * ptr = (U16 *)buff;
    if( buff == NULL) return NULL;

    for(i=0 ; i<idx; i++)
    {
        ptr = GetNextField(ptr, 0);
        if( ptr == NULL)
            break;
    }
    return ptr;
    
}

U32 GetFieldInt(void * buff, S32 len, S32 idx, U32 * ret)
{
    U16 * pver = GetFeild(buff, 0, idx) ;
    if( pver )
        return mmi_ucs2toi((S8*)pver,(S32*)ret,NULL);
    return 0;    
}

U32 GetFieldIntx(void * buff, S32 len, S32 idx, U32 * ret)
{
    U16 * pver = GetFeild(buff, 0, idx) ;
    if( pver )
        return mmi_ucs2tox((S8*)pver,(S32*)ret,NULL);
    return 0;    
}

//TODO:
int ParseAckCode(void * buff, int len)
{
    GetFeild( buff,  len, 1);
    return 1;
}

int ParseAckPackage(int * pcmd, int * perr, U16 * pack, int len)
{
    int fields = 1;
    U16 * ptr_cmd = pack, * ptr_err = NULL;
	pack[len] = 0;

    
    while( *pack && (*pack != L'\n'))
    {
        if( *pack == L'`' || *pack == L'\t')
        {
            *pack = L'\0';
            fields++;
            if( pack[1] !=L'\n' )
                ptr_err = pack+1;
        }
        pack++;
    }

    if( pcmd ) 
    {
        if( ptr_cmd  )
            mmi_ucs2toi((S8*)ptr_cmd,pcmd, NULL);
        else
            *pcmd = 0;
    }
    if( perr  )
    {
        if( ptr_err )
            mmi_ucs2tox((S8*)ptr_err,perr, NULL);
        else 
            *perr = 0xCC;
    }
    return fields;
    
}

void * GetAckHandleEx( NOB_ACK * pack_info)
{
    pack_info->pbuf = GetAckHandle(  &pack_info->cmd, &pack_info->err, &pack_info->field,
                          &pack_info->buflen);
    return pack_info->pbuf ;
}
    

void * GetAckHandle( int * pcmd,int * perr, int * pFieldTotal, int * buflen)
{
    U16 * pack = NULL;
    int totals;
    int len = QyGetAckLen() + 8;
    if( len > 0 &&  len < 64*1024)
    {
        pack = QyMalloc(len);

        if( pack )
        {
            memset( pack, 0 , len );
            QyGetAckData(pack, len-4);

            totals = ParseAckPackage(pcmd, perr, pack+1, len );

            if( pFieldTotal)
                *pFieldTotal = totals;
        }
    }
    if( buflen ) *buflen = len;
    return pack;
}

#ifndef offsetof
#define offsetof(type, mem) ((size_t) ((char*)&((type*)0)->mem - (char*)((type*)0)))
#endif

int g_tm_offset[][2] = 
{
   {4,  offsetof(MYTIME, nYear) }
  ,{2,  offsetof(MYTIME, nMonth)}
  ,{2,  offsetof(MYTIME, nDay)  }
  ,{2,  offsetof(MYTIME, nHour) }
  ,{2,  offsetof(MYTIME, nMin)  }
  ,{2,  offsetof(MYTIME, nSec)  }
};
    
int GetAckTime(void *hack, MYTIME * tmack)
{
    S32 val, rd, i;
    U16 tmp ;
    U16 * ptm = GetFeild(hack, 0, 2);
    for( i=0 ;i<sizeof(g_tm_offset)/(sizeof(int)*2);i++)
    {
        int endp = g_tm_offset[i][0];
        tmp = ptm[endp];
        ptm[endp] = 0;
        mmi_ucs2toi((S8 *)ptm, &val, &rd);
        if( endp == 4 )
            *(S16 *)((U32)tmack + g_tm_offset[i][1] )= (S16)val;
        else if( endp == 2 )
            *(U8 *) ((U32)tmack + g_tm_offset[i][1] )= (U8)val;            
        ptm[endp] = tmp;
        ptm += endp;
    }
    return 0;
}

void FreeAckHandle(void * packHandle)
{
    if( packHandle )
        QyFree(packHandle);
}

typedef struct tag_qy_error_code_lookup
{
    int err;
    U8  pscipt[24];
}QY_ERR_LOOK_UP;


QY_ERR_LOOK_UP g_QyErrStringTble[] = 
{
    {0xFF, ("\x2A\x67\xE5\x77\x19\x95\xEF\x8B\x0\x0") /*L"未知错误"*/},
    {0x00, ("\x10\x62\x9F\x52\x0\x0") /*L"成功"*/},
    {0x01, ("\xE5\x67\xE2\x8B\xD4\x8F\xDE\x56\x7A\x7A\x0\x0") /*L"查询返回空"*/},
    {0xCC, ("\x1A\x90\xAF\x8B\x31\x59\x25\x8D\x0\x0") /*L"通讯失败"*/},
    {0xE0, ("\xD0\x8F\x55\x53\xF7\x53\x3A\x4E\x7A\x7A\x0\x0") /*L"运单号为空"*/},
    {0xFE, ("\x85\x8D\xF6\x65\x0\x0") /*L"超时"*/},
    {0xFB, ("\x28\x75\x37\x62\xD\x54\x16\x62\xC6\x5B\x1\x78\x19\x95\x0\x0") /*L"用户名或密码错"*/},
    {0xFC, ("\x28\x75\x37\x62\xD\x54\x16\x62\xC6\x5B\x1\x78\x19\x95\x0\x0") /*L"用户名或密码错"*/},
};


U16 * QureyErrorString(int errcode)
{
    int i;
    for(i=0; i<sizeof(g_QyErrStringTble)/sizeof(QY_ERR_LOOK_UP);i++)
    {
        if( g_QyErrStringTble[i].err == errcode )
            return (U16 *)g_QyErrStringTble[i].pscipt;
    }
    return (U16 *)g_QyErrStringTble[0].pscipt;
    
}

//U16 qy_str_login[] =  {L"00000062`1000`0100`01291.001`20100914055503`01291.001\t01`\n"};
int QySendLoginCmd(U16 * user , U16 * pwd, int (*f)(int ret))
{
    HCMD hcmd;
    if( (hcmd = QyInitialComamnd(CMD_LOGIN,CMD_LOGIN_REQ,0)) != NULL )
    {
        U16 ver[8];
        QyAppendCmdItem(hcmd, user);
        QyAppendParmItem(hcmd, pwd);
        kal_wsprintf(ver,"%000d",QY_APPLICATION_VERSION);
        QyAppendParmItem(hcmd, ver);
        QyWrapPackage(hcmd);
        QySendPackage(hcmd, f, 0);
        return 1;
    }
    return 0;
}


int QyPrepareSignRecptCmd(U16 * SignName, int totals,QY_RDID * pIds, FuncCmdAck f)
{
    int i;
    HCMD hcmd =  QyInitialComamnd(CMD_SIGN_RECTP,CMD_SRECTP_REQ,(totals*MAX_RDID_LEN+64+QY_USER_MAX_LEN)*2) ;
    if(hcmd)
    {
        U16 Strrdid[MAX_RDID_LEN+2];
        QyAppendCmdItem(hcmd, SignName);
        QyAppendCmdHex(hcmd, totals, L'\t');
        for( i=0; i<totals; i++)
        {
            mmi_asc_n_to_wcs(Strrdid, (S8*)pIds[i].Rdid, MAX_RDID_LEN+1),
            QyAppendParmItem(hcmd, Strrdid);
        }
        QyWrapPackage(hcmd );
        QySendPackage(hcmd, f, 0);
        return 1;
    }
    return 0;

}

//1004`0100`业务员编号`Date&Time
//问题件类型编号\t
//运单总数\t
//运单号\t
//问题件原因说明
//:1004`0100`01291.001`20100925043929`问题件类型  运单总数  问题件单号1  问题件原因  问题件运单号n  空`
#if 0
/*中通
  14	电话无人接听           1. 电话无人接听
    3	查无此人               2. 查无此人
    1	地址不详               3. 地址不详
    5	拒付到付款             4. 拒付到付款
    12	拒付代收货款           5. 拒付代收货款
    6	客户拒收               6. 客户拒收
    7	破损件                 7. 破损件
    15	客户要求重新派送       8. 客户要求重新派送
    17	家中无人               9. 家中无人
    16	其他                   10.其他*/

U8 g_ProblemTextList[] = {
"\x31\x0\x2E\x0\x35\x75\xDD\x8B\xE0\x65\xBA\x4E\xA5\x63\x2C\x54\x0\x0" /*L"1.电话无人接听"*/
"\x32\x0\x2E\x0\xE5\x67\xE0\x65\x64\x6B\xBA\x4E\x0\x0" /*L"2.查无此人"*/
"\x33\x0\x2E\x0\x30\x57\x40\x57\xD\x4E\xE6\x8B\x0\x0" /*L"3.地址不详"*/
"\x34\x0\x2E\x0\xD2\x62\xDD\x7E\x30\x52\xD8\x4E\x3E\x6B\x0\x0" /*L"4.拒绝到付款"*/
"\x35\x0\x2E\x0\xD2\x62\xDD\x7E\xE3\x4E\x36\x65\x27\x8D\x3E\x6B\x0\x0" /*L"5.拒绝代收货款"*/
"\x36\x0\x2E\x0\xA2\x5B\x37\x62\xD2\x62\x36\x65\x0\x0" /*L"6.客户拒收"*/
"\x37\x0\x2E\x0\x34\x78\x5F\x63\xF6\x4E\x0\x0" /*L"7.破损件"*/
"\x38\x0\x2E\x0\xA2\x5B\x37\x62\x81\x89\x42\x6C\xCD\x91\xB0\x65\x3E\x6D\xD1\x53\x0\x0" /*L"8.客户要求重新派发"*/
"\x39\x0\x2E\x0\xB6\x5B\x2D\x4E\xE0\x65\xBA\x4E\x0\x0" /*L"9.家中无人"*/
"\x31\x0\x30\x0\x76\x51\xD6\x4E\x0\x0" /*L"10其他"*/
"\0\0\0\0"
};
const int g_problem_map[]= {16,14,3, 1, 5, 12, 6, 7, 15, 17, 16,11};

#else
/*
18	部分快件签收    1.  ---------------终端顺序
3	查无此人	    2.
13	超区            3.
4	错发件          4.
1	地址不详	    5.
10	电话错误        6.
11	家中无人        7.
9	节假日休息      8.
5	拒付到付款      9.
2	客户电话无人接  10.
6	客户拒收        11.
16	客户无证件      12.
8	客户要求改地址  13.
15	客户要求改日送  14.
7	破损件          15.
17	退件            16.
12	其他            17.
*/
U8 g_ProblemTextList[] = 
{
"\x31\x0\x2E\x0\xE8\x90\x6\x52\xEB\x5F\xF6\x4E\x7E\x7B\x36\x65\x0\x0"  /*L"1.部分快件签收"*/
"\x32\x0\x2E\x0\xE5\x67\xE0\x65\x64\x6B\xBA\x4E\x0\x0"  /*L"2.查无此人"*/
"\x33\x0\x2E\x0\x85\x8D\x3A\x53\x0\x0"  /*L"3.超区"*/
"\x34\x0\x2E\x0\x19\x95\xD1\x53\xF6\x4E\x0\x0" /*L"4.错发件"*/ 
"\x35\x0\x2E\x0\x30\x57\x40\x57\xD\x4E\xE6\x8B\x0\x0" /*L"5.地址不详"*/    
"\x36\x0\x2E\x0\x35\x75\xDD\x8B\x19\x95\xEF\x8B\x0\x0" /*L"6.电话错误"*/
"\x37\x0\x2E\x0\xB6\x5B\x2D\x4E\xE0\x65\xBA\x4E\x0\x0" /*L"7.家中无人"*/
"\x38\x0\x2E\x0\x82\x82\x47\x50\xE5\x65\x11\x4F\x6F\x60\x0\x0" /*L"8.节假日休息"*/
"\x39\x0\x2E\x0\xD2\x62\xD8\x4E\x30\x52\xD8\x4E\x3E\x6B\x0\x0" /*L"9.拒付到付款"*/
"\x31\x0\x30\x0\x2E\x0\xA2\x5B\x37\x62\x35\x75\xDD\x8B\xE0\x65\xBA\x4E\xA5\x63\x0\x0" /*L"10.客户电话无人接"*/
"\x31\x0\x31\x0\x2E\x0\xA2\x5B\x37\x62\xD2\x62\x36\x65\x0\x0" /*L"11.客户拒收"*/
"\x31\x0\x32\x0\x2E\x0\xA2\x5B\x37\x62\xE0\x65\xC1\x8B\xF6\x4E\x0\x0" /*L"12.客户无证件"*/
"\x31\x0\x33\x0\x2E\x0\xA2\x5B\x37\x62\x81\x89\x42\x6C\x39\x65\x30\x57\x40\x57\x0\x0" /*L"13.客户要求改地址"*/
"\x31\x0\x34\x0\x2E\x0\xA2\x5B\x37\x62\x81\x89\x42\x6C\x39\x65\xE5\x65\x1\x90\x0\x0" /*L"14.客户要求改日送"*/
"\x31\x0\x35\x0\x2E\x0\x34\x78\x5F\x63\xF6\x4E\x0\x0" /*L"15.破损件"*/
"\x31\x0\x36\x0\x2E\x0\x0\x90\xF6\x4E\x0\x0" /*L"16.退件"*/
"\x31\x0\x37\x0\x2E\x0\x76\x51\xD6\x4E\x0\x0" /*L"17.其他"*/
"\0\0\0\0"
};

const int g_problem_map[]= {12,18,3,13,4,1,10,11,9,5,2,6,16,8,15,7,17,12};
#endif 

U8 * GetProblemTextByIndex(int index)
{
    U16 * pstr = (U16 *)g_ProblemTextList;
    while(index--)
    {
        int slen = kal_wstrlen(pstr);
        if( slen == 0 )
            return NULL;
        
        pstr += slen + 1;
        if( * pstr == 0 )
            return NULL;
    }
    return (U8*)pstr;
}

int QyPrepareIssueCmd(PROBLEM_JOUNOR * pProblemJouner, int totals,QY_RDID * pIds, FuncCmdAck f)
{
    HCMD hcmd;
    int i = kal_wstrlen(pProblemJouner->strOther);
    U16 Strrdid[MAX_RDID_LEN+2];
    U16 strProblemID[4];
    int idx;
    mmi_ucs2toi((S8*)pProblemJouner->ProblemID, &idx,NULL);
    if( idx < 0 && idx >= sizeof(g_problem_map)/sizeof(int))
        return 0; 
    
    kal_wsprintf(strProblemID,"%d",g_problem_map[idx] );

    hcmd =  QyInitialComamnd(CMD_PROBLEM, CMD_SRECTP_REQ,(totals*MAX_RDID_LEN+64+QY_USER_MAX_LEN)*2+(i*2+16));
    
    if( hcmd )
    {
        
        //QyAppendCmdInt(totals, L'\t');//运单总数 
        for( i=0; i<totals; i++)
        {
            mmi_asc_n_to_wcs(Strrdid, (S8*)pIds[i].Rdid, MAX_RDID_LEN+1);
            if( i == 0 )
            {
                QyAppendCmdItem(hcmd, Strrdid);
                QyAppendParmItem(hcmd, strProblemID);//问题件类型
            }
            else
            {
                QyAppendParmItem(hcmd, Strrdid);
                QyAppendParmItem(hcmd, L" ");
            }
        }
            
        if(pProblemJouner->strOther[0] )
            QyAppendParmItem(hcmd, pProblemJouner->strOther);
        else
            QyAppendParmItem(hcmd, L" ");
        QyWrapPackage(hcmd); 
        QySendPackage(hcmd, f, 0);
        return 1;
    }
    return 0;

}

const int jun_size[] = {0, sizeof(RECIVE_JUNOR), sizeof(SIGN_JUNOR), sizeof(PROBLEM_JOUNOR)};
TASK_HEADER * CreateTask(QYFILE_TYPE ftype, int nInitalIdMax)
{
    TASK_HEADER * pNewTask = NULL;
    if( (ftype &= QYF_FILE_MASK) < QYF_MAX_TYPE )
    {
        if(nInitalIdMax == 0 ) nInitalIdMax = DEF_ID_MAX_BUFF;
        
        pNewTask = (TASK_HEADER *)QyMalloc(sizeof(TASK_HEADER) ); 
        memset( pNewTask, 0 , sizeof(TASK_HEADER));
        if( pNewTask )
        {
            QY_RDID* pIds= (QY_RDID*)QyMalloc(sizeof(QY_RDID)*nInitalIdMax);
            if( pIds )
            {
                pNewTask->pJunor = QyMalloc(jun_size[ftype]);
                if( pNewTask->pJunor )
                {
                    memset(pIds, 0 , sizeof(QY_RDID)*nInitalIdMax);    
                    memset( pNewTask->pJunor, 0 ,  jun_size[ftype]); 
                    GetDateTime(&pNewTask->GenTime);
                    pNewTask->MaxItms = nInitalIdMax;
                    pNewTask->totals = 0;
                    pNewTask->LenJunor = jun_size[ftype] ;
                    pNewTask->filetype = ftype;
                    pNewTask->pRdId = pIds;
                }
            } 
        }
        if(pNewTask == NULL || pNewTask->pJunor == NULL)
        {
            FreeTask(pNewTask);
            pNewTask = NULL;
        }
    }
    return pNewTask;
}

extern S8 StrnCmp(S8 *s1, S8 *s2, int maxlen);
int  SetTaskJunor(TASK_HEADER * ptask, void * pJunor, int len_junor)
{
    if( ptask == NULL ) return 0;
    if( ptask->pJunor == pJunor ) return len_junor;

    memcpy( ptask->pJunor, pJunor, len_junor);
    return len_junor;
}

void * GetTaskJunor(TASK_HEADER * ptask)
{
    return ptask->pJunor;
}

static int LocationRdid(TASK_HEADER * pNewTask, TYPE_RDID * ptarid)
{
    int i;
    QY_RDID* pIds = pNewTask->pRdId;
    for(i = 0 ;i<pNewTask->totals; i++)
    {
        if( StrnCmp((S8*)ptarid, (S8*)pIds[i].Rdid, MAX_RDID_LEN) == 0 )
            return i;
    }
    return ERR_NOT_FONTD;
}

int ReallocRdidBuff(TASK_HEADER * pNewTask)
{
    QY_RDID* pIds;
    int origMax = pNewTask->MaxItms;
    pIds= (QY_RDID*)QyMalloc(sizeof(QY_RDID)*(origMax*2));
    if( pIds )
    {
        memcpy(pIds, pNewTask->pRdId, sizeof(QY_RDID)*pNewTask->totals);
        QyFree(pNewTask->pRdId );
        pNewTask->MaxItms = origMax*2;
        pNewTask->pRdId = pIds;
        return QY_SUCCESS;
    }
    return ERR_NOMORE_MEMORY;
}

int  AppendRdId(TASK_HEADER * ptask, U16 * pstrRdid)
{
    QY_RDID  RDID;
    if( ptask == NULL) return ERR_INVLD_PARMA;

    memset(RDID.Rdid, 0, sizeof(QY_RDID));
    mmi_wcs_n_to_asc((S8 *)RDID.Rdid, (U16*)pstrRdid, MAX_RDID_LEN*sizeof(U16)); //mmi_ucs2_n_to_asc

    if( LocationRdid(ptask, RDID.Rdid) >= 0 )
        return ERR_RDID_REPEAT;

    if( ptask->totals + 1 >= ptask->MaxItms  )
    {
        if( ReallocRdidBuff(ptask) != QY_SUCCESS )
            return ERR_NOMORE_MEMORY;
    }
    memcpy(&ptask->pRdId[ptask->totals] , RDID.Rdid, sizeof(QY_RDID));
    ptask->totals ++;
    return ptask->totals;
}

int  RemoveRdId(TASK_HEADER * ptask, U16 * pstrRdid)
{
    QY_RDID  RDID;
    int location = ERR_NOT_FONTD;
    if( ptask == NULL) return ERR_INVLD_PARMA;

    memset(&RDID, 0, sizeof(QY_RDID));
    mmi_wcs_n_to_asc((S8*)RDID.Rdid, (U16*)pstrRdid, MAX_RDID_LEN*sizeof(U16));

    
    location = LocationRdid(ptask, RDID.Rdid);

    if( location < 0 )  return ERR_NOT_FONTD;

    ptask->totals--;
    memcpy(&ptask->pRdId[location], &ptask->pRdId[ptask->totals],sizeof(QY_RDID));
    memset(&ptask->pRdId[ptask->totals],  0  , sizeof(QY_RDID));
    return QY_SUCCESS;
}

U16   g_SysFileName[][9] ={
    {L"QyRecept"},
    {L"QySign"},
    {L"QyIssue"}
};


U16 * GetQyFileName(QYFILE_TYPE ftype)
{
    int ft = (ftype & QYF_FILE_MASK);
    if(ft ==0 || ft >= QYF_MAX_TYPE ) return NULL;
    return g_SysFileName[ft-1];
}

static int FindQyTaskFile(QYFILE_TYPE ftype,  int bsave)
{
    U16 fname[64];
    U16 szSearch[64];                 //FS_Pattern_Struct list_file[1];
    int mode = bsave ? FS_READ_WRITE : FS_READ_ONLY;
    
    FS_HANDLE fs_h = -1;

    OpenQyDir(QY_USER);
    kal_wsprintf(szSearch, "%w_A.dat",GetQyFileName(ftype));   
    fs_h = OpenQyFile(QY_USER, szSearch, mode);

    if( fs_h >= FS_NO_ERROR )
    {
        UINT size ;
        FS_GetFileSize(fs_h,&size);
        if( size == 0 || size >= MAX_PER_FILE_SIZE )
        {
            int tmp_fh, index;
            FS_Close(fs_h);
            for( index =(int)'B'; index <(int)'Z'; index++)
            {
                kal_wsprintf(fname, "%w_%c.dat",GetQyFileName(ftype),index);
                tmp_fh = OpenQyFile(QY_USER, fname, FS_READ_ONLY);
                if( tmp_fh < 0 )
                    break;
                FS_Close(tmp_fh);
            }
            if( index == (int)'Z')
                return FS_NO_MORE_FILES;
			kal_wsprintf(szSearch, "%w\\%w_A.dat",GetQyDirName(QY_USER),GetQyFileName(ftype));
			kal_wsprintf(fname, "%w\\%w_%c.dat",GetQyDirName(QY_USER),GetQyFileName(ftype),index);
            FS_Rename(szSearch, fname);
            fs_h = FS_NO_MORE_FILES;
        }        
    }

    if( fs_h < 0 && bsave )
    {
		kal_wsprintf(fname, "%w_A.dat",GetQyFileName(ftype));
        mode |= FS_CREATE_ALWAYS ;
        fs_h = OpenQyFile(QY_USER, fname, mode);
    }

    return fs_h;

}


int  SaveTask(TASK_HEADER * ptask)
{
    int ret = ERR_FILE_NOT_OPEN;
    int fs_h  ;
    if( ptask == NULL ) return ERR_INVLD_PARMA;
    fs_h = FindQyTaskFile(ptask->filetype, 1);
    if( fs_h > 0  )
    {
        U32 wdb = 0;
        UINT fsStartPos = FS_Seek(fs_h, 0, FS_FILE_END);
        
        ptask->tsksize = sizeof(TASK_HEADER)+ptask->LenJunor+sizeof(QY_RDID)*ptask->totals-8;
        mmi_asc_n_to_wcs(ptask->taskname, (S8*)ptask->pRdId[0].Rdid, MAX_RDID_LEN+1);//mmi_asc_n_to_ucs2

        ret = ERR_FILE_WRITING;
        FS_Write(fs_h, ptask, sizeof(TASK_HEADER)-8, &wdb);    // sub 8 means not store pointers
        if( wdb != sizeof(TASK_HEADER)-8 ) goto endf;
        
        FS_Write(fs_h, ptask->pJunor, ptask->LenJunor, &wdb);
        if( wdb != ptask->LenJunor ) goto endf;
        
        FS_Write(fs_h, ptask->pRdId,  sizeof(QY_RDID)*ptask->totals, &wdb);     
        if( wdb != sizeof(QY_RDID)*ptask->totals ) goto endf;
        
        FS_Commit(fs_h);
        ret =  QY_SUCCESS;
endf:
        if( ret != QY_SUCCESS )
        {
            U32 FailLenth;
            U16 WrongFlag = QYF_SENT|QYF_UNKOWN;
            FailLenth = FS_Seek(fs_h, 0, FS_FILE_END);
            FailLenth -= fsStartPos;
            if( FailLenth )
            {
                FS_Seek(fs_h, fsStartPos, FS_FILE_BEGIN);
                FS_Write(fs_h, &FailLenth, sizeof(U32), &wdb);              
                FS_Write(fs_h, &WrongFlag, sizeof(U32), &wdb);   
            }

        }
        FS_Close(fs_h);   
    }      
    return ret;
}


QY_ALL_TASKINFO * g_TaskDump;

int OpenTasksFile(int ftype, int index, int mode)
{
    int fsh;
    int findex = g_TaskDump->findex[index];
    U16 fname[64];

    kal_wsprintf(fname,"%w_%c.dat" ,GetQyFileName(ftype),findex);
    fsh  = OpenQyFile(QY_USER, fname,mode);
    return fsh;    
}

int DeleleTask(int ftype, int index)
{
    int fsh;
    if(index<0 || g_TaskDump == NULL || g_TaskDump->Totls < index) return ERR_INVLD_PARMA;
    fsh  = OpenTasksFile( ftype,  index, FS_READ_WRITE);
    if( fsh > 0 )
    {
        UINT rd ;
        U16 flag;
        U32 offset = g_TaskDump->offset[index];
        flag = QYF_SENT | ftype;
        FS_Seek(fsh, offset+4, FS_FILE_BEGIN);
        FS_Write(fsh, &flag, 2 ,&rd);
        FS_Close(fsh);

        if(rd == 2 )
        {
            if( index != g_TaskDump->Totls )
            {
                int nleft = g_TaskDump->Totls-index-1; 
                memmove(&g_TaskDump->TitlePtr[index],&g_TaskDump->TitlePtr[index+1], nleft * sizeof(U8 *));
                memmove(&g_TaskDump->findex[index],  &g_TaskDump->findex[index+1],   nleft * sizeof(U8));
                memmove(&g_TaskDump->offset[index],  &g_TaskDump->offset[index+1],   nleft * sizeof(U32));                            
            }
            g_TaskDump->Totls--;

        }
        return (rd==2) ? QY_SUCCESS  : ERR_FILE_NOT_OPEN;        
    }    
    return ERR_FILE_NOT_OPEN;
}

TASK_HEADER *  LoadTask(int ftype, int index)
{
    TASK_HEADER * ptask = NULL;
    if(index >=0 && g_TaskDump && g_TaskDump->Totls > index)
    {
        int fsh  = OpenTasksFile( ftype,  index, FS_READ_ONLY);
        if( fsh > 0 )
        {
            UINT rd;
            U32 offset = g_TaskDump->offset[index];
            FS_Seek(fsh, offset, FS_FILE_BEGIN);
            FS_Read(fsh, &offset, 4, &rd);
            if( rd == 4)
            {
                ptask = CreateTask(ftype, (offset)/sizeof(QY_RDID));
                FS_Read(fsh, &ptask->filetype, (sizeof(TASK_HEADER)-4-8), &rd);  // sub 8 means not store pointers. 4 is read task size already
                if( rd < (sizeof(TASK_HEADER)-4-8)) 
                {
                    FreeTask(ptask);
                    return NULL;
                }
                FS_Read(fsh, ptask->pJunor,ptask->LenJunor, &rd );
                FS_Read(fsh, ptask->pRdId, ptask->totals*sizeof(QY_RDID), &rd);
            }
            FS_Close(fsh);
        }
    }
    return ptask;
}

void FreeTask(TASK_HEADER * ptask)
{
    if( ptask )
    {
        if( ptask->pRdId) QyFree(ptask->pRdId);
        if( ptask->pJunor) QyFree(ptask->pJunor);
        QyFree(ptask);
    }
}

int  SendTask(TASK_HEADER * ptask, int bpromopt, FuncCmdAck f)
{
    if( ptask == NULL ) return ERR_INVLD_PARMA;
    switch( ptask->filetype )
    {
    case QYF_SIGN:
        return QyPrepareSignRecptCmd(ptask->pJunor, ptask->totals, ptask->pRdId, f);
        break;
    case QYF_PROBLEM:
        return QyPrepareIssueCmd(ptask->pJunor, ptask->totals, ptask->pRdId, f);
    }
    ClearAsynNob();
    return 0;
} 




#define HEADER_SIZE    (sizeof(U32)+sizeof(U16))
typedef struct headif
{
    U32    tsksize;
    U16    filetype;
}QYF_NODE;

void ReStartQyAsySendThread(void);

TASK_HEADER * g_pAsynTask; 
U32 g_pAsynTaskOffset;
U16 g_pAsynTaskExtChar;



int DumpTaskFile(int fsh, int index)
{
     UINT pos = 0 , len,  nvalidf = 0;
     QYF_NODE head;

     U8 * ptr = (U8*)&g_TaskDump->TitleBuff[g_TaskDump->Totls*(MAX_RDID_LEN+1)];
     UINT rd = 0;
     do{
         FS_Read(fsh, &head, HEADER_SIZE,&rd);
         if( rd < HEADER_SIZE ) break;

         len = head.tsksize;

         if( !(head.filetype & QYF_SENT) ) //Not sent yet
         {         
             FS_Read(fsh, ptr, (MAX_RDID_LEN+1)*2,&rd);
             if( rd <  MAX_RDID_LEN*2) break;

             g_TaskDump->TitlePtr[g_TaskDump->Totls] = ptr;
             g_TaskDump->findex[g_TaskDump->Totls] = index;
             g_TaskDump->offset[g_TaskDump->Totls] = pos;
             g_TaskDump->Totls++;

             ptr += (MAX_RDID_LEN+1)*sizeof(U16);
             len -= rd;
             nvalidf++;
         }
         FS_Seek(fsh,  len - HEADER_SIZE ,  FS_FILE_CURRENT);
         pos += head.tsksize;
     }while(1);
     return nvalidf;
}

int DumpTaskByFtype(QYFILE_TYPE ftype)
{
    int index , fsh, ret = 0;
    U16 fname[32];    

    g_TaskDump = QyMalloc(sizeof(QY_ALL_TASKINFO));
    if( g_TaskDump== NULL ) return ERR_NOMORE_MEMORY;
 
    
    g_TaskDump->Totls = 0;    
    for( index = (int)'A'; index<(int)'Z';index++)
    {
        kal_wsprintf(fname, "%w_%c.dat",GetQyFileName(ftype),index);
        fsh = OpenQyFile(QY_USER, fname, FS_READ_ONLY);
        if( fsh > 0 )
        {
            ret = DumpTaskFile(fsh, index); 
             if( ret <= 0)
             {
                FS_Close(fsh);
                DeleteQyFile(QY_USER, fname);
                break;
             }
        }
        FS_Close(fsh);
    }

    return ret;
}

void FreeDump(void )
{
    if(g_TaskDump)
        QyFree(g_TaskDump);
    g_TaskDump = NULL;
}


int FindAsynTask(int fsh,QYF_NODE *node)
{
     UINT rd;
     do{
         FS_Read(fsh, node, HEADER_SIZE,&rd);
         if( rd < HEADER_SIZE ) return 0;

         if( !(node->filetype & (QYF_SENT|QYF_FAILE)) ) //Not sent yet
         {     
            return node->tsksize - HEADER_SIZE ;
         }
         FS_Seek(fsh,  node->tsksize - HEADER_SIZE ,  FS_FILE_CURRENT);
         g_pAsynTaskOffset += node->tsksize;
     }while(1);
     return 0;

}

const int g_cmdReqAck[] = {CMD_RECIVE, CMD_SIGN_RECTP, CMD_PROBLEM};
int OnFishAsynSend(int ret)
{
    int fsh = 0;
    if( ret > 0 )
    {
        int cmd, err,field;
        void * hack = GetAckHandle(&cmd, &err,&field,NULL);
        FreeAckHandle(hack);

        if( g_pAsynTask && cmd == g_cmdReqAck[(g_pAsynTask->filetype&QYF_FILE_MASK) - 1])
        {
            U16 flag = ( err == 0)?  QYF_SENT :  QYF_FAILE;
            U16 fname[64];
            kal_wsprintf(fname,"%w_%c.dat" ,GetQyFileName(g_pAsynTask->filetype&QYF_FILE_MASK),g_pAsynTaskExtChar);
            fsh  = OpenQyFile(QY_USER, fname,FS_READ_WRITE);
            //fsh  = OpenTasksFile( g_pAsynTask->filetype,  g_pAsynTaskExtChar, FS_READ_WRITE);
            if( fsh > 0 )
            {
                UINT rd ;
                flag |= (g_pAsynTask->filetype&QYF_FILE_MASK);
                FS_Seek(fsh, g_pAsynTaskOffset+4, FS_FILE_BEGIN);
                FS_Write(fsh, &flag, 2 ,&rd);
                FS_Close(fsh);
            }    
        }
            
    }
    
    QyFree(g_pAsynTask);
    g_pAsynTask = NULL;
    if( ret > 0 && fsh > 0)
        ReStartQyAsySendThread();
    return 1;
}
 

int AsynSendTask(QYFILE_TYPE ftype)
{
    int fsh, ret = 0, index;
    U16 fname[32]; 
    for( index = (int)'A'; ret == 0 && index<(int)'Z';index++)
    {
        kal_wsprintf(fname, "%w_%c.dat",GetQyFileName(ftype),index);
        fsh = OpenQyFile(QY_USER, fname, FS_READ_ONLY);
        if( fsh > 0 )
        {
            U32 rlen;
            QYF_NODE node;
            g_pAsynTaskOffset = 0;
            rlen = FindAsynTask(fsh, &node); 
            if( rlen > 0 )
            {
                if( node.tsksize )
                {
                    if( g_pAsynTask ) QyFree(g_pAsynTask);
                    
                    g_pAsynTask = CreateTask(ftype, (node.tsksize)/sizeof(QY_RDID));
                    FS_Read(fsh, g_pAsynTask->taskname,sizeof(TASK_HEADER)-6-8, &rlen );
                    FS_Read(fsh, g_pAsynTask->pJunor,g_pAsynTask->LenJunor, &rlen );
                    FS_Read(fsh, g_pAsynTask->pRdId, g_pAsynTask->totals*sizeof(QY_RDID), &rlen);
                    //read header
                    //read jouner
                    //read rdid
                    FS_Close(fsh);
                    if( rlen > 0 )
                    {
                        g_pAsynTaskExtChar = index;
                        g_pAsynTask->tsksize = node.tsksize;
                        g_pAsynTask->filetype = node.filetype;
                        g_CmdType = 1;
                        SendTask(g_pAsynTask, 0, OnFishAsynSend);   
                        g_CmdType = 0;
                    }                    
                    ret = 1;
                }
            }
            else
                DeleteQyFile(QY_USER, fname);
        }
        FS_Close(fsh);
    }
    return ret;
}




int g_AsySendThreadStatus = QYTSK_NOT_RUN;


void ReStartQyAsySendThread(void)
{
    g_AsySendThreadStatus = QYTSK_RUNNING;
}

void StartQyAsySendThread(void)
{
    g_AsySendThreadStatus = QYTSK_RUNNING;
    StartTimer(ASYN_TASK,1000,QyAsnchTaskEntry);
    StartTimer(ASYN_CHECK,g_SettingProf->AutoConnectTime*1000,QyAsnchCheckEntry);    
}

void SuspendQyAsySendThread(void)
{
    g_AsySendThreadStatus = QYTSK_SUSPEND;
}

void ResumeQyAsySendThread(void)
{
    g_AsySendThreadStatus = QYTSK_RUNNING;   
}

void ResetAsyCheckTimer(void)
{
    StartTimer(ASYN_CHECK,g_SettingProf->AutoConnectTime*1000,QyAsnchCheckEntry);
}


void QyAsySendReadyTask(void)
{
    if( AsynSendTask(QYF_RECIVE) == 0 )
    {
        if( AsynSendTask(QYF_SIGN) == 0 )
        {
            if( AsynSendTask(QYF_PROBLEM) == 0 )
            {
                return;
            }
        }
    }  
}


LPNOB g_NobQueu[3][2];
void ClearAsynNob(void)
{
    g_NobQueu[1][0] = g_NobQueu[1][1] = NULL;
}

void ClearNobQueue(void * nob)
{
    LPNOB  pNob = (LPNOB)nob;
    if(pNob && pNob->pCmdCurPtr )
    {
        g_NobQueu[pNob->type][0] = g_NobQueu[pNob->type][1];
        g_NobQueu[pNob->type][1] = NULL;
    }

}

void PostToSystemNob(void * nob)
{
    LPNOB  pNob = (LPNOB)nob;
    if(pNob && pNob->pCmdCurPtr && g_SettingProf )
    {
        if( g_NobQueu[pNob->type][0] == NULL )
            g_NobQueu[pNob->type][0] = pNob;
        else
            g_NobQueu[pNob->type][1] = pNob;
        if( pNob->type == 0 )
            StartTimer(ASYN_TASK,10,QyAsnchTaskEntry);
    }
}


void QyAsnchCheckEntry(void)
{
    StartTimer(ASYN_CHECK,g_SettingProf->AutoConnectTime*1000,QyAsnchTaskEntry);
    //Check ready task to send
    if( g_AsySendThreadStatus == QYTSK_RUNNING && (g_NobQueu[1][0] == NULL ))
    {
        QyAsySendReadyTask();
    }
          
}

void QyAsnchTaskEntry(void)
{
    StartTimer(ASYN_TASK,1000,QyAsnchTaskEntry);
    if( g_OnGoningNob )//Current net resource avlibal
    {
        return ;
    }
        
    if( g_NobQueu[0][0]) //Check Current request
    {
        kal_prompt_trace(MOD_MMI, "Start Send ui task");
        SendNob(g_NobQueu[0][0]);
        return ;
    }

    if( g_AsySendThreadStatus == QYTSK_RUNNING && g_NobQueu[1][0] )
    {
        kal_prompt_trace(MOD_MMI, "Start asynch task");
        SendNob(g_NobQueu[1][0]);
        return ;
    }


    //Check Messge to load
}


void CancelNet(void)
{
    QyNobSendDone(-4);
}

#define TEMP_BUFF_SIZE (0x10000*4 )
/*
升级包信息头
 
升级包文件长度 UNC-2编码，8个字符   分隔符 \0x00\0x09
升级包RAM大小 UNC-2编码，8个字符    分隔符 \0x00\0x09
是否压缩 没有压缩为NONE，压缩则为压缩算法名，长度可变，最多16字符 分隔符  \0x00\0x09
程序说明 该升级包升级信息，长度可变，最大200字符

升级包文件长度	UNC-2编码，8个字符
升级包RAM大小	UNC-2编码，8个字符
校验码	8个字符
依赖版本号	Unicode编码,固定长度,4个字符
是否压缩	没有压缩为NONE，压缩则为压缩算法名，长度可变，最多16字符
程序说明	该升级包升级信息，长度可变，最大200字符

*/

typedef struct tag_UpdatePakageInfo
{
    U32 fsize;
    U32 ramsize;
    U32 chksum;
    U32 CompessType;
    U32 fwrite;
    U16 bPopup;
    U16 txt[200];
    U8 * pbuf;
}UPDATEPAKAGEINFO;
UPDATEPAKAGEINFO *  g_pUpgradeInfo = NULL;
U16 g_szExeBinF[] = {L"AppsEntry.bin"};
U16 g_szDownBinF[] = {L"AppsEntryx.bin"};
U16 g_szDecBinF[] = {L"AppsEntryD.bin"};

void FreeQyUpdateRes(int upRet)
{
    if( g_pUpgradeInfo && g_pUpgradeInfo->bPopup)
    {
        OnUiUpdateEnd(g_pUpgradeInfo->bPopup, upRet);
        g_pUpgradeInfo->bPopup = 0;      
        QyFree(g_pUpgradeInfo->pbuf);
        QyFree(g_pUpgradeInfo);
        kal_prompt_trace(MOD_MMI, "Upgrade resource free");
        g_pUpgradeInfo = NULL;
    }
   
}

void OnUpdateProgOK()
{
    U16 dstf[64], srcf[64];
    GetQyPathFile(dstf,QY_PROG, g_szExeBinF);
    GetQyPathFile(srcf,QY_PROG, g_szDownBinF);
    FS_Delete(dstf);
    FS_Rename(srcf,dstf); 
    g_SettingProf->ProgFLen = g_pUpgradeInfo->fsize;
    g_SettingProf->ProgRamSize = g_pUpgradeInfo->ramsize;
    memset(g_SettingProf->user_info.pwd,0, sizeof(U16)*QY_PSWD_MAX_LEN);  //Clear PWD force to login next log
    SaveQySettingProfile(g_SettingProf);
    
}

int QyOnUpdateAck(int ret)
{
    int update_ret = -1;
    if( ret > 0 )
    {  
        //int fsh = 0;
        //int ntotal = 0;
        int ngot;
        U8 * g_temp = &g_pUpgradeInfo->pbuf[g_pUpgradeInfo->fwrite];
        
		do
        {
            g_temp = &g_pUpgradeInfo->pbuf[g_pUpgradeInfo->fwrite];
            ngot = QyGetAckData(g_temp,  TEMP_BUFF_SIZE );
            
            if( ngot > 0 )
            {
                if( g_pUpgradeInfo )
                    g_pUpgradeInfo->fwrite += ngot;//wt;
            }
        }while( 0);// ngot);
        

        kal_prompt_trace(MOD_MMI, "Read package, %x",g_pUpgradeInfo->fwrite);

        //FS_Close(fsh);
        //QyFree(g_temp);
        StartTimer(SOCKET_TIMEOUT_TIMER,150000,qy_soc_timeout);    
        return 0;

    }
    else if( ret == 0 )
    {
        int fsh = OpenQyFile(QY_PROG, g_szDownBinF, FS_CREATE_ALWAYS|FS_READ_WRITE);
        {
            UINT wt;
            U8  * pbuf = g_pUpgradeInfo->pbuf;
            FS_Write(fsh, pbuf,g_pUpgradeInfo->fwrite,&wt);
            kal_prompt_trace(MOD_MMI, "write file, %x,%x;[%x]",g_pUpgradeInfo->fwrite,wt, g_pUpgradeInfo->fsize);
            kal_prompt_trace(MOD_MMI, "data %x,%x,%x,%x", pbuf[0],pbuf[1],pbuf[2],pbuf[3]);
            FS_Commit(fsh);
            
            FS_Close(fsh);          
        }
        if( g_pUpgradeInfo && g_pUpgradeInfo->CompessType == 1)
        {
            int fsh = OpenQyFile(QY_PROG, g_szDownBinF, FS_READ_WRITE);
            if( fsh > 0 )
            {
                UINT wd;
                char * buff = QyMalloc(TEMP_BUFF_SIZE );
                char * pout = QyMalloc(TEMP_BUFF_SIZE );
                int wlen = Decode(fsh, buff,TEMP_BUFF_SIZE,pout);
                FS_Close(fsh);
                
                fsh = OpenQyFile(QY_PROG, g_szDecBinF,  FS_CREATE_ALWAYS|FS_READ_WRITE);
                if( fsh )
                    FS_Write(fsh, pout, wlen, &wd);
                FS_Close(fsh);
                
                if( wd == (UINT)wlen ) // && VerifyOK)
                {
                    g_SettingProf->ProgFLen = wlen;
                    OnUpdateProgOK();
                    update_ret = 0;
                }
                
                QyFree(buff);
				QyFree(pout);
            }
        }
        else
        {
            //if(verifyOK)
            if( g_pUpgradeInfo->fsize <= g_pUpgradeInfo->fwrite )
            {
                OnUpdateProgOK();
                update_ret = 0;
            }
        }
        
    }
    //StartTimer(SOCKET_TIMEOUT_TIMER,500,FreeQyUpdateRes);    
    FreeQyUpdateRes(update_ret);
    return 1;
    
}


int QySendUpdateSwCmd( int (*f)(int ret), U16 * pver)
{
    HCMD hcmd = QyInitialComamnd(CMD_UPDATESW,CMD_QUERYUPDATE_REQ,0);
    if( hcmd )
    {
		QyAppendCmdItem(hcmd, pver);
        QyWrapPackage(hcmd );
        QySendPackage(hcmd, f, 1);
        return 1;
    }
    return 0;
}

int QyBeginUpdatePackage(int (*f)(int ), U16 * pver)
{
    StopTimer(SOCKET_TIMEOUT_TIMER);
    soc_close(g_qy_socket_id);        
    QySendUpdateSwCmd(f, pver);
    g_pUpgradeInfo->bPopup = OnUiUpdateStart();
    return 1;
}

#define VER_PROG  1


const U16 g_CompressCode[][5] = { {L"NONE"},{L"LZSS"}};



int QyOnQueryUpdateAck(int ret)
{
    if( ret > 0 )
    {
        int cmd, err,field, bCompress;
        void * hack = GetAckHandle(&cmd, &err,&field, NULL);

        bCompress = 0;
        if( cmd == CMD_QUERYUPDATE  )
        {
            int ver = -1  ;
            U16 * pver = GetFeild(hack, 0, 7) ;
            bCompress = -1;
			if( pver )
			{
				int i;
				for(i=0 ;i<sizeof(g_CompressCode)/(sizeof(U16)*5); i++)
				{
					if( memcmp(pver, g_CompressCode[i], 5 * sizeof(U16)) == 0)
					{
                        bCompress = i;
                        break;
					}
                    
				}
            }

            if( bCompress == -1 )
                return 1 ;

            GetFieldInt(hack, 0, 2, (U32 *)&ver) ;
            if ( ver != -1 && ver > VER_PROG )
            {
                if( g_pUpgradeInfo == NULL ) 
                {
                    g_pUpgradeInfo = (UPDATEPAKAGEINFO*)QyMalloc(sizeof(UPDATEPAKAGEINFO)) ;
                    
                }
                if( g_pUpgradeInfo )
                {
                    memset( g_pUpgradeInfo, 0, sizeof(UPDATEPAKAGEINFO) );
                    g_pUpgradeInfo->CompessType = bCompress; 
                    GetFieldIntx(hack, 0, 3, &g_pUpgradeInfo->fsize) ;
                    GetFieldIntx(hack, 0, 4, &g_pUpgradeInfo->ramsize) ;
                    GetFieldIntx(hack, 0, 5, &g_pUpgradeInfo->chksum) ;
                    g_pUpgradeInfo->pbuf = (U8 *)QyMalloc(g_pUpgradeInfo->fsize+1024);
                    kal_prompt_trace(MOD_MMI, "Upgrade resource free, %x",g_pUpgradeInfo->fsize );
                    pver = GetFeild(hack, 0, 2) ;
                    QyBeginUpdatePackage(QyOnUpdateAck,pver);
                }
                
            }
        }
        else
        {
        }
        FreeAckHandle(hack);            
    }
    return 1;
}

int QySendQueryUpdateCmd( int (*f)(int ret), U16 * pver)
{
    HCMD hcmd = QyInitialComamnd(CMD_QUERYUPDATE,CMD_QUERYUPDATE_REQ,0);
    if( hcmd )
    {
		QyAppendCmdItem(hcmd, pver);
        QyWrapPackage(hcmd );
        QySendPackage(hcmd, f, 0);
        return 1;
    }
    return 0;
}

void QureySwUpdateable(void)
{
    U16 vers[8];
    kal_wsprintf(vers, "%04d", QY_APPLICATION_VERSION);
    QySendQueryUpdateCmd(QyOnQueryUpdateAck,vers);
    //QySendQueryUpdateCmd(QyOnQueryUpdateAck);
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Query express status by express id
typedef int (*nob_fnx)(int );


int OnQueryExpIdStatu(int ret)
{
    NOB_ACK  ack_info;
    if( ret > 0 )
    {
        GetAckHandleEx( &ack_info);
    }
    ack_info.result = ret;
    OnUiCmdFinsh(&ack_info);   
    FreeAckHandle(ack_info.pbuf);     
    return 1;
}

int QySendQueryStatuByExpid(nob_fnx cbfnx, U16 * strExpId)
{
    HCMD hcmd = QyInitialComamnd(CMD_QRY_EXP_STATUS,CMD_QRY_EPX_STA_REQ,0);
    if( hcmd )
    {
		QyAppendCmdItem(hcmd, strExpId);
        QyWrapPackage(hcmd );
        QySendPackage(hcmd, cbfnx, 0);
        return 1;
    }
    return 0;
}

void QueryStatuByExpId(U16 * strExpId)
{
    QySendQueryStatuByExpid(OnQueryExpIdStatu, strExpId);
}
