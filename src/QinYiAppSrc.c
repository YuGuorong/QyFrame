#define QY_MODULE     0x2
#include "QinYiCommon.h"
/* Content */
#define SETTING_MODULE
#define LOGIN_MODULE 
#define SIGNRECPT_MODULE
#define PROGLEM_MODULE
#define QUERY_EXPID_MODULE
#define TASK_DETAIL_MODULE
#define RECEPT_NO_BILL_MOUDLE
#define NEW_BILL_MODULE
#define MESSAGE_WINDOW


#define ADD_TEXT_ITEM(text)     {SetInlineItemActivation(&(wgui_inline_items[idx]), INLINE_ITEM_ACTIVATE_WITHOUT_KEY_EVENT, 0);\
                                SetInlineItemDisplayOnly(&(wgui_inline_items[idx]), (U8*)text);idx++;}

#define ADD_CAPTION_ITEM(text)  {SetInlineItemActivation(&wgui_inline_items[idx], INLINE_ITEM_ACTIVATE_WITHOUT_KEY_EVENT, 0); \
                                SetInlineItemCaption(&(wgui_inline_items[idx]), (U8*)text); idx++;}

#define ADD_EDIT_ITEM(txtBuf,chrs, type)   \
                                {SetInlineItemActivation(&wgui_inline_items[idx], INLINE_ITEM_ACTIVATE_WITHOUT_KEY_EVENT, 0);\
                                SetInlineItemTextEdit(&wgui_inline_items[idx], (PU8)txtBuf,chrs+1, type);idx++;}


/************************************************************************************************
*      Module Application related Global function
*
************************************************************************************************/
typedef void (*FncConfirmResult)(int result);
int QyCheckPassword(void);
void OnSideKeyHandle(void);
void ResetAsyCheckTimer(void); 
void TraceMainTitleEx(int line);

QY_SETTING_PROF *  g_SettingProf;
HistoryDelCBPtr g_fncQyConfirmAbort = NULL;
FncConfirmResult g_fncCfmDlgRst;
U16 g_QinYi_UserName[QY_USER_MAX_LEN+1];
U16 g_QinYi_User_Pswd[QY_PSWD_MAX_LEN+1];

void QyDumyFunc(void)
{
}
void QyDumyFuncInt(int val)
{
    val = val;/*avoid warning*/
}

//-- popup  --/////////////////////////////////////////////
void OnPopopEndKey(void)
{
    ClearAllKeyHandler();
    CancelNet();
}

static void PopupWait(U8 *string, U16 imageId, U8 imageOnBottom, U32 popupDuration, U8 toneId)
{
    DisplayPopup(string, imageId, imageOnBottom, popupDuration, toneId);
    DisableKeyEvent();
    SetKeyHandler(OnPopopEndKey, KEY_END, KEY_EVENT_UP);
}



static void OnCfmDlgYes(void)
{
    GoBackHistory();
    if( g_fncCfmDlgRst )
        g_fncCfmDlgRst(1);

}

static void OnCfmDlgNo(void)
{
    GoBackHistory();
    if( g_fncCfmDlgRst )
        g_fncCfmDlgRst(0);
}

static void ConfirmDialog(U16 * title, FncConfirmResult ptrCfmResult)
{
    DisplayConfirm(
        QY_RES(STR_GLOBAL_YES),
        QY_RES(IMG_GLOBAL_YES),
        QY_RES(STR_GLOBAL_NO),
        QY_RES(IMG_GLOBAL_NO),
        (UI_character_type*)title,
        QY_RES(IMG_GLOBAL_QUESTION),
        WARNING_TONE);

    g_fncCfmDlgRst = ptrCfmResult;

    SetRightSoftkeyFunction(OnCfmDlgNo, KEY_EVENT_UP);
    SetLeftSoftkeyFunction(OnCfmDlgYes, KEY_EVENT_UP);        

}

static void QyExitWihoutSave(void)
{
    if( g_fncQyConfirmAbort )
        g_fncQyConfirmAbort(NULL);
    DeleteNHistory(1);
    GoBackHistory();
}

static void ConfirmExitWithSave(void)
{
    DisplayConfirm(
        QY_RES(STR_GLOBAL_YES),
        QY_RES(IMG_GLOBAL_YES),
        QY_RES(STR_GLOBAL_NO),
        QY_RES(IMG_GLOBAL_NO),
        (UI_character_type*)((U16*)"\x6E\x78\xA4\x8B\x0\x90\xFA\x51\x3F\x0\x0\x0") /*L"确认退出?"*/,
        QY_RES(IMG_GLOBAL_QUESTION),
        WARNING_TONE);

    SetRightSoftkeyFunction(GoBackHistory, KEY_EVENT_UP);
    SetLeftSoftkeyFunction(QyExitWihoutSave, KEY_EVENT_UP);        
}    

void SetConfirmExitAbortion(HistoryDelCBPtr funcAbort)
{
    g_fncQyConfirmAbort = funcAbort;
}

//-- Scan adapter  --/////////////////////////////////////////////
pfncScanDone g_QyScanCallback;

void QyScanDone(U16 *strcode)
{
    int i=26;
    U16 * pstr = strcode ;
    while( i--)
    {
        if( *pstr == '\r' || * pstr == '\n' )
        {
            *pstr = '\0';
            break;
        }
        pstr++;
    }   
    if( g_QyScanCallback )
        g_QyScanCallback(strcode);
    close_scan_engine();
}


static void OnScanKeyTrigle(void)
{
    if( g_QyScanCallback )
    {
        open_scan_engine(QyScanDone);
        trig_on_scan_engine();
        kal_prompt_trace(MOD_MMI,"OnScanKeyTrigle" );
    }
}



static void QinYiCloseScanDev(void)
{
    kal_prompt_trace(MOD_MMI,"QinYiCloseScanDev %d",GetScanKeyHandler() );   
    if( GetScanKeyHandler() )
    {
        //close_scan_engine();
        g_QyScanCallback = NULL;
        kal_prompt_trace(MOD_MMI,"close_scan_engine" );   
        SetScanKeyHandler( NULL );
    	SetDefaultScanKeyHandlers();
    }
}
  
static void QinYiSetScanHandle(pfncScanDone pfnx_scan_done)
{
    kal_prompt_trace(MOD_MMI,"open_scan_engine & SetKeyHandler %d",GetScanKeyHandler() );    
    if( GetScanKeyHandler() == NULL )
    {
        //open_scan_engine(pfnx_scan_done);
        g_QyScanCallback = pfnx_scan_done;
        kal_prompt_trace(MOD_MMI,"open_scan_engine" );           
        SetScanKeyHandler( OnScanKeyTrigle );
    	SetDefaultScanKeyHandlers();
    }
} 

static void ExitQinYListWindow(void)
{
    QinYiCloseScanDev();
    CloseCategory57Screen();
}

/************************************************************************************************
*      Module Setting 
*
************************************************************************************************/
#ifdef SETTING_MODULE
//-- Setting loging--//////////////////////////////////////////
void QySettingDetailApp(void);
void QySetingAuthWndOnOK(void)
{
    wgui_update_inline_data();
    if( kal_wstrcmp(g_QinYi_User_Pswd,g_SettingProf->pwd) == 0 )
    {
        U16 srcid = GetActiveScreenId();
        QySettingDetailApp();
        DeleteScreenIfPresent(srcid);
    }
    else
    {
        mmi_scan_display_popup((UI_string_type)((U16*)"\xC6\x5B\x1\x78\x19\x95\xEF\x8B\x21\x0\x0\x0") /*L"密码错误!"*/, MMI_EVENT_INFO);
    }
}

void QySettingAuthEntry(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    U8 *guiBuffer;
    U8 *inputBuffer;
    U16 inputBufferSize;
    int idx = 0;


    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    EntryNewScreen(SRC_SETTING_AUTH, ExitQinYListWindow, QySettingAuthEntry, NULL);
    InitializeCategory57Screen();

    guiBuffer = GetCurrGuiBuffer(SRC_SETTING_AUTH);
    inputBuffer = GetCurrNInputBuffer(SRC_SETTING_AUTH, &inputBufferSize);

    
    /* Setting password */
    ADD_CAPTION_ITEM(((U16*)"\xF7\x8B\x93\x8F\x65\x51\xA1\x7B\x6\x74\xC6\x5B\x1\x78\x0\x0") /*L"请输入管理密码"*/);
    ADD_EDIT_ITEM( (PU8) g_QinYi_User_Pswd, QY_PSWD_MAX_LEN, IMM_INPUT_TYPE_NUMERIC_PASSWORD);

    if (inputBuffer != NULL)
    {
        SetCategory57Data(wgui_inline_items, idx, inputBuffer);
    }

  //  DisableCategory57ScreenDone();

    ShowCategory57Screen_ex(
        (U8*)((U16*)"\xF7\x8B\x93\x8F\x65\x51\xA1\x7B\x6\x74\xC6\x5B\x1\x78\x0\x0") /*L"请输入管理密码"*/ ,
        0,
        QY_RES(STR_GLOBAL_OK),
        QY_RES(IMG_GLOBAL_OK),
        QY_RES(STR_GLOBAL_BACK),
        QY_RES(IMG_GLOBAL_BACK),
        idx,
        NULL,
        wgui_inline_items,
        0,
        guiBuffer);

    SetCategory57RightSoftkeyFunctions(QySetingAuthWndOnOK, GoBackHistory);
}

void QySettingApp(void)
{   
    memset(g_QinYi_User_Pswd, 0, sizeof(U16)*(QY_PSWD_MAX_LEN+1));
    QySettingAuthEntry();

}

//-- Setting Detail--//////////////////////////////////////////
#define MAX_PART_IP_ADDRESS                  4

//U16 g_NetCod[QY_USER_MAX_LEN];
U16 g_ServerIP[QY_IPSTRING_LEN+1];
U16 g_ServerPort[4+1];
U16 g_strReconTime[16+1];
int QyIPAddressString()
{
    int ret =0 , ipval, i;
    int ip[4];
    U16 * ptr = (U16 *)g_ServerIP;
    for(i=0; i<4; i++)
    {
        int rlen =0 ;
        ret =  mmi_ucs2toi(( S8 *)ptr, &ipval, &rlen);
        if( ret >= 0 && rlen >=0 )
        {
            ip[i] = ipval;
        }
        else
            return QY_ERROR;
        ptr += rlen+1;
    }
    for( i= 0 ;i<4 ;i++)
    {
        g_SettingProf->Host_ip[i] = (U8)ip[i];
    }
    return QY_SUCCESS;

}

void OnSettingDetailOK(void)
{
    S32 rlen , rec_time;
    U16 srcid = GetActiveScreenId();
    wgui_update_inline_data();

    if( QyIPAddressString() != QY_SUCCESS )
    {
        DisplayPopup((PU8)((U16*)"\x49\x0\x50\x0\x30\x57\x40\x57\x19\x95\xEF\x8B\x0\x0") /*L"IP地址错误"*/, QY_RES(IMG_GLOBAL_WARNING), 1, UI_POPUP_NOTIFYDURATION_TIME, 0);
        return;
    }
    kal_wstrncpy(g_SettingProf->pwd, g_QinYi_User_Pswd, QY_PSWD_MAX_LEN);
    if( kal_wstrncmp(g_SettingProf->user_info.name, g_QinYi_UserName, QY_USER_MAX_LEN) != 0 )
    {
        g_bQyAuthenticate = UN_AUTHEN;
        memset( g_SettingProf->user_info.pwd, 0 , QY_PSWD_MAX_LEN*sizeof(U16));
        kal_wstrncpy(g_SettingProf->user_info.name, g_QinYi_UserName, QY_USER_MAX_LEN);
    }

    mmi_ucs2toi(( S8 *)g_ServerPort, &g_SettingProf->Host_port, &rlen);
    
    mmi_ucs2toi((S8*)g_strReconTime, &rec_time, &rlen);
    if( rec_time != g_SettingProf->AutoConnectTime )
    {
        ResetAsyCheckTimer(); 
        g_SettingProf->AutoConnectTime = rec_time;
    }
    
    SaveQySettingProfile(g_SettingProf);
    
    DisplayPopup((PU8)((U16*)"\x8C\x5B\x10\x62\x0\x0") /*L"完成"*/, QY_RES(IMG_GLOBAL_SUCCESS), 1, UI_POPUP_NOTIFYDURATION_TIME, 0);
    DeleteScreenIfPresent(srcid);
    
    //GoBackHistory();
}


void QySettingDetailEntry(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    U8 *guiBuffer;
    U8 *inputBuffer;
    U16 inputBufferSize;
    int idx = 0;


    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    EntryNewScreen(SRC_SETTING_APP, ExitQinYListWindow, QySettingDetailEntry, NULL);
    InitializeCategory57Screen();

    guiBuffer = GetCurrGuiBuffer(SRC_SETTING_APP);
    inputBuffer = GetCurrNInputBuffer(SRC_SETTING_APP, &inputBufferSize);

    
    /* Setting password */
    ADD_CAPTION_ITEM(((U16*)"\xA1\x7B\x6\x74\xC6\x5B\x1\x78\x0\x0") /*L"管理密码"*/);
    ADD_EDIT_ITEM( (PU8) g_QinYi_User_Pswd, QY_PSWD_MAX_LEN, IMM_INPUT_TYPE_NUMERIC_SYMBOL);
    ADD_CAPTION_ITEM(((U16*)"\x1A\x4E\xA1\x52\x58\x54\x16\x7F\xF7\x53\x0\x0") /*L"业务员编号"*/);
    ADD_EDIT_ITEM( (PU8) g_QinYi_UserName, QY_USER_MAX_LEN, IMM_INPUT_TYPE_NUMERIC_SYMBOL);
    //ADD_CAPTION_ITEM(L"网点编号");
    //ADD_EDIT_ITEM( (PU8) g_NetCod, QY_PSWD_MAX_LEN, IMM_INPUT_TYPE_NUMERIC);
    ADD_CAPTION_ITEM(((U16*)"\xD\x67\xA1\x52\x68\x56\x49\x0\x50\x0\x0\x0") /*L"服务器IP"*/);
    ADD_EDIT_ITEM( (PU8) g_ServerIP, QY_IPSTRING_LEN, IMM_INPUT_TYPE_NUMERIC_SYMBOL);
    ADD_CAPTION_ITEM(((U16*)"\xD\x67\xA1\x52\x68\x56\xEF\x7A\xE3\x53\x0\x0") /*L"服务器端口"*/);
    ADD_EDIT_ITEM( (PU8) g_ServerPort, 4, IMM_INPUT_TYPE_NUMERIC);
    ADD_CAPTION_ITEM(((U16*)"\xEA\x81\xA8\x52\xDE\x8F\xA5\x63\xF6\x65\xF4\x95\x28\x0\xD2\x79\x29\x0\x0\x0") /*L"自动连接时间(秒)"*/);
    ADD_EDIT_ITEM( (PU8) g_strReconTime, 16, IMM_INPUT_TYPE_NUMERIC);

    if (inputBuffer != NULL)
    {
        SetCategory57Data(wgui_inline_items, idx, inputBuffer);
    }

  //  DisableCategory57ScreenDone();

    ShowCategory57Screen_ex(
        (U8*)((U16*)"\xBE\x8B\x6E\x7F\x0\x0") /*L"设置"*/ ,
        0,
        QY_RES(STR_GLOBAL_OK),
        QY_RES(IMG_GLOBAL_OK),
        QY_RES(STR_GLOBAL_BACK),
        QY_RES(IMG_GLOBAL_BACK),
        idx,
        NULL,
        wgui_inline_items,
        0,
        guiBuffer);

    SetCategory57RightSoftkeyFunctions(OnSettingDetailOK, GoBackHistory);
}

