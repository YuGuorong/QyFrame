#include "QinYiCommon.h"

#define MAX_CMD_BUFF_LEN  1024


void QyAppendCmdItem(U16 *strParam);



U16 *g_pCmdPtr = NULL; 
U16 *g_pCmdCurPtr;
int g_cmdLen;
void (*g_QyCmdFinish)(int ret);

void ResetQyProtocol()
{
    if( g_QyCmdFinish ) g_QyCmdFinish = NULL;
    if( g_pCmdPtr ) 
    {
        QyFree(g_pCmdPtr);
        g_pCmdPtr = NULL;
    }
    g_cmdLen = 0;
}

int QyAppendTime()
{
    MYTIME syst;
    GetDateTime(&syst);
    kal_wsprintf((U16 *)g_pCmdCurPtr, "`%d%02d%02d%02d%02d%02d", syst.nYear, syst.nMonth, syst.nDay, syst.nHour, syst.nMin, syst.nSec); 
    g_pCmdCurPtr += 15;
    return 14;
}

int QyInitialComamnd(int cmd, int req, int maxlen)
{
    ResetQyProtocol();
    g_cmdLen = ( maxlen ==0 )? MAX_CMD_BUFF_LEN : maxlen ; 

    g_pCmdPtr = QyMalloc(g_cmdLen);

    if( g_pCmdPtr == NULL) 
        return 0;

    memset(g_pCmdPtr, 0, g_cmdLen);
    
    kal_wsprintf(((U16 *)g_pCmdPtr)+9, "%4d`%02d00", cmd, req); 
    g_pCmdCurPtr = g_pCmdPtr + 18;

    QyAppendCmdItem(g_SettingProf->user_info.name);
    QyAppendTime();

    return 16;
}

void QyAppendItem(U16 *strParam, U16 spit)
{
    if( g_pCmdPtr )
    {
        kal_wsprintf((U16 *)(g_pCmdCurPtr), "%c%w",spit, strParam); 
        g_pCmdCurPtr += kal_wstrlen(strParam) + 1;
    }    
}

void QyAppendCmdItem(U16 *strParam)
{
    QyAppendItem(strParam, L'`');
}


void QyAppendParmItem(U16 *strParm)
{
    QyAppendItem(strParm, L'\t');
}

void QyAppendCmdInt(int val, U16 spit)
{
    if( g_pCmdPtr )
    {
        kal_wsprintf((U16 *)(g_pCmdCurPtr), "%c%08d",spit, val); 
        g_pCmdCurPtr = g_pCmdCurPtr + kal_wstrlen(g_pCmdCurPtr);
    }    
    
}


void QyWrapPackage()
{
    if( g_pCmdPtr )
    {
         int len = (g_pCmdCurPtr - g_pCmdPtr + 1 - 8 )*2;
         kal_wsprintf(g_pCmdPtr,"%08X", len);
         g_pCmdPtr[8] = L'`';
         kal_wsprintf(g_pCmdCurPtr,"`\n");
         g_cmdLen =(g_pCmdCurPtr - g_pCmdPtr + 2 )*2;
    }         
}


void QyPackageDone(int ret);
int Qy_soc_socket_notify(void *inMsg, int Msg);

void qy_soc_timeout(void)
{
    StopTimer(SOCKET_TIMEOUT_TIMER);
    soc_close(g_qy_socket_id);
    QyPackageDone(-1);
}

int mtk_soc_socket_notify(void *inMsg);
int QySendPackage( void (*f)(int ret) , int bBinary )
{
     int ret = 0;
    if( g_SettingProf )
    {
        int port = bBinary > 0 ? g_SettingProf->BinHost_port : g_SettingProf->Host_port;
        ret = MtkSocketConnect(g_SettingProf->Host_ip, port, 10, Qy_soc_socket_notify);
        if( ret  ) 
            g_QyCmdFinish = f;
	}
    return ret;
}

