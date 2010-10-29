#define QY_MODULE     0x2
#include "QinYiCommon.h"

#define LOGIN_MODULE 
#define SIGNRECPT_MODULE

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
int QyCheckPassword(void);
void OnSideKeyHandle(void);
void ResetAsyCheckTimer(void);

QY_SETTING_PROF *  g_SettingProf;
HistoryDelCBPtr g_fncQyConfirmAbort = NULL;
U16 g_QinYi_UserName[QY_USER_MAX_LEN+1];
U16 g_QinYi_User_Pswd[QY_PSWD_MAX_LEN+1];

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
        (UI_character_type*)(((U16*)"\x2F\x66\x26\x54\x3E\x65\x3\x5F\xF4\x66\x39\x65\x3F\x0\x0\x0") /*L"是否放弃更改?"*/),
        QY_RES(IMG_GLOBAL_QUESTION),
        WARNING_TONE);

    SetRightSoftkeyFunction(GoBackHistory, KEY_EVENT_UP);
    SetLeftSoftkeyFunction(QyExitWihoutSave, KEY_EVENT_UP);        
}    

void SetConfirmExitAbortion(HistoryDelCBPtr funcAbort)
{
    g_fncQyConfirmAbort = funcAbort;
}

pfncScanDone g_QyScanCallback;

void QyScanDone(U16 *strcode)
{
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
    memset(g_QinYi_User_Pswd, 0, sizeof(g_QinYi_User_Pswd));
    QySettingAuthEntry();

}

////////////////////////////////////////////////////////////////////////////////////////////
// menu setting detail
#define MAX_PART_IP_ADDRESS                  4