void QySettingDetailApp(void)
{
    kal_wsprintf(g_ServerIP, "%d.%d.%d.%d",
        g_SettingProf->Host_ip[0],g_SettingProf->Host_ip[1],
        g_SettingProf->Host_ip[2],g_SettingProf->Host_ip[3]);
    kal_wsprintf(g_ServerPort, "%d", g_SettingProf->Host_port);
    kal_wstrncpy(g_QinYi_User_Pswd,g_SettingProf->pwd,QY_PSWD_MAX_LEN);
    kal_wstrncpy(g_QinYi_UserName, g_SettingProf->user_info.name,QY_USER_MAX_LEN );
    kal_wsprintf(g_strReconTime,"%d",g_SettingProf->AutoConnectTime);
    QySettingDetailEntry();
    //RedrawCategory57Screen();
}

#endif

/************************************************************************************************
*      Module Loging 
*
************************************************************************************************/
#ifdef LOGIN_MODULE
//protype -------------------------------------------------------------------
void QinYiAppEntry(void);
int QySaveUserAndPwd(USER_INFO  * puserinfo); 
int LoadUserAndPwd(void);
void QureySwUpdateable(void); 
//Global -------------------------------------------------------------------
USER_INFO * g_SysUserInfo ;
MYTIME    g_LastServerAuthenTime;
static U8 g_curListWndSel = 0;
void DisableKeyEvent(void)
{
    int i;
    for( i=KEY_0; i<KEY_EXTRA_B;i++)
    {
        SetKeyHandler(NULL, i, KEY_EVENT_DOWN);
        SetKeyHandler(NULL, i, KEY_EVENT_UP);  
    } 
}


//Function -------------------------------------------------------------------
int OnUiUpdateStart(void)
{
    DisplayPopup((PU8)((U16*)"\x47\x53\xA7\x7E\xB\x7A\x8F\x5E\x2E\x0\x2E\x0\x2E\x0\x0\x0") /*L"升级程序..."*/, QY_RES(IMG_GLOBAL_PROGRESS), 1,(U32) -1, 0);
    DisableKeyEvent();
    return GetCurrScrnId();
} 