void QyPackageDone(int ret)
{
    kal_prompt_trace(MOD_MMI,"QyPackageDone %d", ret);
    if( g_QyCmdFinish)
    {
        g_QyCmdFinish(ret);
        if( ret <= 0 )
        {
            ResetQyProtocol();
        }
    }
}

    
int Qy_soc_socket_notify(void *inMsg, int msg)
{
    app_soc_notify_ind_struct *soc_notify = (app_soc_notify_ind_struct*) inMsg;

    kal_prompt_trace(MOD_MMI,"Qy_soc_socket_notify %d, %d", soc_notify->event_type,msg);
    
    switch (msg)
    {
    case SOC_WRITE:
        //soc_send(....);
        break;
    case SOC_READ:
        kal_prompt_trace(MOD_MMI,"SOC_READ");
        QyPackageDone(1);
        /*soc_recv(g_qy_socket_id, g_paBuffer, 256, 0);
        mmi_scan_display_popup((UI_string_type) g_paBuffer, MMI_EVENT_INFO);*/
        break;
    case SOC_CONNECT:
        kal_prompt_trace(MOD_MMI,"SOC_CONNECT %d", soc_notify->result);
        if( g_pCmdPtr )
        {
            soc_send(g_qy_socket_id,g_pCmdPtr,g_cmdLen, 0);
            StartTimer(SOCKET_TIMEOUT_TIMER,6000,qy_soc_timeout);
        }
        else
        {
            //QyPackageDone(1);
        }
        
        break;
    case SOC_CLOSE:
        kal_prompt_trace(MOD_MMI,"SOC_CLOSE %d", g_qy_socket_id);
        soc_close(g_qy_socket_id);
        QyPackageDone(0);
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
        ret = soc_send(g_qy_socket_id,g_pCmdPtr,g_cmdLen, 0);
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
    if( *ptr ) ptr++;
    
    while(*ptr && *ptr != L'`')
    {
        ptr++;
    }
    if( ptr == (U16 *)buff )
        ptr = NULL;
    if( *ptr == 0 ) ptr++;
    return ptr;
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

//TODO:
int ParseAckCode(void * buff, int len)
{
    GetFeild( buff,  len, 1);
    return 1;
}

int ParseAckPackage(int * pcmd, int * perr, U16 * pack, int len)
{
    int fields = 1;
    U16 * ptr_cmd = pack, * ptr_err;

    
    while( *pack && (*pack != L'\n'))
    {
        if( *pack == L'`' )
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


void * GetAckHandle( int * pcmd,int * perr, int * pFieldTotal)
{
    int totals;
    int len = QyGetAckLen() + 8;
    U16 * pack = QyMalloc(len);

    if( pack )
    {
        memset( pack, 0 , len );
        QyGetAckData(pack, len-4);

        totals = ParseAckPackage(pcmd, perr, pack+1, len );

        if( pFieldTotal)
            *pFieldTotal = totals;
    }
    return pack;
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
int QySendLoginCmd(U16 * user , U16 * pwd, void (*f)(int ret))
{
    if( QyInitialComamnd(CMD_LOGIN,CMD_LOGIN_REQ,0) )
    {
        U16 ver[8];
        QyAppendCmdItem(user);
        QyAppendParmItem(pwd);
        kal_wsprintf(ver,"%000d",QY_APPLICATION_VERSION);
        QyAppendParmItem(ver);
        QyWrapPackage();
        QySendPackage(f, 0);
        return 1;
    }
    return 0;
}


int QyPrepareSignRecptCmd(U16 * SignName, int totals,QY_RDID * pIds, FuncCmdAck f)
{
    int i;
    if( QyInitialComamnd(CMD_SIGN_RECTP,CMD_SRECTP_REQ,(totals*MAX_RDID_LEN+64+QY_USER_MAX_LEN)*2) )
    {
        U16 Strrdid[MAX_RDID_LEN+2];
        QyAppendCmdItem(SignName);
        QyAppendCmdInt(totals, L'\t');
        for( i=0; i<totals; i++)
        {
            mmi_asc_n_to_wcs(Strrdid, (S8*)pIds[i].Rdid, MAX_RDID_LEN+1),
            QyAppendParmItem(Strrdid);
        }
        QyWrapPackage();
        QySendPackage(f, 0);
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
/*14	电话无人接听           1. 电话无人接听
    3	查无此人               2. 查无此人
    1	地址不详               3. 地址不详
    5	拒付到付款             4. 拒付到付款
    12	拒付代收货款           5. 拒付代收货款
    6	客户拒收               6. 客户拒收
    7	破损件                 7. 破损件
    15	客户要求重新派送       8. 客户要求重新派送
    17	家中无人               9. 家中无人
    16	其他                   10.其他*/

const int g_problem_map[]= {14,3, 1, 5, 12, 6, 7, 15, 17, 16,11};

int QyPrepareIssueCmd(PROBLEM_JOUNOR * pProblemJouner, int totals,QY_RDID * pIds, FuncCmdAck f)
{
    int i = kal_wstrlen(pProblemJouner->strOther);
    U16 Strrdid[MAX_RDID_LEN+2];
    U16 strProblemID[4];
    int idx;
    mmi_ucs2tox((S8*)pProblemJouner->ProblemID, &idx,NULL);
    if( idx < 0 && idx >= sizeof(g_problem_map)/sizeof(int))
        return 0; 
    
    kal_wsprintf(strProblemID,"%d",g_problem_map[idx] );
    
    if( QyInitialComamnd(CMD_PROBLEM, CMD_SRECTP_REQ,(totals*MAX_RDID_LEN+64+QY_USER_MAX_LEN)*2)+(i*2+16) )
    {
        
        //QyAppendCmdInt(totals, L'\t');//运单总数 
        for( i=0; i<totals; i++)
        {
            mmi_asc_n_to_wcs(Strrdid, (S8*)pIds[i].Rdid, MAX_RDID_LEN+1);
            if( i == 0 )
            {
                QyAppendCmdItem(Strrdid);
                QyAppendParmItem(strProblemID);//问题件类型
            }
            else
            {
                QyAppendParmItem(Strrdid);
                QyAppendParmItem(L" ");
            }
        }
            
        if(pProblemJouner->strOther[0] )
            QyAppendParmItem(pProblemJouner->strOther);
        else
            QyAppendParmItem(L" ");
        QyWrapPackage();
        QySendPackage(f, 0);
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
    int fs_h  = FindQyTaskFile(ptask->filetype, 1);
    if( fs_h > 0  )
    {
        U32 wdb = 0;
        UINT fsStartPos = FS_Seek(fs_h, 0, FS_FILE_END);
        
        ptask->tsksize = sizeof(TASK_HEADER)+ptask->LenJunor+sizeof(QY_RDID)*ptask->totals;
        mmi_asc_n_to_wcs(ptask->taskname, (S8*)ptask->pRdId[0].Rdid, MAX_RDID_LEN+1);//mmi_asc_n_to_ucs2

        ret = ERR_FILE_WRITING;
        FS_Write(fs_h, ptask, sizeof(TASK_HEADER), &wdb);    
        if( wdb != sizeof(TASK_HEADER) ) goto endf;
        
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
                FS_Read(fsh, &ptask->filetype, sizeof(TASK_HEADER)-4, &rd);
                if( rd < sizeof(TASK_HEADER)-4) 
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
    return 0;
} 




#define HEADER_SIZE    (sizeof(U32)+sizeof(U16))
typedef struct headif
{
    U32    tsksize;
    U16    filetype;
}QYF_NODE;

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


void QyAsySendThreadEntry(void);

int g_AsySendThreadStatus = QYTSK_NOT_RUN;
TASK_HEADER * g_pAsynTask; 
U32 g_pAsynTaskOffset;
U16 g_pAsynTaskExtChar;

int GetAsynchoThreadStatus()
{
    return g_AsySendThreadStatus;
}

void SetQyAsySendThreadStatus(int status)
{
    g_AsySendThreadStatus = status;
}

void ReStartQyAsySendThread(void)
{
    QYTHREAD_STATUS status= GetAsynchoThreadStatus();
    if(status & QYTSK_TERMINATE)
        return;
    g_AsySendThreadStatus &= ~QYTSK_SENDING;
    if( g_AsySendThreadStatus == QYTSK_RUNNING )
        StartTimer(ASYN_SEND_TASK,10,QyAsySendThreadEntry);
}

void StartQyAsySendThread(void)
{
    QYTHREAD_STATUS status= GetAsynchoThreadStatus();
    if( status== QYTSK_NOT_RUN)
        g_pAsynTask = NULL;
    else if( status == QYTSK_RUNNING )
        return;
    else if(status == QYTSK_TERMINATE)
        return;
    
    SetQyAsySendThreadStatus( QYTSK_RUNNING );    
    StartTimer(ASYN_SEND_TASK,g_SettingProf->AutoConnectTime*1000,QyAsySendThreadEntry);
}

void SuspendQyAsySendThread(void)
{
    SetQyAsySendThreadStatus( QYTSK_SUSPEND|GetAsynchoThreadStatus());
}

void ResumeQyAsySendThread(void)
{
    SetQyAsySendThreadStatus( ~QYTSK_SUSPEND & g_AsySendThreadStatus);
}

void TerminalQyAshSendThread(void)
{
    SetQyAsySendThreadStatus( QYTSK_TERMINATE );
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
void OnFishAsynSend(int ret)
{
    int fsh;
    if( ret > 0 )
    {
        int cmd, err,field;
        void * hack = GetAckHandle(&cmd, &err,&field);
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
    else
        TerminalQyAshSendThread();
}


int AsynSendTask(QYFILE_TYPE ftype)
{
    int fsh, ret, index;
    U16 fname[32]; 
    for( index = (int)'A'; index<(int)'Z';index++)
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
                    FS_Read(fsh, g_pAsynTask->taskname,sizeof(TASK_HEADER)-6, &rlen );
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
                        SetQyAsySendThreadStatus(QYTSK_SENDING|GetAsynchoThreadStatus());
                        SendTask(g_pAsynTask, 0, OnFishAsynSend);                        
                    }                    
                    return ret;
                }
            }
            else
                DeleteQyFile(QY_USER, fname);
        }
        FS_Close(fsh);
    }
    return 0;
}

void QyAsySendThreadEntry(void)
{
    StartTimer(ASYN_SEND_TASK,g_SettingProf->AutoConnectTime*1000,QyAsySendThreadEntry);
    if( QYTSK_RUNNING != GetAsynchoThreadStatus() ) 
        return;
    if( AsynSendTask(QYF_RECIVE) == 0 )
    {
        if( AsynSendTask(QYF_SIGN) == 0 )
        {
            if( AsynSendTask(QYF_PROBLEM) == 0 )
            {
                SetQyAsySendThreadStatus(QYTSK_NOT_RUN);
                StopTimer(ASYN_SEND_TASK);
                return;
            }
        }
    }  
}


#define TEMP_BUFF_SIZE (31580 )
U8 g_temp[TEMP_BUFF_SIZE+64];
void QyOnUpdateAck(int ret)
{
    if( ret > 0 )
    {  
        int fsh = 0;
        int ntotal = 0;
        int ngot;
        do{
            ngot = QyGetAckData(g_temp,  TEMP_BUFF_SIZE );
            
            if( ngot > 0 )
            {
                UINT wt;
                ntotal +=  ngot;
				if (fsh <= 0 )
					fsh = OpenQyFile(QY_PROG, L"AppEntryx.bin", FS_READ_WRITE);
                FS_Seek(fsh, 0, FS_FILE_END);
                FS_Write(fsh, &g_temp, ngot ,&wt);
                FS_Commit(fsh);
            }
        }while( ngot > 0  );
        FS_Close(fsh);
        StartTimer(SOCKET_TIMEOUT_TIMER,150000,qy_soc_timeout);        
    }
}


int QySendUpdateSwCmd( void (*f)(int ret), U16 * pver)
{
    g_SettingProf->Host_port = 9989;
    if( QyInitialComamnd(CMD_UPDATESW,CMD_QUERYUPDATE_REQ,0) )
    {
		QyAppendCmdItem(pver);
        QyWrapPackage();
        QySendPackage(f, 0);
        return 1;
    }
    return 0;
}

int QyBeginUpdatePackage(void (*f)(int ), U16 * pver)
{
    int fsh = OpenQyFile(QY_PROG, L"AppEntryx.bin", FS_CREATE_ALWAYS|FS_READ_WRITE);
    FS_Close(fsh);
    StopTimer(SOCKET_TIMEOUT_TIMER);
    soc_close(g_qy_socket_id);        
    QySendUpdateSwCmd(f, pver);
    return 1;
}

#define VER_PROG  1

void QyOnQueryUpdateAck(int ret)
{
    if( ret > 0 )
    {
        int cmd, err,field;
        void * hack = GetAckHandle(&cmd, &err,&field);

        if( cmd == CMD_QUERYUPDATE  )
        {
            int ver = 0x7ffff;
            U16 * pver = GetFeild(hack, 0, 2) ;
            mmi_ucs2toi((S8*)pver,&ver,NULL);
            if ( ver > VER_PROG )
            {
                QyBeginUpdatePackage(QyOnUpdateAck,pver);
            }
        }
        else
        {
        }
        FreeAckHandle(hack);
        
            
    }
}

int QySendQueryUpdateCmd( void (*f)(int ret), U16 * pver)
{
    g_SettingProf->Host_port = 9988;
    if( QyInitialComamnd(CMD_QUERYUPDATE,CMD_QUERYUPDATE_REQ,0) )
    {
		QyAppendCmdItem(pver);
        QyWrapPackage();
        QySendPackage(f, 0);
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