//U16 g_NetCod[QY_USER_MAX_LEN];
U16 g_ServerIP[QY_IPSTRING_LEN];
U16 g_ServerPort[4];
U16 g_strReconTime[16];
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
*      Module Bar
*
**************************************************************************************************/
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
U16 g_SignRecptName[QY_USER_MAX_LEN];
U16 g_SignRecptCpat[3+4+5];
U16 g_RfBarCode[MAX_RDID_LEN+2];
TASK_HEADER  * g_pSignRecptTask  = NULL;
//Implemetion -------------------------------------------------------------------
int IsValidCode()
{
    int len  = kal_wstrlen(g_RfBarCode);
    
#if 1
    if( len >= 10 )
        return 1;
    return 0;
#else    
    
    if( len == 10 || len == 12 || len == 13 )
        return 1;
    return 0;
#endif 
    
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
    SetTaskJunor(g_pSignRecptTask, g_SignRecptName, QY_USER_MAX_LEN);
    if( SaveTask(g_pSignRecptTask) >= 0  )
    {
        U16 srcid = GetActiveScreenId();
        DisplayPopup((PU8)((U16*)"\xD1\x53\x1\x90\x10\x62\x9F\x52\x0\x0") /*L"发送成功"*/, QY_RES(IMG_GLOBAL_INFO), 1, UI_POPUP_NOTIFYDURATION_TIME, 0);
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
    if( IsValidCode() && (g_pSignRecptTask->totals < 300) )
    {
        ret = AppendRdId(g_pSignRecptTask, g_RfBarCode);
        kal_wsprintf(g_SignRecptCpat,"%w:%d/300",((U16*)"\x6B\x62\xCF\x63\x0\x0") /*L"扫描"*/, g_pSignRecptTask->totals);
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
    kal_wstrncpy(g_RfBarCode, pstrCode, 24);
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
        if( g_SignRecptName[0] && g_SignRecptName[1] )
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

    if( g_pSignRecptTask == NULL )
        g_pSignRecptTask= CreateTask(QYF_SIGN, 8);

    /*  Name */
    SetInlineItemActivation(&wgui_inline_items[QY_SIGN_NAME_CAP], INLINE_ITEM_ACTIVATE_WITHOUT_KEY_EVENT, 0);
    SetInlineItemCaption(&(wgui_inline_items[QY_SIGN_NAME_CAP]), (U8*) (((U16*)"\x7E\x7B\x36\x65\xBA\x4E\xD3\x59\xD\x54\x0\x0") /*L"签收人姓名"*/));

    SetInlineItemActivation(&wgui_inline_items[QY_SING_NAME], INLINE_ITEM_ACTIVATE_WITHOUT_KEY_EVENT, 0);
    SetInlineItemTextEdit( &wgui_inline_items[QY_SING_NAME],  (PU8)g_SignRecptName, QY_USER_MAX_LEN-1, IMM_INPUT_TYPE_SENTENCE);

    /* RDID code */
    kal_wsprintf(g_SignRecptCpat,"%w:%d/300",((U16*)"\x6B\x62\xCF\x63\x0\x0") /*L"扫描"*/, g_pSignRecptTask->totals);
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
    char * ptr = QyMalloc( 100);
    kal_prompt_trace(MOD_MMI, "FuncQyCheckHeap %x", ptr);
    FuncQyCheckHeap();
    QyFree(ptr);
    
    memset(g_RfBarCode,  0, 24 *2);
    memset(g_SignRecptName,0, QY_USER_MAX_LEN*2 );
    ExitQinYnSignRecpt(NULL);
    
    g_pSignRecptTask= CreateTask(QYF_SIGN, 8);
    EntryQinYiSignRecptEx();
}
///////////////////////////////////////////////////////////////////////////
void FreeDump(void );
int  DumpTaskByFtype(QYFILE_TYPE ftype);
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

        DumpTaskByFtype(g_DumpType); //
        ShowQinYiMenu(g_titleResend,g_TaskDump->TitlePtr,NULL,g_TaskDump->Totls,QueueTaskdMenuSel, QueueTaskdMenuExit);
        set_left_softkey_label(get_string(QY_RES(STR_GLOBAL_OPTIONS)));
        set_left_softkey_icon(get_image(QY_RES(IMG_GLOBAL_OPTIONS)));  
        RedrawListCategoryScreen();
    }
    
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Show detail of diffent task
U16 * g_pTaskTotal = NULL;
U16 * g_pTaskTime = NULL;
TASK_HEADER * g_pDeailTask = NULL ;
extern const int g_cmdReqAck[];

int TaskSendDone(int ret)
{
    if( ret > 0 )
    {
        int cmd, err,field;
        void * hack = GetAckHandle(&cmd, &err,&field, NULL);
        FreeAckHandle(hack);

        if( cmd == g_cmdReqAck[(g_DumpType &QYF_FILE_MASK)-1] )
        {
            if( err == 0)
            {
                    
                DeleleTask(g_DumpType, g_OptSel4Resend);
                if( g_SendTaskMode == 0 ||  SendNextTask() == 0)
                {
                    GoBackToHistory(g_SrcIdBeforeList);
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
        DisplayPopup((PU8)(((U16*)"\x1A\x90\xAF\x8B\x31\x59\x25\x8D\x0\x0") /*L"通讯失败"*/), QY_RES(IMG_GLOBAL_ERROR), 0, UI_POPUP_NOTIFYDURATION_TIME, 0);
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
    
U8 ExitTaskDetalListWindow(void * p)
{
    if( g_pDeailTask ) 
    {
        FreeTask(g_pDeailTask);
        g_pDeailTask = NULL;
    }

    if( g_pTaskTotal)
    {
        QyFree(g_pTaskTotal);
        g_pTaskTotal = NULL;
    }
    
    if( g_pTaskTime)
    {
        QyFree(g_pTaskTime);
        g_pTaskTime = NULL;
    }
	return 0;
}

int FillReciveJunorItem(int idx)
{
    return idx;
}

int FillSignJunorItem(int idx)
{
    SIGN_JUNOR * pJunor;
    

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
        (U8*) ((U16*)"\x49\x7B\x85\x5F\xD1\x53\x1\x90\x0\x0") /*L"等待发送"*/,
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
    g_pDeailTask = LoadTask(g_DumpType, g_OptSel4Resend);
    g_pTaskTotal = QyMalloc(sizeof(U16)*16);
	g_pTaskTime = QyMalloc(24*2);
    
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

#endif /*SIGNRECPT_MODULE*/
////////////////////////////////////////////////////////////////////////////////////////////////////////
TASK_HEADER  * g_pProblemTask  = NULL;
int g_ProblemMenuSel;
U16 * g_pOtherProblem;

void SendProblemTask(void)
{

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
    SetTaskJunor(g_pProblemTask, &prob_jounor, sizeof(16)*4 + kal_wstrlen(prob_jounor.strOther));
    if( SaveTask(g_pProblemTask) >= 0  )
    {
        U16 srcid = GetActiveScreenId();
        DisplayPopup((PU8)((U16*)"\xD1\x53\x1\x90\x10\x62\x9F\x52\x0\x0") /*L"发送成功"*/, QY_RES(IMG_GLOBAL_INFO), 1, UI_POPUP_NOTIFYDURATION_TIME, 0);
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
    kal_wstrncpy(g_RfBarCode, pstrCode, 24);
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
    ADD_EDIT_ITEM(g_pOtherProblem,100,IMM_INPUT_TYPE_SENTENCE);    
     
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
    memset(g_RfBarCode,  0, 24 *2);
    memset(g_SignRecptName,0, sizeof(16)*4);
    ExitQinYnProblem(NULL);
    g_pOtherProblem = QyMalloc(100*2);
    memset(g_pOtherProblem,0 ,100*2);
    g_pProblemTask = CreateTask(QYF_PROBLEM, 8);
    QyPeoblemListEntry();
}


////////////////////////////////////////////////////////////////////////////////////////list ///////////
//  list window
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
    DisplayPopup((PU8)((U16*)"\xDE\x8F\xA5\x63\xD\x67\xA1\x52\x68\x56\x2E\x0\x2E\x0\x2E\x0\x0\x0") /*L"连接服务器..."*/, QY_RES(IMG_GLOBAL_PROGRESS), 1,(U32) -1, 0);
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
    kal_wstrncpy(g_RfBarCode, pstrCode, 24);
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


///////////////////////////////////////////////////////////////////////////////////////List end ////////
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

///////////////////////////////////////////////////////////////////////////////////////menu ////////////
//  menu window
// old {(\([\"x\\A-F0-9]*\))\w+\/\*\([^\*]*\)\*\/}  note: uncheck whole words match
// new \2
// old ((U[0-9]+\*)\(\"[^\"]+\"\))
//



/*******************************************************************************/
#define InitStrTble(ptr, item)  { int nu = item; while(nu--> 0) { ptr[nu] = &ptr##Tbl[nu][0];} }

U8  g_strMainMenuTbl[][6] =
{
    {("\xDB\x8F\x65\x51\x0") /*L"进入"*/}
    ,{("\x7B\x76\x55\x5F\x0") /*L"登录"*/}
    ,{("\xBE\x8B\x6E\x7F\x0") /*L"设置"*/} 
    ,{("\x73\x51\x8E\x4E\x0") /*L"关于"*/}     
} ;
#define QYMAX_MENU_MAIN_ITEMS  4
U8 * g_strMainMenu[QYMAX_MENU_MAIN_ITEMS];


U8  g_strMainEntryTbl[][8] =
{
     {("\x36\x65\xF6\x4E\x0") /*L"收件(0/0)"*/}
    ,{("\x7E\x7B\x36\x65\x0") /*L"签收"*/}
    ,{("\xEE\x95\x98\x98\xF6\x4E\x0") /*L"问题件"*/}
    ,{("\xE5\x67\xE2\x8B\x0") /*L"查询"*/}
    ,{("\x1A\x90\xE5\x77\x0") /*L"通知(0)"*/}    
} ;
#define QYMAX_MENU_MAIN_ENTYR_ITEM  5
U8 * g_strMainEntry[QYMAX_MENU_MAIN_ENTYR_ITEM];

U8  g_titleRecpt[] = {"\x36\x65\xF6\x4E\x0\x0" /*L"收件"*/ };
U8   g_strReceptionTbl[][10] =
{
     {("\x49\x7B\x85\x5F\xDE\x56\x0D\x59\x0") /*L"等待回复"*/}
    ,{("\x09\x67\x55\x53\x36\x65\xF6\x4E\x0") /*L"有单收件"*/}
    ,{("\xE0\x65\x55\x53\x36\x65\xF6\x4E\x0") /*L"无单收件"*/}
    ,{("\x4B\x62\xA8\x52\x36\x65\xF6\x4E\x0") /*L"手动收件"*/}
    ,{("\x49\x7B\x85\x5F\xD1\x53\x01\x90\x0") /*L"等待发送"*/}    
} ;
#define QYMAX_MENU_RECPT_ITEM  5
U8*   g_strReception[QYMAX_MENU_MAIN_ENTYR_ITEM];



U8   g_titleSignRecpt[] = {("\x7E\x7B\x36\x65\x0\x0") /*L"签收"*/ };
U8   g_strSingReceptTbl[][10] =
{
     {("\x7E\x7B\x36\x65\x0\x0") /*L"签收"*/}
    ,{("\x49\x7B\x85\x5F\xD1\x53\x1\x90\x0") /*L"等待发送"*/}
};
#define QYMAX_MENU_SIGNRECPT_ITEM  2
U8*   g_strSingRecept[QYMAX_MENU_SIGNRECPT_ITEM];



U8   g_titleProblemList[] = {("\xEE\x95\x98\x98\xF6\x4E\x0\x0") /*L"问题件"*/ };
U8   g_strProblemListTbl[][10] =
{
     {("\xEE\x95\x98\x98\xF6\x4E\x0\x0") /*L"问题件"*/}
    ,{("\x49\x7B\x85\x5F\xD1\x53\x1\x90\x0") /*L"等待发送"*/}    
};
#define QYMAX_MENU_PROBLEM_ITEM  2
U8 * g_strProblemList[QYMAX_MENU_PROBLEM_ITEM];




U8   g_titleOptionReSend[] = {"\x9\x90\x79\x98\x0\x0"/*L"选项"*/};
U8   g_strOptReSendListTbl[][10] =
{
     {("\x53\x62\x0\x5F\x0") /*L"打开"*/}
    ,{("\xCD\x91\xD1\x53\x0") /*L"重发"*/}    
    ,{("\x68\x51\xE8\x90\xCD\x91\xD1\x53") /*L"全部重发"*/}    
};
#define QYMAX_MENU_OPT_SEND_ITEM  3
U8 * g_strOptReSendList[QYMAX_MENU_OPT_SEND_ITEM] ;


U8   g_strQueryTbl[][6] =
{
     {("\xE5\x67\xE2\x8B\x0") /*L"查询"*/}
    ,{("\xA2\x8B\x55\x53\x0") /*L"订单"*/}
    ,{("\x2C\x67\x30\x57\x0") /*L"本地"*/}    
};
#define QYMAX_MENU_QUERY_ITEM  3
U8 * g_strQuery[QYMAX_MENU_QUERY_ITEM] ;


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


void QinYiOptResendEntry(void)
{
    ShowQinYiMenu(g_titleOptionReSend,g_strOptReSendList,NULL,sizeof(g_strOptReSendList)/sizeof(U8 *),OnQinYiOptResendMenuSel, QinYiOptResendExit);
}


int OnQinYiReceptMenuSel(S32 sel)
{    
    switch(sel)
    {
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
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
    InitStrTble(g_strMainMenu, QYMAX_MENU_MAIN_ITEMS);
    InitStrTble(g_strMainEntry,QYMAX_MENU_MAIN_ENTYR_ITEM);
    InitStrTble(g_strReception,QYMAX_MENU_MAIN_ENTYR_ITEM);
    InitStrTble(g_strSingRecept,QYMAX_MENU_SIGNRECPT_ITEM);
    InitStrTble(g_strOptReSendList,QYMAX_MENU_OPT_SEND_ITEM);
    InitStrTble(g_strQuery,QYMAX_MENU_QUERY_ITEM);
    InitStrTble(g_strProblemList,QYMAX_MENU_PROBLEM_ITEM);

} 


U32 g_R9Val;

void QinYiAppMain(void)
{           
    kal_prompt_trace(MOD_MMI," Dll Entry, %x,%x,%d",R9_BASE_BACKUP,g_R9Val, FLAG_BASE_BACKUP);  

    SetKeyHandler(NULL, KEY_EXTRA_1,   KEY_EVENT_UP);
    SetKeyHandler(NULL, KEY_QUICK_ACS, KEY_EVENT_UP);  

#if  0 //BT_DEBUG
    if( LoadBtFile() )
        return;
#endif    

    LoadQySetting(g_SettingProf); 
    InitMenuStr();
    
    ShowQinYiMenu(NULL,g_strMainMenu,NULL,QYMAX_MENU_MAIN_ITEMS,OnQinYiSelMainMenu, NULL);
}

 /*****************************************************************************/




/*static void exec_key_handler(mmi_key_evt_struct *evt_p)
*/