void OnUiUpdateEnd(U16 srcid, int result)
{
    if( result == 0 )
    {
        if( g_SettingProf->UpgradeMode == 0 )
            GoBackToHistory(IDLE_SCREEN_ID);
        DisplayPopup((PU8)("\x47\x53\xA7\x7E\xB\x7A\x8F\x5E\x10\x62\x9F\x52\xC\xFF\xF7\x8B\xCD\x91\xB0\x65\x7B\x76\x55\x5F\x0\x0") /*L"升级程序成功，请重新登录"*/, QY_RES(IMG_GLOBAL_OK), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
    }
    else
    {
        DisplayPopup(((PU8)"\x47\x53\xA7\x7E\xB\x7A\x8F\x5E\x31\x59\x25\x8D\x0\x0") /*L"升级程序失败"*/, QY_RES(IMG_GLOBAL_ERROR), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
    }
    
}

void SetQyLoginAuthenStatus(AUTHEN_TYPE  QyLogStatus)
{
    g_bQyAuthenticate = QyLogStatus;
}


int QyOnLoginAck(int ret)
{
    U16 sid = GetActiveScreenId();
    if(sid ==  POPUP_SCREENID)
    {
        ClearAllKeyHandler();
    }
    if( ret > 0 )
    {
        int cmd, err,field;
        MYTIME tmsvr, tmclt;
        void * hack = GetAckHandle(&cmd, &err,&field, NULL);

        
        FreeAckHandle(hack);

        if( cmd == CMD_LOGIN  )
        {
            if( err == 0 || err == 2 )
            {
                GetAckTime(hack, &tmsvr);

                GetDateTime(&tmclt);
                if(tmsvr.nYear != tmclt.nYear || tmsvr.nMonth != tmclt.nMonth 
                    || tmsvr.nDay != tmclt.nDay || tmsvr.nHour != tmclt.nHour
                    || tmsvr.nMin != tmclt.nMin )
                {
                    rtc_format_struct tmloc;
                    tmloc.rtc_year = tmsvr.nYear-2000;
                    tmloc.rtc_mon  = tmsvr.nMonth;
                    tmloc.rtc_day  = tmsvr.nDay;
                    tmloc.rtc_hour = tmsvr.nHour;
                    tmloc.rtc_min  = tmsvr.nMin;
                    tmloc.rtc_sec  = tmsvr.nSec;
                    kal_prompt_trace(MOD_MMI,"Login set time: (%d-%d-%d,%d:%d:%d)",
                    tmloc.rtc_year , 
                    tmloc.rtc_mon  , 
                    tmloc.rtc_day  , 
                    tmloc.rtc_hour , 
                    tmloc.rtc_min  , 
                    tmloc.rtc_sec   );
                    SetDateTimeEx( &tmloc);
                }
                kal_wstrncpy(g_SysUserInfo->name, g_QinYi_UserName, QY_USER_MAX_LEN);
                kal_wstrncpy(g_SysUserInfo->pwd,  g_QinYi_User_Pswd,QY_PSWD_MAX_LEN);
				QySaveUserAndPwd(g_SysUserInfo);
                g_bQyAuthenticate = QY_AUTHEND;
                GetDateTime(&g_LastServerAuthenTime);
                //show main qinyi menu
                gdi_layer_lock_frame_buffer();   
                DeleteScreenIfPresent(POPUP_SCREENID);
                DeleteScreenIfPresent(SRC_QINYI_LOGIN_APP);
                gdi_layer_unlock_frame_buffer();    
                 
                QinYiAppEntry();
                kal_prompt_trace(MOD_MMI,"Login statu (%d)", err );   
                if( err == 2 )
                {
                    QureySwUpdateable();
                }
            }
            else
            {
                DisplayPopup((PU8)QureyErrorString(err), QY_RES(IMG_GLOBAL_ERROR), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
            }
            return 1;
        }
        else
        {
            DisplayPopup((PU8)(((U16*)"\x1A\x90\xAF\x8B\x31\x59\x25\x8D\x0\x0") /*L"通讯失败"*/), QY_RES(IMG_GLOBAL_ERROR), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
        }
        
            
    }
    else if( ret == -1 )
    {
        gdi_layer_lock_frame_buffer();                
        GoBackHistory();
        gdi_layer_unlock_frame_buffer();    
        DisplayPopup((PU8)(((U16*)"\x1A\x90\xAF\x8B\x31\x59\x25\x8D\x0\x0") /*L"通讯失败"*/), QY_RES(IMG_GLOBAL_ERROR), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
    }

    return 1;
        
}

void QY_LoginCheck(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    //if( g_bQyAuthenticate == UN_AUTHEN )
    wgui_update_inline_data();
    if( g_bQyAuthenticate != LOCAL_AUTH )
    {   
        //Server authenticate 
		U16 tmpUserName[QY_USER_MAX_LEN];
		kal_wstrncpy(tmpUserName, g_SysUserInfo->name, QY_USER_MAX_LEN);
		kal_wstrncpy(g_SysUserInfo->name, g_QinYi_UserName, QY_USER_MAX_LEN);
        if( QySendLoginCmd(g_QinYi_UserName,g_QinYi_User_Pswd,QyOnLoginAck) )
        {
            DisplayPopup((PU8)((U16*)"\xDE\x8F\xA5\x63\xD\x67\xA1\x52\x68\x56\x2E\x0\x2E\x0\x2E\x0\x0\x0") /*L"连接服务器..."*/, QY_RES(IMG_GLOBAL_PROGRESS), 1,(U32) -1, 0);
            //EntryQYLoginProcess();  
            DisableKeyEvent();
        }
        else
        {
            DisplayPopup((PU8)((U16*)"\xDE\x8F\xA5\x63\x31\x59\x25\x8D\x0\x0") /*L"连接失败"*/, QY_RES(IMG_GLOBAL_ERROR), 1, (U32) -1, 0);
        }
		kal_wstrncpy( g_SysUserInfo->name, tmpUserName, QY_USER_MAX_LEN);

    }
    else//Local authenticate?
    {
        if(   ( kal_wstrcmp( g_QinYi_User_Pswd, g_SysUserInfo->pwd) == 0 )
            &&( kal_wstrcmp( g_QinYi_UserName,  g_SysUserInfo->name) == 0 ) )
        {
                g_bQyAuthenticate = QY_AUTHEND;
                GetDateTime(&g_LastServerAuthenTime);
                gdi_layer_lock_frame_buffer();
                GoBackToHistory(SCR_QINYI_APP_WINDOW_1);
                gdi_layer_unlock_frame_buffer();
                QinYiAppEntry();
                StartQyAsySendThread();
        }
        else 
        {
            DisplayPopup((PU8)((U16*)"\x28\x75\x37\x62\xD\x54\x16\x62\xC6\x5B\x1\x78\x19\x95\x0\x0") /*L"用户名或密码错"*/, QY_RES(IMG_GLOBAL_ERROR), 1, UI_POPUP_NOTIFYDURATION_TIME, 0);
        }
    }
}

void QyListWndSetHilt(S32 nIndex)
{
    g_curListWndSel = (U8) nIndex;
}


void EntryQinYiLoginEx(void) 
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    U8 *guiBuffer;
    U8 *inputBuffer;
    U16 inputBufferSize;
    int idx = 0;


    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    EntryNewScreen(SRC_QINYI_LOGIN_APP, ExitQinYListWindow, EntryQinYiLoginEx, NULL);
    InitializeCategory57Screen();

    guiBuffer = GetCurrGuiBuffer(SRC_QINYI_LOGIN_APP);
    inputBuffer = GetCurrNInputBuffer(SRC_QINYI_LOGIN_APP, &inputBufferSize);

    RegisterHighlightHandler(QyListWndSetHilt);
    
    /* Login Name */
    ADD_CAPTION_ITEM(((U16*)"\x7B\x76\x55\x5F\x28\x75\x37\x62\xD\x54\x0\x0") /*L"登录用户名"*/);
    ADD_CAPTION_ITEM((PU8)g_QinYi_UserName);    
    /* Login password */
    ADD_CAPTION_ITEM(((U16*)"\xC6\x5B\x1\x78\x0\x0") /*L"密码"*/);
    ADD_EDIT_ITEM( (PU8) g_QinYi_User_Pswd, QY_PSWD_MAX_LEN, IMM_INPUT_TYPE_NUMERIC_PASSWORD);

    if (inputBuffer != NULL)
    {
        SetCategory57Data(wgui_inline_items, idx, inputBuffer);
    }

  //  DisableCategory57ScreenDone();

    ShowCategory57Screen_ex(
        (U8*) (((U16*)"\x7B\x76\x55\x5F\x0\x0") /*L"登录"*/),
        0,
        QY_RES(STR_GLOBAL_OK),
        QY_RES(IMG_GLOBAL_OK),
        QY_RES(STR_GLOBAL_BACK),
        QY_RES(IMG_GLOBAL_BACK),
        idx,
        NULL,
        wgui_inline_items,
        idx-1,
        guiBuffer);

    SetCategory57RightSoftkeyFunctions(QY_LoginCheck, GoBackHistory);
    

}

void EntryQinYiLogin(int bServerAuthen)
{
    switch(LoadUserAndPwd())
    {
    case ERR_NOT_AUTHENT:
        g_bQyAuthenticate = SERVER_AUTH;
        break;
    case QY_SUCCESS:
        g_bQyAuthenticate = bServerAuthen;
        break;
    case QY_ERROR:
        DisplayPopup((PU8)(((U16*)"\xFB\x7C\xDF\x7E\xFA\x51\x19\x95\x0\x0") /*L"系统出错"*/), QY_RES(IMG_GLOBAL_ERROR), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
        return;
        break;
    }
    kal_wstrcpy(g_QinYi_UserName, g_SysUserInfo->name);
	memset( g_QinYi_User_Pswd, 0, QY_PSWD_MAX_LEN*2);
    
    EntryQinYiLoginEx();
}
    

#endif /* LOGIN_MODULE*/
/**************************************************************************************************
*      Module SignRecption 
*
**************************************************************************************************/
#ifdef SIGNRECPT_MODULE
//protype -------------------------------------------------------------------
typedef enum _QY_SIGN_RECPT_LIST_ITEM
{
    QY_SIGN_NAME_CAP,
    QY_SING_NAME,
    QY_SCAN_CAP,
    QY_BAR_CODE,
    QY_SEND_MENU,
    QY_SIGN_RECP_MAX
}QY_SIGN_RECPT_LIST_ITEM;


//Global -------------------------------------------------------------------
U16 g_SignRecptName[QY_USER_MAX_LEN+1];
U16 g_SignRecptCpat[3+4+5];
U16 g_RfBarCode[MAX_RDID_LEN+2];
TASK_HEADER  * g_pSignRecptTask  = NULL;
//Implemetion -------------------------------------------------------------------
#define IsValidCode()     IsValidCodeEx(__LINE__, g_RfBarCode)
#define RecheckCode(str)  IsValidCodeEx(__LINE__, str)

void LogFile (int ivk_line, U16 * code)
{
    U16 tmp[16];
    int fs_h  = OpenQyFile(QY_USER, L"Log.txt",FS_READ_WRITE);
    if( fs_h <= 0 ) fs_h  = OpenQyFile(QY_TMP, L"Log.txt",FS_READ_WRITE|FS_CREATE_ALWAYS);
    if( fs_h > 0  )
    {
        UINT wt;
        kal_wsprintf(tmp, "\r\n%d:\t", ivk_line );
        FS_Seek(fs_h, 0, FS_FILE_END);
        FS_Write(fs_h, tmp, kal_wstrlen(tmp)*2, &wt);
        FS_Write(fs_h, code,kal_wstrlen(code)*2, &wt);
        FS_Close(fs_h);
    }
}


int IsValidCodeEx(int line, U16 * pcode)
{
#if (VENDOR_NAME ==  VENDOR_MEIDA) || (VENDOR_NAME ==  VENDOR_NENGDA) //VENDOR_ZHONGTONG 
    int len  = kal_wstrlen(pcode);
    if( len >= 10 )
        return 1;
#elif VENDOR_NAME == VENDOR_ZHONGTONG 
    int i;
    for(i=0 ; i<15; i++)
    {
        if( pcode[i] == 0 )
        {
            break;
        }
        else if( pcode[i]>= '0' && pcode[i] <='9' )
        {
             
        }
        else 
        {
            if( (i != 9 ) || ( pcode[i]< 'A' || pcode[i] > 'Z' ) )
            {
                LogFile( line, pcode);
                kal_prompt_trace(MOD_MMI, "scan wrong %w", pcode);
                return 0;
            }
        }
    }
    kal_prompt_trace(MOD_MMI, "scan len %d", i);
    if( i== 10 || i ==12 || i==13 )
        return 1;
#endif
    return 0;
}

static U8 ExitQinYnSignRecpt(void * p) 
{
    if( g_pSignRecptTask )
    {
        FreeTask(g_pSignRecptTask);
        g_pSignRecptTask = NULL;
    }
    return 0;
}

static void StoreSignRecptData(void)
{
    //YYYGGRRR QySendSignRecptCmd(g_SignRecptName,g_ScanTotal,g_QueuBars, QyOnSignRecptAck);
	QY_RDID * prdid = (QY_RDID *)g_pSignRecptTask->pRdId;
    SetTaskJunor(g_pSignRecptTask, g_SignRecptName, QY_USER_MAX_LEN);
    mmi_asc_n_to_wcs(g_pSignRecptTask->taskname, (S8*)prdid[0].LaserId, MAX_RDID_LEN+1);////**??**//
    if( SaveTask(g_pSignRecptTask, NULL) >= 0  )
    {
        U16 srcid = GetActiveScreenId();
        DisplayPopup((PU8)((U16*)"\xD1\x53\x1\x90\x10\x62\x9F\x52\x0\x0") /*L"发送成功"*/, QY_RES(IMG_GLOBAL_SUCCESS), 1, UI_POPUP_NOTIFYDURATION_TIME, 0);
        DeleteScreenIfPresent(srcid);
        ExitQinYnSignRecpt(NULL);
        StartQyAsySendThread();
        //StartTimer(EXIT_WINDOW_TIMER, UI_POPUP_NOTIFYDURATION_TIME, GoBackHistory);
    }
    else
    {
        DisplayPopup((PU8)((U16*)"\x85\x51\x58\x5B\xD\x4E\xB3\x8D\x2C\x0\xD1\x53\x1\x90\x31\x59\x25\x8D\x0\x0") /*L"内存不足,发送失败"*/, QY_RES(IMG_GLOBAL_SAVE), 1, UI_POPUP_NOTIFYDURATION_TIME, 0);
		RedrawCategory57Screen();//dm_redraw_category_screen();
    }
}

static void QySignRecptCheck(void)
{
     if( currentHighlightIndex == QY_BAR_CODE )
     {
        if( IsValidCode()  )
        {
            kal_wsprintf(g_SignRecptCpat,"%w:%d",((U16*)"\x6B\x62\xCF\x63\x0\x0") /*L"扫描"*/, g_pSignRecptTask->totals);
            RedrawCategory57Screen();//dm_redraw_category_screen();
        }
     }
     if(currentHighlightIndex == QY_SIGN_RECP_MAX)
     {
        StoreSignRecptData();
     }
}

static void QySignReccpExit(void)
{
    if((g_pSignRecptTask&&g_pSignRecptTask->totals) || g_RfBarCode[0] || g_SignRecptName[0])
    {
        ConfirmExitWithSave();
    }
    else
    {
        GoBackHistory();
    }
}

static int  AddSignBarCode(void)
{
    int ret = QY_ERROR;
    if( IsValidCode() && (g_pSignRecptTask->totals < QY_MAX_BARS) )
    {
        ret = AppendRdId(g_pSignRecptTask, g_RfBarCode);
        kal_wsprintf(g_SignRecptCpat,"%w:%d/%d",((U16*)"\x6B\x62\xCF\x63\x0\x0") /*L"扫描"*/, g_pSignRecptTask->totals, QY_MAX_BARS);
		RedrawCategory57Screen();//dm_redraw_category_screen();
        //inline_fixed_list_goto_item(3, MMI_FALSE);
        //gdi_lcd_repaint_all();
    }
    return ret;
}
static void OnEnteryKeyInSignWnd(void)
{
    //handle_inline_text_edit_complete();
    wgui_update_inline_data();
    AddSignBarCode();
}

void OnQySignScanCode(U16 * pstrCode)
{
    int toneid = BATTERY_WARNING_TONE ;
    kal_prompt_trace(MOD_MMI,"OnQySignScanCode" );        
    kal_wstrncpy(g_RfBarCode, pstrCode, (MAX_RDID_LEN+1));
    if( AddSignBarCode() >= QY_SUCCESS )
    {
        toneid = ERROR_TONE;
    }
    
    playRequestedTone(toneid);
}

void SetSignRecptHighlightIndex(S32 nIndex)
{
    int bShow = 0;
    SetHighlightIndex(nIndex);
    if( nIndex == QY_SEND_MENU)
    {
        if( g_SignRecptName[0] )//&& g_SignRecptName[1] )
        {
            if(g_pSignRecptTask->totals)
            {
                bShow = 1;
            }
        }
        
        if ( bShow == 0 )
        {
            ClearKeyHandler(KEY_LSK, KEY_EVENT_UP);
            SetLeftSoftkeyFunction(QySignRecptCheck, KEY_EVENT_UP);
            ChangeLeftSoftkey(0, 0);
        }
        else
        {
            ChangeLeftSoftkey(QY_RES(STR_GLOBAL_OK), QY_RES(IMG_GLOBAL_OK));
            SetLeftSoftkeyFunction(StoreSignRecptData, KEY_EVENT_UP);
        }
    }
    else if( nIndex == QY_BAR_CODE  )
    {
        //
       SetLeftSoftkeyFunction(QySignRecptCheck, KEY_EVENT_UP);
       ClearKeyHandler(KEY_ENTER, KEY_EVENT_DOWN);
       SetKeyHandler(OnEnteryKeyInSignWnd, KEY_ENTER, KEY_EVENT_UP);
        
    }
    UpdateStatusIcons();    
    SetDefaultScanKeyHandlers();
    
}
void EntryQinYiSignRecptEx(void) 
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    U8 *guiBuffer;
    U8 *inputBuffer;
    U16 inputBufferSize;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    EntryNewScreen(SRC_QINYI_SIGN_APP, ExitQinYListWindow, EntryQinYiSignRecptEx, NULL);
    InitializeCategory57Screen();

    guiBuffer = GetCurrGuiBuffer(SRC_QINYI_SIGN_APP);
    inputBuffer = GetCurrNInputBuffer(SRC_QINYI_SIGN_APP, &inputBufferSize);

    RegisterHighlightHandler(SetSignRecptHighlightIndex);

    /*  Name */
    SetInlineItemActivation(&wgui_inline_items[QY_SIGN_NAME_CAP], INLINE_ITEM_ACTIVATE_WITHOUT_KEY_EVENT, 0);
    SetInlineItemCaption(&(wgui_inline_items[QY_SIGN_NAME_CAP]), (U8*) (((U16*)"\x7E\x7B\x36\x65\xBA\x4E\xD3\x59\xD\x54\x0\x0") /*L"签收人姓名"*/));

    SetInlineItemActivation(&wgui_inline_items[QY_SING_NAME], INLINE_ITEM_ACTIVATE_WITHOUT_KEY_EVENT, 0);
    SetInlineItemTextEdit( &wgui_inline_items[QY_SING_NAME],  (PU8)g_SignRecptName, QY_USER_MAX_LEN-1, IMM_INPUT_TYPE_SENTENCE);

    /* RDID code */
    kal_wsprintf(g_SignRecptCpat,"%w:%d/%d",((U16*)"\x6B\x62\xCF\x63\x0\x0") /*L"扫描"*/, g_pSignRecptTask->totals, QY_MAX_BARS);
    SetInlineItemActivation(&wgui_inline_items[QY_SCAN_CAP], INLINE_ITEM_ACTIVATE_WITHOUT_KEY_EVENT, 0);
    SetInlineItemCaption(&(wgui_inline_items[QY_SCAN_CAP]), (U8*)g_SignRecptCpat );

    SetInlineItemActivation(&wgui_inline_items[QY_BAR_CODE], INLINE_ITEM_ACTIVATE_WITHOUT_KEY_EVENT, 0);
    SetInlineItemTextEdit(&wgui_inline_items[QY_BAR_CODE], (PU8)g_RfBarCode, MAX_RDID_LEN+1, IMM_INPUT_TYPE_NUMERIC);

    SetInlineItemActivation(&(wgui_inline_items[QY_SEND_MENU]), INLINE_ITEM_ACTIVATE_WITHOUT_KEY_EVENT, 0);
    SetInlineItemDisplayOnly(&(wgui_inline_items[QY_SEND_MENU]), (U8*)((U16*)"\xD1\x53\x1\x90\x70\x65\x6E\x63\x0\x0") /*L"发送数据"*/);


    if (inputBuffer != NULL)
    {
        SetCategory57Data(wgui_inline_items, QY_SIGN_RECP_MAX, inputBuffer);
    }

    DisableCategory57ScreenDone();

    ShowCategory57Screen_ex(
        (U8*) (((U16*)"\x7E\x7B\x36\x65\x0\x0") /*L"签收"*/),
        0,
        QY_RES(STR_GLOBAL_OK),
        QY_RES(IMG_GLOBAL_OK),
        QY_RES(STR_GLOBAL_BACK),
        QY_RES(IMG_GLOBAL_BACK),
        QY_SIGN_RECP_MAX,
        NULL,
        wgui_inline_items,
        0,
        guiBuffer);

    SetConfirmExitAbortion(ExitQinYnSignRecpt);
    SetCategory57LeftSoftkeyFunction(QySignRecptCheck);
    SetCategory57RightSoftkeyFunctions(QySignRecptCheck, QySignReccpExit);
    SetKeyHandler(QySignReccpExit, KEY_END, KEY_EVENT_DOWN);

    QinYiSetScanHandle(OnQySignScanCode);


    //Init Scan Engieen and regist key handle
    SetDelScrnIDCallbackHandler(SRC_QINYI_SIGN_APP, ExitQinYnSignRecpt );

}

void EntryQinYiSignRecpt(void) 
{
    FuncQyCheckHeap();
    
    memset(g_RfBarCode,  0, sizeof(U16)*(MAX_RDID_LEN+2)  );
    memset(g_SignRecptName,0, QY_USER_MAX_LEN*2 );
    ExitQinYnSignRecpt(NULL);
    
    g_pSignRecptTask= CreateTask(QYF_SIGN, 0);
    EntryQinYiSignRecptEx();
}
///////////////////////////////////////////////////////////////////////////
void FreeDump(void );
int  DumpTaskIndexList(QYFILE_TYPE ftype);
void QinYiOptResendEntry(void);
extern QY_ALL_TASKINFO * g_TaskDump;

int g_OptSel4Resend, g_OptListCnt;

U8  g_titleResend[] =  {("\x49\x7B\x85\x5F\xD1\x53\x1\x90\x0\x0" /*L"等待发送"*/)};
U8  g_DumpType = 0;
U8  g_SendTaskMode;
U16 g_SrcIdBeforeList;


void QueueTaskdMenuExit(void)
{
    FreeDump();
    ResumeQyAsySendThread();    
}

int QueueTaskdMenuSel(S32 sel)
{
    g_OptSel4Resend = sel;
    QinYiOptResendEntry();        
    return 0;
}


void ShowQueueTaskEntry(void)
{
    if( g_DumpType  && g_DumpType < QYF_MAX_TYPE)
    {
        g_SrcIdBeforeList = GetActiveScreenId();
        SuspendQyAsySendThread();
		g_OptListCnt = ( g_TaskDump  ) ? g_TaskDump->Totls : 0;

        DumpTaskIndexList(g_DumpType); //
        ShowQinYiMenu(g_titleResend,g_TaskDump->TitlePtr,NULL,g_TaskDump->Totls,QueueTaskdMenuSel, QueueTaskdMenuExit);
        set_left_softkey_label(get_string(QY_RES(STR_GLOBAL_OPTIONS)));
        set_left_softkey_icon(get_image(QY_RES(IMG_GLOBAL_OPTIONS)));  
        RedrawListCategoryScreen();
    }
    
}
#endif /*SIGNRECPT_MODULE*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Show detail of diffent task
#ifdef TASK_DETAIL_MODULE

WSTR  g_pTaskTotal = NULL;
WSTR  g_pWaterNum  = NULL;
WSTR  g_pTaskTime  = NULL;
WSTR  g_pWaitTitle = NULL;
TASK_HEADER * g_pDeailTask = NULL ;
extern const int g_cmdReqAck[];
extern WSTR g_newBillDetal[MAX_NEW_BILL_ITEM];

int TaskSendDone(int ret)
{
    if( ret > 0 )
    {
        int cmd, err,field;
        void * hack = GetAckHandle(&cmd, &err,&field, NULL);
        FreeAckHandle(hack);

        if( cmd == g_cmdReqAck[(g_DumpType &QYF_FILE_MASK)-1] 
            || ( cmd ==CMD_NOORDER_BILL && (g_DumpType &QYF_FILE_MASK) == QYF_RECIVE) )
        {
            if( err == 0)
            {
                    
                DeleleTask(g_DumpType, g_OptSel4Resend);
                if( g_SendTaskMode == 0 ||  SendNextTask() == 0)
                {
                    //DeleteBetweenScreen(g_SrcIdBeforeList, GetCurrScrnId());
                    GoBackToHistory(g_SrcIdBeforeList);
                    g_DumpType = QYF_RECIVE;
                    ShowQueueTaskEntry();
                    
                }
            }
            else
            {
                DisplayPopup((PU8)QureyErrorString(err), QY_RES(IMG_GLOBAL_ERROR), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
                ClearAllKeyHandler();
            }
        }
        else
        {
            DisplayPopup((PU8)(((U16*)"\x1A\x90\xAF\x8B\x31\x59\x25\x8D\x0\x0") /*L"通讯失败"*/), QY_RES(IMG_GLOBAL_ERROR), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
            ClearAllKeyHandler();
        }        
    }
    else
    {
        DisplayPopup((PU8)(((U16*)"\x1A\x90\xAF\x8B\x31\x59\x25\x8D\x0\x0") /*L"通讯失败"*/), 
            QY_RES(IMG_GLOBAL_ERROR), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
        ClearAllKeyHandler();
    }
    return 1;
}

void OnConfirmSendTask(void)
{
    if( g_pDeailTask ) 
    {
        if( SendTask(g_pDeailTask, 1, TaskSendDone) )
        {
            PopupWait((PU8)("\xDE\x8F\xA5\x63\xD\x67\xA1\x52\x68\x56\x2E\x0\x2E\x0\x2E\x0\x0\x0") /*L"连接服务器..."*/, QY_RES(IMG_GLOBAL_PROGRESS), 1,(U32) -1, 0);
            //EntryQYLoginProcess();            
        }
        else
        {
            DisplayPopup((PU8)("\xDE\x8F\xA5\x63\x31\x59\x25\x8D\x0\x0") /*L"连接失败"*/, QY_RES(IMG_GLOBAL_ERROR), 1, (U32) -1, 0);
        }
            
    }
}
#define RELEASE_HANDLE(h)  if(h){QyFree(h), h = NULL;}
    
U8 ExitTaskDetalListWindow(void * p)
{
    if( g_pDeailTask ) 
    {
        FreeTask(g_pDeailTask); g_pDeailTask = NULL;
    }

    RELEASE_HANDLE( g_pTaskTotal);
    RELEASE_HANDLE( g_pWaterNum );    
    RELEASE_HANDLE( g_pTaskTime );
    RELEASE_HANDLE( g_pWaitTitle );
    
	return 0;
}

int FillReciveJunorItem(int idx)
{
    WSTR pDetail;
    BILL_PREP_TBL * pJunor;
    BILL_PROPERTY * pPrep; 
    pJunor = (BILL_PREP_TBL*)g_pDeailTask->pJunor; 
    pPrep  = (BILL_PROPERTY *)g_pDeailTask->pRdId;

    pDetail = (WSTR)pJunor->prep;
    mmi_asc_n_to_wcs(g_RfBarCode,(S8*)pPrep->Barcode, MAX_RDID_LEN+1);
    g_RfBarCode[MAX_RDID_LEN] = 0;
    
    if( pJunor->type == (QYF_RECIVE | QYF_ACCEPT) )
    {
        int i;
        kal_wsprintf(g_pTaskTotal, "%w(%d)", ((U16*)"\x9\x67\xA2\x8B\x55\x53\xD0\x8F\x55\x53\x0\x0") /*L"有订单运单"*/, pJunor->Total);
        for(i=0; i<MAX_NEW_BILL_ITEM;i++)
        {
            g_newBillDetal[i] = pDetail;
            pDetail += kal_wstrlen(pDetail)+1;
        }
        kal_wstrncpy(g_pWaitTitle,g_newBillDetal[NB_SEND_NAME], 16);
        ADD_TEXT_ITEM( g_pTaskTotal );
        ADD_TEXT_ITEM( g_RfBarCode );
        ADD_TEXT_ITEM( g_newBillDetal[NB_SEND_NAME] );
        ADD_TEXT_ITEM( g_newBillDetal[NB_SEND_ADDR] );
        ADD_TEXT_ITEM( g_newBillDetal[NB_SEND_PHONE] );
        ADD_TEXT_ITEM( g_newBillDetal[NB_GUID] );
        if( pPrep->water != (UINT)-1 )
        {
            if( g_pWaterNum == NULL ) g_pWaterNum = QyMalloc(32*sizeof(U16));
            ADD_CAPTION_ITEM( ((U16*)"\x41\x6D\x34\x6C\xF7\x53\x0\x0") /*L"流水号"*/);
            kal_wsprintf(g_pWaterNum, "%d",pPrep->water);
            ADD_TEXT_ITEM(g_pWaterNum );

        }
    }
    else if( pJunor->type == (QYF_RECIVE | QYF_CREATE) )
    {
        kal_wstrncpy(g_pWaitTitle,((U16*)"\xE0\x65\xA2\x8B\x55\x53\xD0\x8F\x55\x53\x0\x0") /*L"无订单运单"*/, 16);

        kal_wsprintf(g_pTaskTotal, "%w(%d)",((U16*)"\xD0\x8F\x55\x53\x0\x0") /*L"运单"*/, pJunor->Total);
        ADD_TEXT_ITEM( g_pTaskTotal);
        ADD_TEXT_ITEM( g_RfBarCode );
        ADD_CAPTION_ITEM( ((U16*)"\xA2\x5B\x37\x62\x16\x7F\xF7\x53\x0\x0") /*L"客户编号"*/);
        ADD_TEXT_ITEM( g_pDeailTask->taskname );
        
    }

    
    kal_wsprintf(g_pTaskTime,"%d.%02d/%02d-%02d:%02d:%02d",
        g_pDeailTask->GenTime.nYear, g_pDeailTask->GenTime.nMonth, g_pDeailTask->GenTime.nDay,
        g_pDeailTask->GenTime.nHour, g_pDeailTask->GenTime.nMin,  g_pDeailTask->GenTime.nSec);

    ADD_TEXT_ITEM(g_pTaskTime);
    return idx;
}

int FillSignJunorItem(int idx)
{
    SIGN_JUNOR * pJunor;
    
    kal_wstrncpy(g_pWaitTitle,((U16*)"\x7E\x7B\x36\x65\x0\x0") /*L"签收"*/, 16);

    pJunor = (SIGN_JUNOR*)g_pDeailTask->pJunor; 
    kal_wsprintf(g_pTaskTotal, "%w(%d)",((U16*)"\xD0\x8F\x55\x53\x70\x65\x0\x0") /*L"运单数"*/, g_pDeailTask->totals);
    
    ADD_CAPTION_ITEM( ((U16*)"\x7E\x7B\x36\x65\xBA\x4E\xD3\x59\xD\x54\x0\x0") /*L"签收人姓名"*/);
    ADD_TEXT_ITEM( pJunor->name );
    ADD_CAPTION_ITEM(g_pTaskTotal);
    ADD_TEXT_ITEM( g_pDeailTask->taskname );
    
    kal_wsprintf(g_pTaskTime,"%d.%02d/%02d-%02d:%02d:%02d",
        g_pDeailTask->GenTime.nYear, g_pDeailTask->GenTime.nMonth, g_pDeailTask->GenTime.nDay,
        g_pDeailTask->GenTime.nHour, g_pDeailTask->GenTime.nMin,  g_pDeailTask->GenTime.nSec);

    ADD_TEXT_ITEM(g_pTaskTime);
    return idx;


}

extern U8 * GetProblemTextByIndex(int index);
int FillProblemJunorItem(int idx)
{
    S32 ProblemIndex = 0;
    U16 * pProblemText ;
    PROBLEM_JOUNOR * pJunor= (PROBLEM_JOUNOR*)g_pDeailTask->pJunor; 
    kal_wstrncpy(g_pWaitTitle,((U16*)"\xEE\x95\x98\x98\xF6\x4E\x0\x0") /*L"问题件"*/, 16);
    
    ADD_CAPTION_ITEM(  ((U16*)"\xEE\x95\x98\x98\xF6\x4E\x7B\x7C\x8B\x57\x0\x0") /*L"问题件类型"*/);
    //ADD_TEXT_ITEM( pJunor->ProblemID );
    mmi_ucs2toi((S8*)pJunor->ProblemID, (S32*)&ProblemIndex, NULL);

    if(ProblemIndex && (pProblemText =  (U16*)GetProblemTextByIndex(ProblemIndex-1) ) != NULL)
        ADD_TEXT_ITEM( pProblemText );

    kal_wsprintf(g_pTaskTotal, "%w(%d)",((U16*)"\xD0\x8F\x55\x53\x70\x65\x0\x0") /*L"运单数"*/, g_pDeailTask->totals);
    
    ADD_CAPTION_ITEM(g_pTaskTotal);
    ADD_TEXT_ITEM( g_pDeailTask->taskname );
    
    kal_wsprintf(g_pTaskTime,"%d.%02d/%02d-%02d:%02d:%02d",
        g_pDeailTask->GenTime.nYear, g_pDeailTask->GenTime.nMonth, g_pDeailTask->GenTime.nDay,
        g_pDeailTask->GenTime.nHour, g_pDeailTask->GenTime.nMin,  g_pDeailTask->GenTime.nSec);
    ADD_TEXT_ITEM(pJunor->strOther);

    ADD_TEXT_ITEM(g_pTaskTime);
    return idx;
}

int FillJunorItem(int idx)
{
    switch(g_DumpType)
    {
    case QYF_RECIVE:
        idx = FillReciveJunorItem(idx);
        break;
    case QYF_SIGN: 
        idx = FillSignJunorItem(idx);
        break;
    case QYF_PROBLEM:
        idx = FillProblemJunorItem(idx);
        break;
    }
    return idx;
}

void TaskDetalHighlightIndex(S32 nIndex)
{
    if( nIndex == 0 )
    {
        ChangeLeftSoftkey(QY_RES(STR_GLOBAL_OK), QY_RES(IMG_GLOBAL_OK));
        SetLeftSoftkeyFunction(OnConfirmSendTask, KEY_EVENT_UP);
    }
    else
    {
        ClearKeyHandler(KEY_LSK, KEY_EVENT_UP);
        ChangeLeftSoftkey(0, 0);
    }
   
}
void ShowTaskDetal(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    U8 *guiBuffer;
    U8 *inputBuffer;
    U16 inputBufferSize;
    int idx = 0;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    EntryNewScreen(SRC_SHOW_TASK_APP, ExitQinYListWindow, ShowTaskDetal, NULL);
    InitializeCategory57Screen();

    guiBuffer = GetCurrGuiBuffer(SRC_SHOW_TASK_APP);
    inputBuffer = GetCurrNInputBuffer(SRC_SHOW_TASK_APP, &inputBufferSize);

    RegisterHighlightHandler(TaskDetalHighlightIndex);

    /*  Name */
    ADD_TEXT_ITEM( ((U16*)"\xD1\x53\x1\x90\x70\x65\x6E\x63\x0\x0") /*L"发送数据"*/);

    idx = FillJunorItem(idx);
    

    if (inputBuffer != NULL)
    {
        SetCategory57Data(wgui_inline_items, idx, inputBuffer);
    }

    DisableCategory57ScreenDone();

    ShowCategory57Screen_ex(
        (U8*) g_pWaitTitle,
        0,
        QY_RES(STR_GLOBAL_OK),
        QY_RES(IMG_GLOBAL_OK),
        QY_RES(STR_GLOBAL_BACK),
        QY_RES(IMG_GLOBAL_BACK),
        idx,
        NULL,
        wgui_inline_items,
        0,
        guiBuffer);

    SetCategory57LeftSoftkeyFunction(OnConfirmSendTask);
    SetCategory57RightSoftkeyFunctions(OnConfirmSendTask, GoBackHistory);
    SetDelScrnIDCallbackHandler(SRC_SHOW_TASK_APP, ExitTaskDetalListWindow );
    
    //Init Scan Engieen and regist key handle
}

int SendNextTask(void)
{
    if( g_TaskDump->Totls )
    {
        ExitTaskDetalListWindow(NULL);
        g_pDeailTask = LoadTask(g_DumpType, 0);
        if (g_pDeailTask == NULL)
        {
            DisplayPopup((PU8)((U16*)"\x53\x62\x0\x5F\xFB\x4E\xA1\x52\x55\x53\x31\x59\x25\x8D\x0\x0") /*L"打开任务单失败"*/, QY_RES(IMG_GLOBAL_ERROR), 1, UI_POPUP_NOTIFYDURATION_TIME, 0);
        }
        else
        {        
            SendTask(g_pDeailTask, 1, TaskSendDone);
        }
    }
    return g_TaskDump->Totls;

}

void ShowTaskEntry( int bNotShowDetail)
{
    ExitTaskDetalListWindow(NULL);
    g_pDeailTask  = LoadTask(g_DumpType, g_OptSel4Resend);
    g_pTaskTotal  = QyMalloc(sizeof(U16)*16);
	g_pTaskTime   = QyMalloc(24*2);
    g_pWaitTitle  = QyMalloc(32);
    
    if (g_pDeailTask == NULL)
    {
        DisplayPopup((PU8)((U16*)"\x53\x62\x0\x5F\xFB\x4E\xA1\x52\x55\x53\x31\x59\x25\x8D\x0\x0") /*L"打开任务单失败"*/, QY_RES(IMG_GLOBAL_ERROR), 1, UI_POPUP_NOTIFYDURATION_TIME, 0);
    }
    else
    {        
        if( bNotShowDetail )
            OnConfirmSendTask();
        else
            ShowTaskDetal();            
    }
}

#endif 
////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef PROGLEM_MODULE
TASK_HEADER  * g_pProblemTask  = NULL;
int g_ProblemMenuSel;
U16 * g_pOtherProblem;

void SendProblemTask(void)
{
	QY_RDID * prdid = (QY_RDID *)g_pProblemTask->pRdId;
    PROBLEM_JOUNOR prob_jounor;
#ifndef MULTI_PROBLEM_SUPPORT               
        if( g_RfBarCode[0] && kal_wstrlen(g_RfBarCode) >= 6 )
        {
            AppendRdId(g_pProblemTask, g_RfBarCode);
        }
        else
            return;
#endif 
    
    kal_wstrcpy(prob_jounor.ProblemID,g_SignRecptName);
    kal_wstrcpy(prob_jounor.strOther, g_pOtherProblem);
    SetTaskJunor(g_pProblemTask, &prob_jounor, 
        offsetof(PROBLEM_JOUNOR,strOther) + (kal_wstrlen(prob_jounor.strOther)*2 + 2));
    mmi_asc_n_to_wcs(g_pProblemTask->taskname, (S8*)prdid[0].LaserId, MAX_RDID_LEN+1);////**??**//    
    if( SaveTask(g_pProblemTask, NULL) >= 0  )
    {
        U16 srcid = GetActiveScreenId();
        DisplayPopup((PU8)((U16*)"\xD1\x53\x1\x90\x10\x62\x9F\x52\x0\x0") /*L"发送成功"*/, 
            QY_RES(IMG_GLOBAL_SUCCESS), 1, UI_POPUP_NOTIFYDURATION_TIME, 0);
        DeleteScreenIfPresent(srcid);
        ExitQinYnSignRecpt(NULL);
        StartQyAsySendThread();
        //StartTimer(EXIT_WINDOW_TIMER, UI_POPUP_NOTIFYDURATION_TIME, GoBackHistory);
    }
    else
    {
        DisplayPopup((PU8)((U16*)"\x85\x51\x58\x5B\xD\x4E\xB3\x8D\x2C\x0\xD1\x53\x1\x90\x31\x59\x25\x8D\x0\x0") /*L"内存不足,发送失败"*/, QY_RES(IMG_GLOBAL_SAVE), 1, UI_POPUP_NOTIFYDURATION_TIME, 0);
		RedrawCategory57Screen();//dm_redraw_category_screen();
    }
}

void OnOkkeyProblemWind(void)
{
    
    if( g_ProblemMenuSel > 4 )
    {
        kal_wsprintf(g_SignRecptName,"%d", g_ProblemMenuSel - 4);
        RedrawCategory57Screen();//dm_redraw_category_screen();
    }
    else if( g_ProblemMenuSel == 0 )
    {
#ifndef MULTI_PROBLEM_SUPPORT               
        if( g_RfBarCode[0] && kal_wstrlen(g_RfBarCode) >= 6 )
        {
            AppendRdId(g_pProblemTask, g_RfBarCode);
            SendProblemTask();        
        }
#else 
        SendProblemTask();        
#endif
    }
}


static int AddProblemBarCode(void)
{
    int ret =QY_ERROR;    
    if( IsValidCode() )
    {
        ret = AppendRdId(g_pProblemTask, g_RfBarCode);
        kal_wsprintf(g_SignRecptCpat,"%w:%d",((U16*)"\x6B\x62\xCF\x63\x0\x0") /*L"扫描"*/, g_pProblemTask->totals);
        RedrawCategory57Screen();//dm_redraw_category_screen();
    }
    return ret;
}


static void OnEnterKeyProblemWnd(void)
{
    wgui_update_inline_data();
    AddProblemBarCode();
}

void OnQyProblemScanCode(U16 * pstrCode)
{
    //int len = kal_wstrlen(pstrCode );
    int toneid = BATTERY_WARNING_TONE ;
    kal_prompt_trace(MOD_MMI,"OnQyProblemScanCode" );        
    kal_wstrncpy(g_RfBarCode, pstrCode, MAX_RDID_LEN+1);
#ifdef MULTI_PROBLEM_SUPPORT       
    if( AddProblemBarCode() >= QY_SUCCESS) 
#endif
    {
        RedrawCategory57Screen();//dm_redraw_category_screen();
        toneid = ERROR_TONE;
    }
    playRequestedTone(toneid);
}

void OnProblemHighlightIndex(int sel)
{
    g_ProblemMenuSel = sel;
    if( sel == 0 )
    {
        int bShow = 0;
        if( g_SignRecptName[0] )
        {
#ifndef MULTI_PROBLEM_SUPPORT               
            if( g_RfBarCode[0] && kal_wstrlen(g_RfBarCode) >= 6 )
#else            
            if(g_pProblemTask->totals)
#endif                
            {
                bShow = 1;
            }
        }
        
        if ( bShow == 0 )
        {
            ClearKeyHandler(KEY_LSK, KEY_EVENT_UP);
            SetLeftSoftkeyFunction(OnOkkeyProblemWind, KEY_EVENT_UP);
            ChangeLeftSoftkey(0, 0);
        }
        else
        {
            ChangeLeftSoftkey(QY_RES(STR_GLOBAL_OK), QY_RES(IMG_GLOBAL_OK));
            SetLeftSoftkeyFunction(SendProblemTask, KEY_EVENT_UP);
        }
    }
    else if( sel == 2 || sel == 1  )
    {
        SetLeftSoftkeyFunction(OnOkkeyProblemWind, KEY_EVENT_UP);
        ClearKeyHandler(KEY_ENTER, KEY_EVENT_DOWN);
        SetKeyHandler(OnEnterKeyProblemWnd, KEY_ENTER, KEY_EVENT_UP);
    }
    else
    {
        ChangeLeftSoftkey(QY_RES(STR_GLOBAL_OK), QY_RES(IMG_GLOBAL_OK));
        SetLeftSoftkeyFunction(OnOkkeyProblemWind, KEY_EVENT_UP);
    }
    UpdateStatusIcons();        
    SetDefaultScanKeyHandlers();
}

static void QyProblemExit(void)
{
    if(g_pProblemTask->totals || g_RfBarCode[0] || g_SignRecptName[0] )
    {
        ConfirmExitWithSave();
    }
    else
    {
        GoBackHistory();
    }
}


static U8 ExitQinYnProblem(void * p)
{
    if( g_pProblemTask )
    {
        FreeTask(g_pProblemTask);
        g_pProblemTask = NULL;
    }
    if( g_pOtherProblem )
    {
        QyFree(g_pOtherProblem);
        g_pOtherProblem = NULL;
    }
    return 0;
}

void QyPeoblemListEntry(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    U8 *guiBuffer;
    U8 *inputBuffer;
    U16 * pProblemText;
    U16 inputBufferSize;
    int idx = 0, i;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    EntryNewScreen(SRC_SHOW_TASK_APP, ExitQinYListWindow, QyPeoblemListEntry, NULL);
    InitializeCategory57Screen();

    guiBuffer = GetCurrGuiBuffer(SRC_SHOW_TASK_APP);
    inputBuffer = GetCurrNInputBuffer(SRC_SHOW_TASK_APP, &inputBufferSize);

    RegisterHighlightHandler(OnProblemHighlightIndex);

    /*  Name */
    ADD_TEXT_ITEM(((U16*)"\xD1\x53\x1\x90\x70\x65\x6E\x63\x0\x0") /*L"发送数据"*/);
#ifdef MULTI_PROBLEM_SUPPORT    
    kal_wsprintf(g_SignRecptCpat,"%w:%d",((U16*)"\x6B\x62\xCF\x63\x0\x0") /*L"扫描"*/, g_pProblemTask->totals);
#else
    kal_wsprintf(g_SignRecptCpat,"%w",((U16*)"\x6B\x62\xCF\x63\x0\x0") /*L"扫描"*/);
#endif
    ADD_CAPTION_ITEM( g_SignRecptCpat);
    ADD_EDIT_ITEM(g_RfBarCode,MAX_RDID_LEN,IMM_INPUT_TYPE_NUMERIC);    
    ADD_CAPTION_ITEM( ((U16*)"\xEE\x95\x98\x98\xF6\x4E\x7B\x7C\x8B\x57\x0\x0") /*L"问题件类型"*/);
    ADD_EDIT_ITEM(g_SignRecptName,2,IMM_INPUT_TYPE_NUMERIC);    
    for(i=0; (pProblemText=(U16 *)GetProblemTextByIndex(i))!= NULL; i++)
    {
        ADD_TEXT_ITEM(pProblemText);
    }
    ADD_CAPTION_ITEM( (((U16*)"\xEE\x95\x98\x98\xF6\x4E\x9F\x53\xE0\x56\x0\x0") /*L"问题件原因"*/));
    ADD_EDIT_ITEM(g_pOtherProblem,LEN_OTH_PROBLEM_TXT,IMM_INPUT_TYPE_SENTENCE);    
     
    if (inputBuffer != NULL)
    {
        SetCategory57Data(wgui_inline_items, idx, inputBuffer);
    }

    DisableCategory57ScreenDone();

    ShowCategory57Screen_ex(
        (U8*) ((U16*)"\xEE\x95\x98\x98\xF6\x4E\x0\x0") /*L"问题件"*/,
        0,
        QY_RES(STR_GLOBAL_OK),
        QY_RES(IMG_GLOBAL_OK),
        QY_RES(STR_GLOBAL_BACK),
        QY_RES(IMG_GLOBAL_BACK),
        idx,
        NULL,
        wgui_inline_items,
        0,
        guiBuffer);

    SetCategory57LeftSoftkeyFunction(OnOkkeyProblemWind);
    SetCategory57RightSoftkeyFunctions(OnOkkeyProblemWind, QyProblemExit);
    SetDelScrnIDCallbackHandler(SRC_SHOW_TASK_APP, ExitQinYnProblem );
    QinYiSetScanHandle(OnQyProblemScanCode);
    //Init Scan Engieen and regist key handle
}

void QyEntryProblemApp(void)
{
    memset(g_RfBarCode,  0, sizeof(U16)*(MAX_RDID_LEN+2)  );
    memset(g_SignRecptName,0, sizeof(U16)*QY_USER_MAX_LEN);
    ExitQinYnProblem(NULL);
    g_pOtherProblem = QyMalloc(LEN_OTH_PROBLEM_TXT*2);
    if( g_pOtherProblem  == NULL ) return;
    memset(g_pOtherProblem,0 ,LEN_OTH_PROBLEM_TXT*2);
    g_pProblemTask = CreateTask(QYF_PROBLEM, 0);
    QyPeoblemListEntry();
}

#endif  /*TASK_DETAIL_MODULE*/

////////////////////////////////////////////////////////////////////////////////////////list ///////////
//  QURERY window
#ifdef QUERY_EXPID_MODULE
void (*g_OnSendCmdDone)(NOB_ACK * nob_ack);
void OnUiCmdFinsh(NOB_ACK * nob_ack)
{
    if( g_OnSendCmdDone ) 
        g_OnSendCmdDone(nob_ack);
}

void PopupSendCmd(int (*FnxSendCmd)(void), void (*FnxFinshCmd)(NOB_ACK *), int timeout)
{
    if( FnxSendCmd && FnxSendCmd() == 0 ) 
        return;
    g_OnSendCmdDone = FnxFinshCmd;
    DisplayPopup((PU8)((U16*)"\xDE\x8F\xA5\x63\xD\x67\xA1\x52\x68\x56\x2E\x0\x2E\x0\x2E\x0\x0\x0") /*L"连接服务器..."*/,
        QY_RES(IMG_GLOBAL_PROGRESS), 1,(U32) -1, 0);
    DisableKeyEvent();    
    SetKeyHandler(OnPopopEndKey, KEY_END, KEY_EVENT_UP);
}


void QueryExpIdOnOkVoid(void); 

int QyStartQueryExpIdStatu(void)
{
    QueryStatuByExpId(g_RfBarCode);
    return 1;
}

U8 g_QureyExpIdStatuTitle[] = "\xD0\x8F\x55\x53\xB6\x72\x1\x60\xE5\x67\xE2\x8B\xD3\x7E\x9C\x67\x0\x0" /*L"运单状态查询结果"*/;
extern U16 *g_qy_display_info_str;

void OnQryExpIdStatusExit(void)
{
    if(g_qy_display_info_str)
        QyFree(g_qy_display_info_str);
    g_qy_display_info_str = NULL;
}

void QyOnExpIdStatuAck(NOB_ACK * pnob_ack)
{
    ClearAllKeyHandler();
    GoBackHistory();
    if( pnob_ack && pnob_ack->result > 0 && pnob_ack->err == 0 && pnob_ack->field> 4 )
    {
        U16 * pbuf = (U16 *)QyMalloc(pnob_ack->buflen);
        if( pbuf  ) 
        {
            int i;
            pbuf[0] =0 ;
            for( i=4; i<pnob_ack->field; i++)
            {
                U16 * ptr = GetFeild(pnob_ack->pbuf, 0,i) ;
                if( ptr[0] && kal_wstrcmp(ptr, L"null") != 0 )
                {
                    kal_wstrcat(pbuf, ptr);
                    kal_wstrcat(pbuf, L"\n");
                }
            }
            QyShowMessage((U16 *)g_QureyExpIdStatuTitle,pbuf, OnQryExpIdStatusExit);
        }
    }
}

void QueryExpIdHlt(int sel)
{
    if( sel == 2 )
    {
        int bShow = 0;
        if( g_RfBarCode[0] && g_RfBarCode[1] )
        {
            bShow = 1;
        }
        
        if ( bShow == 0 )
        {
            ClearKeyHandler(KEY_LSK, KEY_EVENT_UP);
            SetLeftSoftkeyFunction(QueryExpIdOnOkVoid, KEY_EVENT_UP);
            ChangeLeftSoftkey(0, 0);
        }
        else
        {
            ChangeLeftSoftkey(QY_RES(STR_GLOBAL_OK), QY_RES(IMG_GLOBAL_OK));
            SetLeftSoftkeyFunction(QueryExpIdOnOkVoid, KEY_EVENT_UP);
        }
    }

}

void QueryExpIdOnOkVoid(void)
{
    PopupSendCmd(QyStartQueryExpIdStatu, QyOnExpIdStatuAck, 60*1000);
}

int  QueryExpIdOnOk(int sel)
{
    if( sel == 3 )
    {
        QyStartQueryExpIdStatu();
    }
    return 1;
}

void QueryExpIdOnExit(void)
{
    QinYiCloseScanDev();
}

int  QueryExpIdConfirm(int val) 
{
    return 0;
}

void OnQyQueryExpIdStatusScanCode(U16 * pstrCode)
{
    //int len = kal_wstrlen(pstrCode );
    int toneid = BATTERY_WARNING_TONE ;
    kal_prompt_trace(MOD_MMI,"OnQyProblemScanCode" );        
    kal_wstrncpy(g_RfBarCode, pstrCode, MAX_RDID_LEN+1);
    RedrawCategory57Screen();//dm_redraw_category_screen();
    toneid = ERROR_TONE;

    playRequestedTone(toneid);
}

int  FillQueryExpid(int *pdef)
{
    int idx = 0;
    AddListItem(idx++, ((U16*)"\x6B\x62\xCF\x63\x2F\x0\x4B\x62\xA8\x52\x93\x8F\x65\x51\x55\x53\xF7\x53\x0\x0") /*L"扫描/手动输入单号"*/,0 ,-1);
    AddListItem(idx++,  g_RfBarCode, MAX_RDID_LEN ,IMM_INPUT_TYPE_NUMERIC);
    AddListItem(idx++, ((U16*)"\xE5\x67\xE2\x8B\x0\x0") /*L"查询"*/,0 ,-2);
    QinYiSetScanHandle(OnQyQueryExpIdStatusScanCode);
    return idx;
}


void QueryExpidEntry(void)
{
    ShowQinYiList(((U8*)"\xA2\x8B\x55\x53\xE5\x67\xE2\x8B\x0\x0") /*L"订单查询"*/, 
        FillQueryExpid,QueryExpIdHlt,QueryExpIdOnOk,QueryExpIdOnExit,QueryExpIdConfirm);
}

void QueryByExpid(void)
{
    //memcpy(g_RfBarCode, L"200867885052", sizeof(U16)*MAX_RDID_LEN);
    memset(g_RfBarCode, 0, sizeof(U16)*MAX_RDID_LEN);
    QueryExpidEntry();
}

#endif /*QUERY_EXPID_MODULE*/
/////////////////////////////////////////////////////////////////////////////////////
#ifdef RECEPT_NO_BILL_MOUDLE


MENU_TEXT g_strPayMethodTbl[]=
{
    "\xB0\x73\xD8\x4E\x0\x0" /*L"现付"*/
    "\x8\x67\xD3\x7E\x0\x0"  /*L"月结"*/
    "\x30\x52\xD8\x4E\x0\x0" /*L"到付"*/
};
#define STR_PAY_METHOD_MAX 3
U8 * g_strPayMethod[STR_PAY_METHOD_MAX];


U16 g_wait_sel;
U16 g_NewBillType;
U16 g_waitRectSrcId;
WSTR * g_NewBillStr;
U16 * g_NewBillPtr;
int g_BillTotal;
int g_BillNameTotal;
WSTR g_newBillDetal[MAX_NEW_BILL_ITEM];
WSTR g_RebackReson;
BILL_PREP_INPUT * g_BillPrepInput;
BILL_PREP_TBL  * g_BillPrepTbl;

void QyRecptApp(U16 BillType);
extern U8* g_strReception[];
extern U8* g_strWaitReply[];

void WaitRectMenu(void);

#endif /*RECEPT_NO_BILL_MOUDLE*/


int WaitRecepAck(int ret)
{
    NOB_ACK  ack_info;
    ack_info.pbuf = NULL;
    if( ret )
    {
            U16 caption[28];
        int imgid = QY_RES(IMG_GLOBAL_WARNING);
        ack_info.result = ret;
        GetAckHandleEx( &ack_info);
        
        if( ack_info.result != 0xFF )
        {
            U16 del_ways[] = {QYF_ACCEPT,QYF_REJECT,QYF_FWORD};
            DeleteNewBill(g_newBillDetal[NB_GUID],QYF_RECIVE ,del_ways[g_wait_sel]); // ?? not finish yet ?? //
            imgid = QY_RES(IMG_GLOBAL_SUCCESS);
            GoBackToHistory(g_waitRectSrcId);
            //DeleteUptoScrID(g_waitRectSrcId);
            QyRecptApp(g_NewBillType);
            kal_wsprintf( caption, "%w%w!",g_strWaitReply[g_wait_sel],((U16*)"\x10\x62\x9F\x52\x0\x0") /*L"成功"*/ );
        }
        else
        {
            kal_wsprintf( caption, "%w%w!",g_strWaitReply[g_wait_sel],((U16*)"\x31\x59\x25\x8D\x0\x0") /*L"失败"*/ );
        }
        DisplayPopup((PU8 )caption,imgid, 0, UI_POPUP_NOTIFYDURATION_TIME, 0);         //??//   
   }

    return 1;
}

void SendRecept(void)
{
    WSTR redraw_item[MAX_REDRAW_ITEM];
    U16 RedrawType[] = {L"0"};
    RedrawType[0] += g_wait_sel;
    redraw_item[RD_GUID] =  g_newBillDetal[NB_GUID];
    redraw_item[RD_TYPE] = RedrawType;
    redraw_item[RD_RESON] = g_RebackReson ?g_RebackReson  : g_SignRecptName ;
    redraw_item[RD_NO] = g_SignRecptName;
    SendRecptCmd(redraw_item, WaitRecepAck);
    DisplayPopup((PU8)((U16*)"\xDE\x8F\xA5\x63\xD\x67\xA1\x52\x68\x56\x2E\x0\x2E\x0\x2E\x0\x0\x0") /*L"连接服务器..."*/,
        QY_RES(IMG_GLOBAL_PROGRESS), 1,(U32) -1, 0);
    DisableKeyEvent();    
    SetKeyHandler(OnPopopEndKey, KEY_END, KEY_EVENT_UP);
    
    
}

int  FillWaitRecpt(int *pdef)
{
    int idx = 0;
    if( g_wait_sel == 1 )
    {
        AddListItem(idx++, ((U16*)"\xA4\x64\x0\x95\x9F\x53\xE0\x56\x0\x0") /*L"撤销原因"*/,0 ,QY_LIST_CAPTION);
        AddListItem(idx++, g_RebackReson, TEXT_MAX_LEN , IMM_INPUT_TYPE_SENTENCE);
        AddListItem(idx++,  ((U16*)"\xD1\x53\x1\x90\x0\x0") /*L"发送"*/,0 ,QY_LIST_TEXT);
    }
    else if( g_wait_sel == 2 )
    {
        AddListItem(idx++,  ((U16*)"\x6C\x8F\xD1\x53\x58\x54\xE5\x5D\x16\x7F\xF7\x53\x0\x0") /*L"转发员工编号"*/,0 ,QY_LIST_CAPTION);
        AddListItem(idx++,  g_SignRecptName, QY_USER_MAX_LEN ,IMM_INPUT_TYPE_NUMERIC_SYMBOL);
        AddListItem(idx++,  ((U16*)"\xD1\x53\x1\x90\x0\x0") /*L"发送"*/,0 ,QY_LIST_TEXT);
    }
    return idx;
}


int WaitRecptOnOk(int sel)
{
    int valid = 1;
    wgui_update_inline_data();
    if( g_wait_sel == 1 )
    {
        if( g_RebackReson == NULL )
        {
            GoBackHistory();
            return 1;
        }
        if(  kal_wstrlen(g_RebackReson) == 0 ) 
            valid = 0;
    }
    else if( (g_wait_sel == 2 ) &&  (kal_wstrlen(g_SignRecptName) == 0 ) )
    {
        valid = 0;
    }

    if( valid == 0 )
    {
        DisplayPopup((PU8)(((U16*)"\x93\x8F\x65\x51\xA4\x64\x0\x95\x9F\x53\xE0\x56\x16\x62\x6C\x8F\xD1\x53\x58\x54\xE5\x5D\x16\x7F\xF7\x53\x0\x0") /*L"输入撤销原因或转发员工编号"*/),
            QY_RES(IMG_GLOBAL_WARNING), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
    }
    else 
    {
        SendRecept();
    }
    return 0;
}

void CbWaitRecptOnOk(void)
{
    WaitRecptOnOk(0);
}


void WaitRecptOnExit(void)
{
    if( g_RebackReson )
    {
        QyFree(g_RebackReson);
        g_RebackReson = NULL;
    }
}

void WaitRecptHlt(int sel)
{
    ChangeLeftSoftkey(QY_RES(STR_GLOBAL_OK), QY_RES(IMG_GLOBAL_OK));
    SetLeftSoftkeyFunction(CbWaitRecptOnOk, KEY_EVENT_UP);
}

void WaitRecptEntry(void)
{
    WaitRecptOnExit();
    if( g_wait_sel )
    {
        memset(g_SignRecptName, 0 ,sizeof(U16)*( QY_USER_MAX_LEN+1));
        g_RebackReson =(WSTR) QyMalloc(TEXT_MAX_LEN*sizeof(U16));
        ShowQinYiList(((U8*)"\xE0\x65\xA2\x8B\x55\x53\x36\x65\xF6\x4E\x0\x0") /*L"无订单收件"*/,
            FillWaitRecpt,WaitRecptHlt,WaitRecptOnOk, WaitRecptOnExit, NULL);
        ChangeLeftSoftkey(QY_RES(STR_GLOBAL_OK), QY_RES(IMG_GLOBAL_OK));
        SetLeftSoftkeyFunction(CbWaitRecptOnOk, KEY_EVENT_UP);        
    }
    else
    {
        SendRecept();
    }
}
/*  */
#ifdef NEW_BILL_MODULE



//--- New Bill Wait Recpt ------------------------------------------------------------
void CbNewBillDetailOnOk(void);
void OnNewBillAddBar(U16 * pstrCode);
void OnNewBillDelBar(U16 * pstrCode);

typedef enum _NEWBILL_HLT_KEY_ITEM
{
    NBD_BAR_ADD,
    NBD_BAR_DEL,
    NBD_SEND,
    NBD_MAX_KEY_ITEM,
    NBD_COST,
    NBD_CLIENT_ID,
    NBD_WATER,
    NBD_INPUT_OK
}NEWBILL_HLT_KEY_ITEM;

BYTE g_NBHltKeyItems[NBD_MAX_KEY_ITEM];
static int g_hltNewBillDetail; 


int  NewBillDetailConfirm(int val) 
{
    ConfirmExitWithSave();
    return 1;
}

int  NewBillAceptOnOk(int sel)
{
    WaitRectMenu();
    return 0;
}

void NewBillAceptHlt(int sel)
{
    ChangeLeftSoftkey(QY_RES(STR_GLOBAL_OK), QY_RES(IMG_GLOBAL_OK));
    SetLeftSoftkeyFunction(CbNewBillDetailOnOk, KEY_EVENT_UP);
}

void NewBillDetailOnExit(void)
{
    if( g_BillPrepInput )
    {
        QyFree(g_BillPrepInput);
        g_BillPrepInput = NULL;
    }
    if( g_BillPrepTbl )
    {
        QyFree(g_BillPrepTbl);
        g_BillPrepTbl = NULL;
    }
}

UINT CalNewBillLen(WSTR * bill_deatil)
{
    UINT len = 0;
    int i;
    if( g_BillPrepTbl->type ==  (QYF_RECIVE|QYF_ACCEPT) )
    {
        for( i=0 ;i<MAX_NEW_BILL_ITEM;i++)
        {
            len += kal_wstrlen(bill_deatil[i])+1;
        }
    }
    return len*2;
}

UINT WriteBillJunor(int fsh , TASK_HEADER * ptask)
{
    UINT wt;
    UINT len, i, wten = 0;
    
    FS_Write(fsh, g_BillPrepTbl, offsetof(BILL_PREP_TBL, prep), &wt);
    wten += wt;

    if( g_BillPrepTbl->type ==  (QYF_RECIVE|QYF_ACCEPT) )
    {
        for( i=0 ;i<MAX_NEW_BILL_ITEM;i++)
        {
            len = kal_wstrlen(g_newBillDetal[i])+1;
            FS_Write(fsh, g_newBillDetal[i], len*2,&wt);
            wten += wt;
        } 
    }
    return wten;   
}

void SaveBill(BILL_PREP_TBL* bill_tbl,WSTR *bill_deatil)
{
    int ret = 0;
    UINT jurlen  = CalNewBillLen(g_newBillDetal);
    TASK_HEADER * ptask = CreateTask(QYF_RECIVE, -1 );
    ptask->LenJunor = jurlen + offsetof(BILL_PREP_TBL, prep);
    ptask->pRdId = &bill_tbl->prep[0];
    ptask->totals = g_BillPrepTbl->Total;
    ptask->MaxItms = ptask->totals;
    ptask->u.info.rdid_size = sizeof(BILL_PROPERTY);
    if( g_NewBillType == (QYF_RECIVE | QYF_ACCEPT ) )
        kal_wstrncpy(ptask->taskname,g_newBillDetal[NB_SEND_NAME], MAX_RDID_LEN);
    else
        kal_wstrncpy(ptask->taskname, ((U16*)"\xE0\x65\xA2\x8B\x55\x53\x36\x65\xF6\x4E\x0\x0") /*L"无订单收件"*/, MAX_RDID_LEN);
    ptask->taskname[MAX_RDID_LEN] = 0;

    ret = SaveTask(ptask, WriteBillJunor) ;
    if( ret == QY_SUCCESS )
    {
        if( g_NewBillType == (QYF_RECIVE | QYF_ACCEPT ) )
            DeleteNewBill(g_newBillDetal[NB_GUID],g_NewBillType ,QYF_SENT);
        GoBackToHistory(g_waitRectSrcId);
        QyRecptApp(g_NewBillType);
        DisplayPopup( (U8 *)((U16*)"\xDD\x4F\x58\x5B\x10\x62\x9F\x52\x0\x0") /*L"保存成功"*/,
            QY_RES(IMG_GLOBAL_SUCCESS), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
    }
        
    FreeTask(ptask);
        
}

void OnBillConfrimSend(int result)
{
    if( result == 1 )
    {
        g_BillPrepTbl->type = g_NewBillType;
        GetDateTime(&g_BillPrepTbl->gentime);        
        mmi_wcs_n_to_asc((S8*)g_BillPrepTbl->guid,g_BillPrepInput->ClientId,MAX_CLIENT_ID_LEN*2);
        g_BillPrepTbl->guid[MAX_GUID_LEN] = 0;
        
        SaveBill(g_BillPrepTbl,g_newBillDetal);        

    }
}

int CheckCurrency(U16 * pstr)
{
    int len = 0,  offset= 0;
    while( * pstr )
    {
        if( *pstr == '.' && offset == 0)
            offset = 1;
        else if( *pstr >'9' || *pstr < '0')  
        {
            return -3;
        }
        pstr++;
        len++;        
    }
    return 1;
}

int CheckNewBillInput(WSTR * title)
{
    if(0)// g_BillPrepInput->ClientId[0] == 0 ) 
    {
        if( title ) *title = ((U16*)"\xF7\x8B\x93\x8F\x65\x51\xA2\x5B\x37\x62\x16\x7F\xF7\x53\x0\x0") /*L"请输入客户编号"*/;
        return NBD_CLIENT_ID;
    }
    if( g_BillPrepInput->cost[0] == 0 )
    {
        if( title ) *title = ((U16*)"\xF7\x8B\x6B\x58\x99\x51\xD0\x8F\x39\x8D\x0\x0") /*L"请填写运费"*/;
        return NBD_COST;
    }

    if( CheckCurrency(g_BillPrepInput->cost) < 0 )
    {
        if( title ) *title = ((U16*)"\xF7\x8B\x63\x6B\x6E\x78\x6B\x58\x99\x51\xD0\x8F\x39\x8D\x0\x0") /*L"请正确填写运费"*/;
        return NBD_COST;
    }

    if( CheckCurrency(g_BillPrepInput->cash) < 0 )
    {
        if( title ) *title = ((U16*)"\xF7\x8B\x63\x6B\x6E\x78\x6B\x58\x99\x51\xE3\x4E\x36\x65\xD1\x91\x9D\x98\x0\x0") /*L"请正确填写代收金额"*/;
        return NBD_COST;
    }
    
    if( CheckCurrency(g_BillPrepInput->insurence) < 0 )
    {
        if( title ) *title = ((U16*)"\xF7\x8B\x63\x6B\x6E\x78\x6B\x58\x99\x51\xDD\x4F\xF7\x4E\xD1\x91\x9D\x98\x0\x0") /*L"请正确填写保价金额"*/;
        return NBD_COST;
    }
     
    if( (g_BillPrepInput->en_water )&& ( g_BillPrepInput->water[0] == 0 ) )
    {
        if( title ) *title = ((U16*)"\xF7\x8B\x93\x8F\x65\x51\x41\x6D\x34\x6C\xF7\x53\x0\x0") /*L"请输入流水号"*/;
        return NBD_WATER;
    }

    if( g_BillPrepTbl && g_BillPrepTbl->Total == 0 )
    {
        if( title ) *title = ((U16*)"\xD0\x8F\x55\x53\x3A\x4E\x7A\x7A\xC\xFF\xF7\x8B\x93\x8F\x65\x51\x2F\x0\x6B\x62\xCF\x63\xD0\x8F\x55\x53\xF7\x53\x0\x0") /*L"运单为空，请输入/扫描运单号"*/;
        return NBD_BAR_ADD;
    }

     return NBD_INPUT_OK;
    
}

void OnNewBillDetailSend(void)
{
    WSTR ptitle =NULL;
    if( g_BillPrepInput == NULL ) 
    {
        GoBackHistory( );
        return;
    }
    if( CheckNewBillInput(&ptitle) !=  NBD_INPUT_OK)
    {
        DisplayPopup( (U8 *)ptitle,QY_RES(IMG_GLOBAL_WARNING), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
    }
    else
    {
        ConfirmDialog(((U16*)"\x6E\x78\xA4\x8B\xD1\x53\x1\x90\x3F\x0\x0\x0") /*L"确认发送?"*/, OnBillConfrimSend);
    }
     
}

int NewBillDetailOnOk(int sel)
{
    if( g_hltNewBillDetail == g_NBHltKeyItems[NBD_SEND] )
    {
        OnNewBillDetailSend( );
    }
    else if(g_hltNewBillDetail == g_NBHltKeyItems[NBD_BAR_ADD])
    {
        wgui_update_inline_data();
        OnNewBillAddBar(g_BillPrepInput->barcode);
    }
    else if(g_hltNewBillDetail == g_NBHltKeyItems[NBD_BAR_DEL])
    {
        wgui_update_inline_data();
        OnNewBillDelBar(g_BillPrepInput->barcode);
    }
    return sel;
}

BILL_PROPERTY * InitBillPrepBar(WSTR scan_code, int bDel)
{
    int i;
    BYTE barcode[MAX_RDID_LEN+2] ;
    BILL_PROPERTY * bill_list = &g_BillPrepTbl->prep[g_BillPrepTbl->Total];
    if ( RecheckCode(scan_code) == 0 )
    {
        return NULL;
    }
    memset(barcode, 0 , MAX_RDID_LEN+1);
    mmi_wcs_n_to_asc((S8*)barcode,scan_code,MAX_RDID_LEN*2);
    bill_list = &g_BillPrepTbl->prep[0];
    for( i=0; i<g_BillPrepTbl->Total; i++)
    {
        if(memcmp( barcode, bill_list->Barcode, MAX_RDID_LEN) == 0 )
        {
            if( bDel )
                return bill_list;
            return NULL;
        }
        bill_list++;
    }
    if( bDel == 0 )
    {
        bill_list = &g_BillPrepTbl->prep[g_BillPrepTbl->Total];
        memcpy( bill_list->Barcode, barcode, MAX_RDID_LEN+1);
        bill_list->Barcode[MAX_RDID_LEN] = 0;
        return bill_list;
    }
    return NULL;
}

void AddPrepInfo(BILL_PROPERTY * bill_prep)
{
    S32 temp = -1;
    mmi_ucs2toi((S8 *)g_BillPrepInput->water, (S32*)&temp, NULL);
    bill_prep->water = (UINT)temp;
    
    bill_prep->payeway = g_BillPrepInput->PayMethodSel;
    
    if( g_BillPrepInput->insurence[0] )
        mmi_ucs2toCurrency(g_BillPrepInput->insurence, (S32*)&bill_prep->insurence);
    else
        bill_prep->insurence = (UINT)(-1);
    if( g_BillPrepInput->cash[0] )
        mmi_ucs2toCurrency(g_BillPrepInput->cash, (S32*)&bill_prep->cash);
    else 
        bill_prep->cash = (UINT)(-1);
    
    mmi_ucs2toCurrency(g_BillPrepInput->cost, (S32*)&bill_prep->cost);
    
    mmi_wcs_n_to_asc((S8*)bill_prep->sms_no,g_BillPrepInput->SMS_num,QY_PHONE_MAX_LEN*2);
    
    
}

void OnNewBillAddBar(U16 * pstrCode)
{ 
    int toneid =  BATTERY_WARNING_TONE ;
    if( g_BillPrepTbl->Total < QY_MAX_BARS )
    {
        WSTR title;
        int err = CheckNewBillInput(&title);
        if( err == NBD_INPUT_OK || err == NBD_BAR_ADD)
        {
            BILL_PROPERTY * bill_prep = InitBillPrepBar(pstrCode,  0 );
            if( bill_prep )
            {
                //if(bill_list->Barcode)
                AddPrepInfo(bill_prep);
                g_BillPrepTbl->Total++;
                kal_wstrncpy(g_BillPrepInput->barcode, pstrCode, MAX_RDID_LEN+1 );
                g_BillPrepInput->bar_del[0] = 0;
                kal_wsprintf(g_SignRecptCpat,"%w:%d/%d",((U16*)"\x6B\x62\xCF\x63\x0\x0") /*L"扫描"*/, g_BillPrepTbl->Total, QY_MAX_BARS);                
                RedrawCategory57Screen();
                toneid = ERROR_TONE;;
            }
        }
        else
        {
            DisplayPopup( (U8 *)title,QY_RES(IMG_GLOBAL_WARNING), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
        }
    }
    else
    {
        DisplayPopup( (U8 *)((U16*)"\x85\x51\x58\x5B\xF2\x5D\xE1\x6E\x21\x0\x0\x0") /*L"内存已满!"*/,QY_RES(IMG_GLOBAL_WARNING), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
    }
    
    playRequestedTone(toneid);
}

void OnNewBillDelBar(U16 * pstrCode)
{
    int toneid = BATTERY_WARNING_TONE;
    if( g_BillPrepTbl->Total <= 0 )
    {
        DisplayPopup((U8*)((U16*)"\xA1\x6C\x9\x67\x6B\x62\xCF\x63\x61\x67\x1\x78\x21\x0\x0\x0") /*L"没有扫描条码!"*/,
                QY_RES(IMG_GLOBAL_WARNING), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
    }  
    else
    {
        BILL_PROPERTY * bill_last = &g_BillPrepTbl->prep[g_BillPrepTbl->Total];
        BILL_PROPERTY * bill_del = InitBillPrepBar(pstrCode , 1 );
        
        if( bill_del )
        {
            if( bill_last != bill_del )
            {
                *bill_del = *bill_last;
                g_BillPrepTbl->Total--;
            }
            
            g_BillPrepInput->barcode[0] = 0;
            kal_wstrncpy(g_BillPrepInput->bar_del, pstrCode, MAX_RDID_LEN+1 );
            kal_wsprintf(g_SignRecptCpat,"%w:%d/%d",((U16*)"\x6B\x62\xCF\x63\x0\x0") /*L"扫描"*/, g_BillPrepTbl->Total, QY_MAX_BARS);
                
            DisplayPopup((U8*)((U16*)"\x20\x52\x64\x96\x61\x67\x1\x78\x10\x62\x9F\x52\x21\x0\x0\x0") /*L"删除条码成功!"*/,
                    QY_RES(IMG_GLOBAL_WARNING), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
            toneid = ERROR_TONE ;
        }
    }
    playRequestedTone(toneid);
}

void NewBillDetailHlt(int sel)
{
    ChangeLeftSoftkey(QY_RES(STR_GLOBAL_OK), QY_RES(IMG_GLOBAL_OK));
    SetLeftSoftkeyFunction(CbNewBillDetailOnOk, KEY_EVENT_UP);
    if( g_hltNewBillDetail == sel ) return;
    g_hltNewBillDetail = sel;
    
    if(sel == g_NBHltKeyItems[NBD_BAR_ADD] )
    {
        QinYiSetScanHandle(OnNewBillAddBar);
    }
    else if( sel == g_NBHltKeyItems[NBD_BAR_DEL] )
    {
        QinYiSetScanHandle(OnNewBillDelBar);            
    }
    else if( sel == g_NBHltKeyItems[NBD_SEND] )
    {
        QinYiCloseScanDev();
    }    
    else
    {
        QinYiCloseScanDev();
    }    
}

void CbNewBillDetailOnOk(void)
{
    switch( g_NewBillType)
    {
    case QYF_RECIVE:
        NewBillAceptOnOk(0);
        break;
    case QYF_RECIVE|QYF_ACCEPT:
        NewBillDetailOnOk(0);
        break;
    case QYF_RECIVE|QYF_CREATE:
        NewBillDetailOnOk(0);
        break;
    }    
}

int  FillRecptNoBill(int idx)
{
    if( g_BillPrepInput == NULL )
    {
        g_BillPrepInput = (BILL_PREP_INPUT *)QyMalloc(sizeof(BILL_PREP_INPUT ));
        memset(g_BillPrepInput,0, sizeof(BILL_PREP_INPUT));
    }

    return idx;
}

int FillBillProperty(int idx, int bWater )
{
    if( g_BillPrepInput == NULL )
    {
        g_BillPrepInput = (BILL_PREP_INPUT *)QyMalloc(sizeof(BILL_PREP_INPUT ));
        memset(g_BillPrepInput,0, sizeof(BILL_PREP_INPUT));
    }
    AddListItem(idx++,((U16*)"\xA2\x5B\x37\x62\x16\x7F\xF7\x53\x0\x0") /*L"客户编号"*/,0 ,QY_LIST_CAPTION);
    AddListItem(idx++, g_BillPrepInput->ClientId , MAX_CLIENT_ID_LEN ,IMM_INPUT_TYPE_NUMERIC);

    g_BillPrepInput->PayMethodSel = 0;
    AddListItem(idx++, ((U16*)"\x2F\x65\xD8\x4E\x7B\x7C\x8B\x57\x20\x0\x0\x0") /*L"支付类型 "*/, 0, QY_LIST_CAPTION );
    AddListSelItem(idx++,g_strPayMethod,STR_PAY_METHOD_MAX,&g_BillPrepInput->PayMethodSel,QyDumyFuncInt );
    
    AddListItem(idx++, ((U16*)"\xD0\x8F\x39\x8D\x0\x0") /*L"运费"*/, 0, QY_LIST_CAPTION );
    AddListItem(idx++,  g_BillPrepInput->cost, 13 ,IMM_INPUT_TYPE_NUMERIC_SYMBOL);
    
    kal_wsprintf(g_SignRecptCpat,"%w:%d/%d",((U16*)"\x6B\x62\xCF\x63\x0\x0") /*L"扫描"*/, g_BillPrepTbl->Total, QY_MAX_BARS);
    AddListItem(idx++, g_SignRecptCpat, 0, QY_LIST_CAPTION );
    g_NBHltKeyItems[NBD_BAR_ADD] = idx;
    AddListItem(idx++,  g_BillPrepInput->barcode, MAX_RDID_LEN ,IMM_INPUT_TYPE_NUMERIC_SYMBOL);

    if( bWater ) 
    {
        g_BillPrepInput->en_water = bWater;
        AddListItem(idx++, ((U16*)"\x41\x6D\x34\x6C\xF7\x53\x0\x0") /*L"流水号"*/, 0, QY_LIST_CAPTION );
        AddListItem(idx++,  g_BillPrepInput->water,  3 ,IMM_INPUT_TYPE_NUMERIC);
    }

    AddListItem(idx++, ((U16*)"\xE3\x4E\x36\x65\x27\x8D\x3E\x6B\xD1\x91\x9D\x98\x0\x0") /*L"代收货款金额"*/, 0, QY_LIST_CAPTION );
    AddListItem(idx++,  g_BillPrepInput->cash, 13 ,IMM_INPUT_TYPE_NUMERIC_SYMBOL);
    
    AddListItem(idx++, ((U16*)"\xDD\x4F\xF7\x4E\xD1\x91\x9D\x98\x0\x0") /*L"保价金额"*/, 0, QY_LIST_CAPTION );
    AddListItem(idx++,  g_BillPrepInput->insurence, 13 ,IMM_INPUT_TYPE_NUMERIC_SYMBOL);

    g_NBHltKeyItems[NBD_SEND] = idx;
    AddListItem(idx++, ((U16*)"\xD1\x53\x1\x90\x70\x65\x6E\x63\x0\x0") /*L"发送数据"*/, 0, QY_LIST_TEXT);

    AddListItem(idx++, ((U16*)"\x53\x0\x4D\x0\x53\x0\xED\x77\xE1\x4F\x1A\x90\xE5\x77\xF7\x53\x1\x78\x0\x0") /*L"SMS短信通知号码"*/, 0, QY_LIST_CAPTION );
    AddListItem(idx++,  g_BillPrepInput->SMS_num, MAX_RDID_LEN ,IMM_INPUT_TYPE_NUMERIC_SYMBOL);
    
    AddListItem(idx++, ((U16*)"\x20\x52\x64\x96\x61\x67\x1\x78\x0\x0") /*L"删除条码"*/, 0, QY_LIST_CAPTION );
    g_NBHltKeyItems[NBD_BAR_DEL] = idx;
    AddListItem(idx++,  g_BillPrepInput->bar_del, MAX_RDID_LEN ,IMM_INPUT_TYPE_NUMERIC_SYMBOL);
    
    
    return idx;
}

int  FillNewBillDetail(int idx)
{
    
    AddListItem(idx++,((U16*)"\x69\x72\x41\x6D\xF7\x53\x3A\x0\x0\x0") /*L"物流号:"*/,0 ,QY_LIST_CAPTION);
    AddListItem(idx++,  g_newBillDetal[NB_GUID], 0, QY_LIST_TEXT);

    AddListItem(idx++,((U16*)"\xD1\x53\xF6\x4E\xBA\x4E\x30\x57\x40\x57\x3A\x0\x0\x0") /*L"发件人地址:"*/,0 ,QY_LIST_CAPTION);
    AddListItem(idx++,  g_newBillDetal[NB_SEND_ADDR], 0, QY_LIST_TEXT);

    AddListItem(idx++,((U16*)"\xD1\x53\xF6\x4E\xBA\x4E\xD3\x59\xD\x54\x3A\x0\x0\x0") /*L"发件人姓名:"*/,0 ,QY_LIST_CAPTION);
    AddListItem(idx++,  g_newBillDetal[NB_SEND_NAME], 0, QY_LIST_TEXT);

    AddListItem(idx++,((U16*)"\xD1\x53\xF6\x4E\xBA\x4E\x35\x75\xDD\x8B\x3A\x0\x0\x0") /*L"发件人电话:"*/,0 ,QY_LIST_CAPTION);
    AddListItem(idx++,  g_newBillDetal[NB_SEND_PHONE], 0, QY_LIST_TEXT);

//    AddListItem(idx++,L"物流号状态:",0 ,QY_LIST_CAPTION);
//    AddListItem(idx++,  g_newBillDetal[NB_GUID_STATE], 0, QY_LIST_TEXT);
    return idx;
}

int  FillBillList(int *pdef)
{
    int idx = 0;
    switch( g_NewBillType)
    {
    case QYF_RECIVE:
        idx = FillNewBillDetail(idx);
        break;
    case QYF_RECIVE|QYF_ACCEPT:
        {
            int bWater = 0;
            mmi_ucs2toi((S8*)g_newBillDetal[NB_GUID_STATE], &bWater, NULL);
            

            idx = FillNewBillDetail(idx);
            *pdef =idx;
            idx = FillBillProperty(idx, bWater);
        }
        break;
    case QYF_RECIVE|QYF_CREATE:
        idx = FillRecptNoBill(idx);
        idx = FillBillProperty(idx, 0);
        break;
    }    
    return idx;
}

void InitIput()
{
    if( g_BillPrepTbl )
        QyFree(g_BillPrepTbl);
    g_BillPrepTbl = QyMalloc(sizeof(BILL_PREP_TBL)+sizeof(BILL_PROPERTY)*(QY_MAX_BARS-1));
    memset(g_BillPrepTbl, 0, offsetof(BILL_PREP_TBL, prep));
    g_BillPrepTbl->Total = 0;

}

void NewBillDetailApp(void)
{
    g_hltNewBillDetail = -1;
    switch( g_NewBillType)
    {
    case QYF_RECIVE:
        ShowQinYiList(g_strReception[0],
            FillBillList,NewBillAceptHlt,NewBillAceptOnOk,QyDumyFunc,NULL);
        break;
    case QYF_RECIVE|QYF_ACCEPT:
        InitIput();
        ShowQinYiList(g_strReception[1],
            FillBillList,NewBillDetailHlt,NewBillDetailOnOk,NewBillDetailOnExit,NewBillDetailConfirm);
        break;
    case QYF_RECIVE|QYF_CREATE:
        InitIput();
        ShowQinYiList(g_strReception[2],
            FillBillList,NewBillDetailHlt,NewBillDetailOnOk,NewBillDetailOnExit,NewBillDetailConfirm);
        break;
    }
    ChangeLeftSoftkey(QY_RES(STR_GLOBAL_OK), QY_RES(IMG_GLOBAL_OK));
    SetCategory57LeftSoftkeyFunction(CbNewBillDetailOnOk);
    //SetLeftSoftkeyFunction(CbNewBillDetailOnOk, KEY_EVENT_UP);
    
}

//--------------------------------------------------------------------------------

int QyRecptAppOnSel(int nsel)
{
    LoadNewBillDetail((BYTE *)g_NewBillPtr, nsel,g_BillTotal, g_newBillDetal,g_NewBillType);
    NewBillDetailApp();
    return 0;
}

void QyRecptAppExit(void)
{
    if( g_NewBillStr ) 
    {
        QyFree(g_NewBillStr);
        g_NewBillStr = NULL;
    }
    if( g_NewBillPtr )
    {
        QyFree(g_NewBillPtr);
        g_NewBillPtr = NULL;
    }
    g_BillTotal = 0;
}

void LoadAllNewBill(U16 ftype )
{
    UINT bill_size, all_size;
    U16 * pbill, * ptr;
    int fsh = FindNewBill(&bill_size, &all_size, ftype);
    int bill_total = 0;
    if( fsh > 0)
    {
        UINT rd;
        UINT load_size = 0;
        int bErase =( all_size == 0 ) ? 1 :  0;
        pbill = (U16 *)QyMalloc(bill_size);
        ptr = pbill;
        do
        {
            if( pbill == NULL ) break;
            
            LoadNextNewBill(fsh, (BYTE*)ptr, bill_size - load_size, &rd, ftype);
            
            if( rd )
            {
                load_size += rd;
                bill_total ++;
                ptr += rd/sizeof(U16);
            }
        }while(rd);

        if( bill_total )
        {
            g_BillTotal = bill_total;
            g_NewBillPtr = pbill;            
        }
        else //no valid bill find
        {
            FS_GetFileSize(fsh, &bill_size);
            QyFree(pbill);
        }
            
        if( all_size == 0 ) bErase = 1;
        NewBillLookupDone(fsh, bErase);
    }
}

void QyRecptApp(U16 ftype)
{ 
    U8 * ptitle;
    QyRecptAppExit();
    LoadAllNewBill(ftype);
    g_NewBillStr = QyMalloc(sizeof(WSTR)*(g_BillTotal+1));
    g_NewBillStr[0] = '\0';
    g_BillNameTotal = GetBillName((BYTE*)g_NewBillPtr,g_BillTotal, &g_NewBillStr[0]);
    g_NewBillType = ftype;
    switch( ftype)
    {
    case QYF_RECIVE:
        ptitle = g_strReception[0];
        break;
    case QYF_RECIVE|QYF_ACCEPT:
        ptitle = g_strReception[1];
        break;
    default:
        return;
        break;
    }
    
    ShowQinYiMenu(ptitle,(U8 **) g_NewBillStr, NULL, g_BillNameTotal,QyRecptAppOnSel,  QyRecptAppExit );

}

#endif /*NEW_BILL_MODULE*/

#ifdef MESSAGE_WINDOW
#define  MSG_WINDOW_SRC_ID      (SCR_QINYI_APP_MAX-5)
U16 * g_qy_display_info_str;
U16 * g_qy_display_info_title;
FuncPtr qyfnx_display_info_ext;

U8 ExitMsgTxtWnd(void *msg)
{
    if( qyfnx_display_info_ext)
        qyfnx_display_info_ext();
    return 0;
}
void QyShowMessageEntry(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    U8 *guiBuffer;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    EntryNewScreen(MSG_WINDOW_SRC_ID, NULL, QyShowMessageEntry, NULL);
    guiBuffer = GetCurrGuiBuffer(MSG_WINDOW_SRC_ID);

    ShowCategory79Screen(
        g_qy_display_info_title,
        get_image(0),
        get_string(0),
        get_image(0),
        get_string(QY_RES(STR_GLOBAL_BACK)),
        get_image(QY_RES(IMG_GLOBAL_BACK)),
        MMI_TRUE,
        MMI_FALSE,        
        (PU8) g_qy_display_info_str,
        kal_wstrlen( g_qy_display_info_str) + 1,
        guiBuffer);

    SetRightSoftkeyFunction(GoBackHistory, KEY_EVENT_UP);
    /* SetKeyHandler(mmi_brw_display_info_go_back_history, KEY_LEFT_ARROW, KEY_EVENT_DOWN); */

}


void QyShowMessage(U16 * title, U16 * Info, FuncPtr fncExit)
{
    g_qy_display_info_title = title;
    g_qy_display_info_str   = Info;
    qyfnx_display_info_ext  = fncExit;
    QyShowMessageEntry();    
}


#endif /*MESSAGE_WINDOW*/
///////////////////////////////////////////////////////////////////////////////////////menu ////////////
//  menu window
// old {(\([\"x\\A-F0-9]*\))\w+\/\*\([^\*]*\)\*\/}  note: uncheck whole words match
// new \2
// old ((U[0-9]+\*)\(\"[^\"]+\"\))
//



/*******************************************************************************/
#define InitStrTble(ptr , item)       InitStrTbleEx(ptr, (U16 *)(ptr##Tbl), item)
int wstlen(void * pstr)
{
    U8 * ptr = (U8 *)pstr;
    int len = 0;
    while( ptr[0] || ptr[1] )
    {
        len ++;
        ptr += 2;
    }
    return len;    
        
}

void InitStrTbleEx(U8 ** ptr, U16 * pstr, int item)
{
    int i;
    for(i=0 ; i<item; i++)
    {
        int slen = wstlen(pstr);
        if( slen == 0 )
            return ;
        ptr[i] =(U8*) pstr;
        
        pstr += slen + 1;
        if( * pstr == 0 )
        {
            return ;
        };
    }
}



MENU_TEXT   g_strMainMenuTbl[] =
{
    "\xDB\x8F\x65\x51\x0\x0" /*L"进入"*/
    "\x7B\x76\x55\x5F\x0\x0" /*L"登录"*/
    "\xBE\x8B\x6E\x7F\x0\x0" /*L"设置"*/ 
    "\x73\x51\x8E\x4E\x0\x0" /*L"关于"*/     
} ;
#define QYMAX_MENU_MAIN_ITEMS  4
U8 * g_strMainMenu[QYMAX_MENU_MAIN_ITEMS];


MENU_TEXT  g_strMainEntryTbl[] =
{
    "\x36\x65\xF6\x4E\x0\x0" /*L"收件(0/0)"*/
    "\x7E\x7B\x36\x65\x0\x0" /*L"签收"*/
    "\xEE\x95\x98\x98\xF6\x4E\x0\x0" /*L"问题件"*/
    "\xE5\x67\xE2\x8B\x0\x0" /*L"查询"*/
    "\x1A\x90\xE5\x77\x0\x0" /*L"通知(0)"*/    
} ;
#define QYMAX_MENU_MAIN_ENTYR_ITEM  5
U8 * g_strMainEntry[QYMAX_MENU_MAIN_ENTYR_ITEM];

MENU_TEXT  g_titleRecpt[] = {"\x36\x65\xF6\x4E\x0\x0" /*L"收件"*/ };
MENU_TEXT  g_strReceptionTbl[] =
{
    "\xB\x4E\x55\x53\x85\x5F\xD\x59\x0\x0"   /*L"下单待复"*/
    "\x09\x67\x55\x53\x36\x65\xF6\x4E\x0\x0" /*L"有单收件"*/
    "\xE0\x65\x55\x53\x36\x65\xF6\x4E\x0\x0" /*L"无单收件"*/
    "\x4B\x62\xA8\x52\x36\x65\xF6\x4E\x0\x0" /*L"手动收件"*/
    "\x49\x7B\x85\x5F\xD1\x53\x01\x90\x0\x0" /*L"等待发送"*/    
} ;
#define QYMAX_MENU_RECPT_ITEM  5
U8*   g_strReception[QYMAX_MENU_RECPT_ITEM];



MENU_TEXT   g_titleSignRecpt[] = {("\x7E\x7B\x36\x65\x0\x0") /*L"签收"*/ };
MENU_TEXT   g_strSingReceptTbl[] =
{
    "\x7E\x7B\x36\x65\x0\x0" /*L"签收"*/
    "\x49\x7B\x85\x5F\xD1\x53\x1\x90\x0\x0" /*L"等待发送"*/
};
#define QYMAX_MENU_SIGNRECPT_ITEM  2
U8*   g_strSingRecept[QYMAX_MENU_SIGNRECPT_ITEM];



MENU_TEXT   g_titleProblemList[] = {("\xEE\x95\x98\x98\xF6\x4E\x0\x0") /*L"问题件"*/ };
MENU_TEXT   g_strProblemListTbl[] =
{
   "\xEE\x95\x98\x98\xF6\x4E\x0\x0" /*L"问题件"*/
   "\x49\x7B\x85\x5F\xD1\x53\x1\x90\x0\x0" /*L"等待发送"*/    
};
#define QYMAX_MENU_PROBLEM_ITEM  2
U8 * g_strProblemList[QYMAX_MENU_PROBLEM_ITEM];




MENU_TEXT   g_titleOptionReSend[] = {"\x9\x90\x79\x98\x0\x0"/*L"选项"*/};
MENU_TEXT   g_strOptReSendListTbl[]  =
{
    "\x53\x62\x0\x5F\x0\x0" /*L"打开"*/
    "\xCD\x91\xD1\x53\x0\x0" /*L"重发"*/    
    "\x68\x51\xE8\x90\xCD\x91\xD1\x53\x0\x0" /*L"全部重发"*/    
};
#define QYMAX_MENU_OPT_SEND_ITEM  3
U8 * g_strOptReSendList[QYMAX_MENU_OPT_SEND_ITEM] ;


MENU_TEXT   g_strQueryTbl[]  =
{
    "\xE5\x67\xE2\x8B\x0\x0" /*L"查询"*/
    "\xA2\x8B\x55\x53\x0\x0" /*L"订单"*/
    "\x2C\x67\x30\x57\x0\x0" /*L"本地"*/    
};
#define QYMAX_MENU_QUERY_ITEM  3
U8 * g_strQuery[QYMAX_MENU_QUERY_ITEM] ;

MENU_TEXT  g_strWaitReplyTbl[] =
{
    "\xA5\x63\x36\x65\xB\x4E\x55\x53\x0\x0" /*L"接收下单"*/
    "\xA4\x64\x0\x95\xB\x4E\x55\x53\x0\x0"  /*L"撤销下单"*/
    "\x6C\x8F\xD1\x53\xB\x4E\x55\x53\x0\x0" /*L"转发下单"*/
} ;
#define QYMAX_MENU_WAIT_ITEM  3
U8*   g_strWaitReply[QYMAX_MENU_WAIT_ITEM];



int g_qinyi_app_menu_sel =0;
int g_qinyi_app_window_level = 0;



int OnQinYiOptResendMenuSel(S32 sel)
{    
    switch(sel)
    {
    case 0:
    case 1:
        g_SendTaskMode = 0;
        ShowTaskEntry(sel);     
        break;
    case 2:
        g_OptSel4Resend = 0;
        g_SendTaskMode = 1;        
        ShowTaskEntry(sel);   
        break;
    default:
        break;
    }        
 	return 0;
} 


void QinYiOptResendExit(void)
{
}


int QinyiWaitRecp(int sel)
{
    g_wait_sel = sel;
    WaitRecptEntry();
    return 0;
}

void QinyiWaitExit(void)
{

}

void QinYiOptResendEntry(void)
{
    ShowQinYiMenu(g_titleOptionReSend,g_strOptReSendList,NULL,sizeof(g_strOptReSendList)/sizeof(U8 *),OnQinYiOptResendMenuSel, QinYiOptResendExit);
}

void WaitRectMenu(void)
{
    ShowQinYiMenu(g_strReception[0],g_strWaitReply,NULL,sizeof(g_strWaitReply)/sizeof(U8 *),QinyiWaitRecp, QinyiWaitExit);
}

int OnUiChkNeBillCmdAck(int ret)
{
    ret = OnChkNeBillCmdAck(ret);
    if( ret > 1)
    {
        DisplayPopup((PU8)( ((U16*)"\x9\x67\xA2\x8B\x55\x53\x30\x52\xBE\x8F\x0\x0") /*L"有订单到达"*/), 
            QY_RES(IMG_GLOBAL_INFO), 1, UI_POPUP_NOTIFYDURATION_TIME, 0);
    }
    else
    {
        GoBackHistory();

    }
    return 1;
}

int OnQinYiReceptMenuSel(S32 sel)
{    
    g_waitRectSrcId = GetActiveScreenId();
    switch(sel)
    {
    case 0:
        QyRecptApp(QYF_RECIVE);
        break;
    case 1:
        QyRecptApp(QYF_RECIVE|QYF_ACCEPT);
        break;
    case 2:
        g_NewBillType = QYF_RECIVE|QYF_CREATE;
        NewBillDetailApp();
        break;
    case 3:
        ChkNewBill(OnUiChkNeBillCmdAck);  
        DisplayPopup((PU8)((U16*)"\xDE\x8F\xA5\x63\xD\x67\xA1\x52\x68\x56\x2E\x0\x2E\x0\x2E\x0\x0\x0") /*L"连接服务器..."*/,
                            QY_RES(IMG_GLOBAL_PROGRESS), 1,(U32) -1, 0);
        DisableKeyEvent();    
        SetKeyHandler(OnPopopEndKey, KEY_END, KEY_EVENT_UP);
        
        break;
    case 4:
        g_DumpType = QYF_RECIVE;
        ShowQueueTaskEntry();
        break;
    default: 
        break;
    }        
	return 0;
} 


void QinYiReceptExit(void)
{
}


void QinYiReceptEntry()
{
    ShowQinYiMenu(g_titleRecpt,g_strReception,NULL,sizeof(g_strReception)/sizeof(U8 *),OnQinYiReceptMenuSel, QinYiReceptExit);
}

int OnQinYiSingReceptMenuSel(S32 sel)
{
    switch(sel)
    {
    case 0:
        EntryQinYiSignRecpt();//
        break;
    case 1:
        g_DumpType = QYF_SIGN;
        ShowQueueTaskEntry();
        break;
    default:
        break;
    }        
    return 0;

}

void QinYiSingReceptEntry(void)
{
    ShowQinYiMenu(g_titleSignRecpt,g_strSingRecept,NULL,sizeof(g_strSingRecept)/sizeof(U8 *),OnQinYiSingReceptMenuSel, NULL);
}


int OnQinYiProblemMenuSel(S32 sel)
{    
    switch(sel)
    {
    case 0:
        QyEntryProblemApp();
        break;
    case 1:
        g_DumpType = QYF_PROBLEM;
        ShowQueueTaskEntry();
        break;
    default:
        break;
    }      
	return 0;
}

void QinYiProblemEntry(void) 
{
    ShowQinYiMenu(g_titleProblemList,g_strProblemList,NULL,sizeof(g_strProblemList)/sizeof(U8 *),OnQinYiProblemMenuSel, NULL);
}

int OnQinYiQueryMenuSel(S32 sel)
{    
    switch(sel)
    {
    case 0:
        
        break;
    case 1:
        QueryByExpid();
        break;
    case 2:
        
        break;
    default:
        break;
    }        
	return 0;
}

void QinYiQueryEntry(void) 
{
    ShowQinYiMenu(NULL,g_strQuery,NULL,sizeof(g_strQuery)/sizeof(U8 *),OnQinYiQueryMenuSel, NULL);
}




int OnQinYiSelMainEntry(S32 qinyi_app_menu_sel)
{
    switch(qinyi_app_menu_sel)
    {
    case 0:
        QinYiReceptEntry();//mmi_qinyi_waiting();
        break;
    case 1:
        QinYiSingReceptEntry();
        break;
    case 2:
        QinYiProblemEntry();
        break;
    case 3:
        QinYiQueryEntry();
        break;
    default:
        break;
    }        
    
	return 0;
}

void QinYiAppEntry()
{
    StartQyAsySendThread();
    ShowQinYiMenu(NULL,g_strMainEntry,NULL,sizeof(g_strMainEntry)/sizeof(U8 * ),OnQinYiSelMainEntry, NULL);
}
 
U32 CalcLocal(void);
U8 g_sys_about_title[] = "\xE4\x52\x81\x86\x2F\x65\x1\x63\xF4\x8B\xE\x66\x0\x0";

void OnAboutWindowExit(void)
{
    if( g_qy_display_info_str)
        QyFree(g_qy_display_info_str);
    g_qy_display_info_str = NULL;
}

int OnQinYiSelMainMenu(int qinyi_app_menu_sel)
{
    switch(qinyi_app_menu_sel)
    {
    case 0:
        if( QyCheckPassword() )
        {
            QinYiAppEntry();//mmi_qinyi_waiting();
        }
        else
        {
            EntryQinYiLogin(LOCAL_AUTH);//EntryEmBTLoopback(); //JH_Test_Show_Edit() ; Test for a full window test
        }
        break;
    case 1:
        {
            EntryQinYiLogin(SERVER_AUTH);//EntryEmBTLoopback(); //JH_Test_Show_Edit() ; Test for a full window test
        }
        break;
    case 2:
        QySettingApp();//mmi_scan_display_popup((UI_string_type)L"Comming soon!", MMI_EVENT_INFO);
        break;
    case 3:
        if( g_qy_display_info_str)
            QyFree(g_qy_display_info_str);
        g_qy_display_info_str = (U16*)QyMalloc(128*2);
        kal_wsprintf(g_qy_display_info_str, "%w\n\n%w %d\n%w %d\n\n%s\n%s,\n%w: %x",
            ((U16*)"\xE4\x52\x81\x86\x2F\x65\x1\x63\x6B\x62\xCF\x63\xC8\x7E\xEF\x7A\x0\x0") /*L"勤蚁支持扫描终端"*/,
            ((U16*)"\x3B\x4E\x3A\x67\x6F\x8F\xF6\x4E\x48\x72\x2C\x67\x3A\x0\x20\x0\x20\x0\x20\x0\x0\x0") /*L"主机软件版本:   "*/,
            QINYI_PROG_VERSION,            
            ((U16*)"\x47\x53\xA7\x7E\x5\x53\x48\x72\x2C\x67\x3A\x0\x20\x0\x20\x0\x20\x0\x0\x0") /*L"升级包版本:   "*/,
            QY_APPLICATION_VERSION  ,
            __DATE__, __TIME__,
            ((U16*)"\x21\x68\x8C\x9A\x8C\x54\x0\x0") /*L"校验和"*/,
            CalcLocal()   );
        
            QyShowMessage((U16*)g_sys_about_title, g_qy_display_info_str, OnAboutWindowExit);
            
        break;
    default:
        break;
    }         
	return 0;
}


int QySaveUserAndPwd(USER_INFO  * puserinfo)
{
    SaveQySettingProfile(g_SettingProf);
    return 0; 
}

 
int LoadUserAndPwd(void)
{
    if( g_SettingProf )
    {
        g_SysUserInfo = &g_SettingProf->user_info;
        if( g_SysUserInfo->pwd[0] != L'\0' )
            return QY_SUCCESS;   
        return ERR_NOT_AUTHENT;
    }
    return QY_ERROR;
}


int QyCheckPassword()
{//Global varibal 
    MYTIME syst;
    if( g_bQyAuthenticate ==  UN_AUTHEN ) 
        return 0;
    //timer expire
    GetDateTime(&syst);

    if(    g_LastServerAuthenTime.nYear != syst.nYear 
        || g_LastServerAuthenTime.nDay  != syst.nDay 
        || g_LastServerAuthenTime.nMonth!= syst.nMonth )
    {
        return 0;
    }

    return 1;
}


#if  0 //BT_DEBUG

U16 g_sBtFile[]= {L"C:\\Received\\AppsEntry.bin"};

int LoadBtFile(void)
{
    int fsh  = FS_Open(g_sBtFile,FS_READ_ONLY);
    if( fsh >0 )
    {
        U32 rd, flen;  
        U8 * buff ;

        FS_GetFileSize(fsh, &flen);
        buff = (U8*)QyMalloc(flen);
        FS_Read(fsh, buff, flen, &rd);
        FS_Close(fsh);
        fsh = OpenQyFile(QY_PROG, L"AppsEntry.bin", FS_READ_WRITE|FS_CREATE_ALWAYS);
        if(fsh)
        {
            flen = 0;  
            FS_Write(fsh, buff,rd, &flen);
            FS_Close(fsh);
            if( rd == flen )
                FS_Delete(g_sBtFile);
        }
    }
    return 0;    
}
#endif
void InitMenuStr(void)
{
    InitStrTble(g_strMainMenu,      QYMAX_MENU_MAIN_ITEMS       );
    InitStrTble(g_strMainEntry,     QYMAX_MENU_MAIN_ENTYR_ITEM  );
    InitStrTble(g_strReception,     QYMAX_MENU_RECPT_ITEM       );
    InitStrTble(g_strSingRecept,    QYMAX_MENU_SIGNRECPT_ITEM   );
    InitStrTble(g_strOptReSendList, QYMAX_MENU_OPT_SEND_ITEM    );
    InitStrTble(g_strQuery,         QYMAX_MENU_QUERY_ITEM       );
    InitStrTble(g_strProblemList,   QYMAX_MENU_PROBLEM_ITEM     );
    InitStrTble(g_strWaitReply,     QYMAX_MENU_WAIT_ITEM        );
    InitStrTble(g_strPayMethod ,    STR_PAY_METHOD_MAX          );


} 


U32 g_R9Val;

void QyOnFocus(int wndType, U16 srcid)
{   
}   

void QinYiAppMain(void)
{           

    SetKeyHandler(NULL, KEY_EXTRA_1,   KEY_EVENT_UP);
    SetKeyHandler(NULL, KEY_QUICK_ACS, KEY_EVENT_UP);  

#if  0 //BT_DEBUG
    if( LoadBtFile() )
        return;
#endif    
//	g_QinYiFnxOnfocus = QyOnFocus;

    LoadQySetting(g_SettingProf); 
    InitMenuStr();
    
    ShowQinYiMenu(NULL,g_strMainMenu,NULL,QYMAX_MENU_MAIN_ITEMS,OnQinYiSelMainMenu, NULL);
}

 /*****************************************************************************/

void TraceMainTitleEx(int line)
{
}



/*static void exec_key_handler(mmi_key_evt_struct *evt_p)
*/

