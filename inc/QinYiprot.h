typedef void (*FuncPtr) (void);
typedef void (*oslTimerFuncPtr) (void*);
typedef S32         MMI_key_code_type;
typedef S32         MMI_key_event_type;
typedef U16         UI_string_ID_type;
typedef U16         UI_image_ID_type;
typedef U16         UI_audio_ID_type;
typedef kal_uint16  nvram_lid_enum;
typedef MYTIME      UI_time;
typedef void (*pfncScanDone)(U16 *strcode);
//typedef void (*PsIntFuncPtr)(void *rsp);
typedef void (*QyFocusFnx)(int wndType, U16 srcid);


#ifndef UpdateStatusIcons
#define ShowStatusIcon          wgui_status_icon_show_status_icon
#define HideStatusIcon          wgui_status_icon_hide_status_icon
#define UpdateStatusIcons       wgui_status_icon_update_status_icons
#endif

#ifndef MYQUEUE
#define MYQUEUE         ilm_struct
#endif

// Add export interface here. just declare prototype only, and then regenerate other headers

#ifdef __cplusplus
extern "C" {
#endif
    void kal_wsprintf(WCHAR *outstr, char *fmt,...);
    void kal_prompt_trace(module_type type, const kal_char *fmt,...);
            
    int kal_wstrlen(const WCHAR *wstr);
    WCHAR *kal_wstrcpy(WCHAR *to, const WCHAR *from);
    WCHAR *kal_wstrncpy(WCHAR *to, const WCHAR *from, int n);
    int kal_wstrcmp(const WCHAR *s1, const WCHAR *s2);
    int kal_wstrncmp(const WCHAR *s1, const WCHAR *s2, int n);
    WCHAR *kal_wstrcat(WCHAR *s1, const WCHAR *s2);
    WCHAR *kal_wstrncat(WCHAR *s1, const WCHAR *s2, int n);
    WCHAR *kal_wstrchr(const WCHAR *s, int c);
    WCHAR *kal_wstrrchr(const WCHAR *str, int ch);

    S32 mmi_ucs2toi(const S8 *strSrc, S32 *out_num, S32 *read_length);
    S32 mmi_ucs2tox(const S8 *strSrc, S32 *out_num, S32 *read_length);
    U16 mmi_asc_to_wcs(U16 *pOutBuffer, S8 *pInBuffer);
    U16 mmi_asc_n_to_wcs(U16 *pOutBuffer, S8 *pInBuffer, U32 len);
    U16 mmi_wcs_to_asc(S8 *pOutBuffer, U16 *pInBuffer);
    U16 mmi_wcs_n_to_asc(S8 *pOutBuffer, U16 *pInBuffer, U32 len);
    U16 mmi_asc_to_wcs_ex(U16 *dest, S8 *src, U32 *src_end_pos);
    U16 mmi_asc_n_to_wcs_ex(U16 *dest, S8 *src, U32 len, U32 *src_end_pos);
    U16 *mmi_wcslwr(U16 *string);
    U16 *mmi_wcsupr(U16 *string);
    S32 mmi_wcsicmp(const U16 *str_src, const U16 *str_dst);
    S32 mmi_wcsnicmp(const U16 *str_src, const U16 *str_dst, U32 count);

    void * FuncQyMalloc(unsigned int size, unsigned short MOD, unsigned short line);
    void FuncQyFree(void *ptr);



    void StopTimer(U16 timerid);
    void StartTimer(U16 timerid, U32 delay, FuncPtr funcPtr);
    void StartTimerEx(U16 timerid, U32 delay, oslTimerFuncPtr funcPtr, void* arg);
    void applib_dt_get_date_time(applib_time_struct *t); //GetDateTime

    void playRequestedTone(ALL_TONE_ENUM playtone);
    void stopRequestedTone(ALL_TONE_ENUM playtone);
    
    int FS_Open(const WCHAR * FileName, UINT Flag);
    int FS_Close(FS_HANDLE FileHandle);
    int FS_Read(FS_HANDLE FileHandle, void * DataPtr, UINT Length, UINT * Read);
    int FS_Write(FS_HANDLE FileHandle, void * DataPtr, UINT Length, UINT * Written);
    int FS_Seek(FS_HANDLE FileHandle, int Offset, int Whence);
    int FS_Commit(FS_HANDLE FileHandle);

    int FS_GetFileSize(FS_HANDLE FileHandle, UINT * Size);
    int FS_GetFilePosition(FS_HANDLE FileHandle, UINT * Position);

    int FS_Delete(const WCHAR * FileName);
    int FS_CheckFile(const WCHAR * FileName);

    int FS_GetCurrentDir(WCHAR * DirName, UINT MaxLength);
    int FS_SetCurrentDir(const WCHAR * DirName);
    int FS_CreateDir(const WCHAR * DirName);
    int FS_RemoveDir(const WCHAR * DirName);

    int FS_Rename(const WCHAR * FileName, const WCHAR * NewName);
    int FS_XDelete(const WCHAR * FullPath, UINT Flag, BYTE *RecursiveStack, const UINT StackSize);
    int FS_GetDrive(UINT Type, UINT Serial, UINT AltMask);

    S32 WriteRecord(nvram_lid_enum nLID, U16 nRecordId, void *pBuffer, U16 nBufferSize, S16 *pError);
    S32 ReadRecord(nvram_lid_enum nLID, U16 nRecordId, void *pBuffer, U16 nBufferSize, S16 *pError);
    S32 ReadMultiRecord(nvram_lid_enum nLID, U16 nRecordId, void *pBuffer, U16 nBufferSize, U16 nRecordAmount, S16 *pError);
    S32 WriteValue(U16 nDataItemId, void *pBuffer, U8 nDataType, S16 *pError);
    S32 ReadValue(U16 nDataItemId, void *pBuffer, U8 nDataType, S16 *pError);

    void mmi_frm_set_protocol_event_handler(U16 eventID, PsIntFuncPtr funcPtr, MMI_BOOL isMultiHandler);
    kal_int8 soc_create(    kal_uint8         domain,
                            socket_type_enum  type,
                            kal_uint8         protocol,
                            module_type       mod_id,
                            kal_uint32        nwk_account_id);
    kal_int8 soc_setsockopt(kal_int8   s,
                            kal_uint32 option,
                            void       *val,
                            kal_uint8  val_size);
    kal_int8 soc_getsockopt(kal_int8   s,
                            kal_uint32 option,
                            void       *val,
                            kal_uint8  val_size);
    kal_int8 soc_gethostbyname(kal_bool is_blocking,
                            module_type     mod_id,
                            kal_int32       request_id,
                            const kal_char  *domain_name,
                            kal_uint8       *addr,
                            kal_uint8       *addr_len,
                            kal_uint8       access_id,
                            kal_uint32      nwk_account_id);
    kal_int8 soc_abort_dns_query(kal_bool     by_mod_id,
                             module_type  mod_id,
                             kal_bool     by_request_id,
                             kal_uint32   request_id,
                             kal_bool     by_access_id,
                             kal_uint8    access_id,
                             kal_bool     by_nwk_account_id,
                             kal_uint32   nwk_account_id);
    kal_int8 soc_bind(kal_int8 s, sockaddr_struct *addr);
    kal_int8 soc_listen(kal_int8 s, kal_uint8 backlog);
    kal_int8 soc_accept(kal_int8 s, sockaddr_struct *addr);
    kal_int8 soc_connect(kal_int8 s, sockaddr_struct *addr);
    kal_int32 soc_sendto(kal_int8	     s,
                            const void       *buf,
                            kal_int32	     len,
                            kal_uint8 	     flags,
                            sockaddr_struct *addr);
    
    kal_int32 soc_send( kal_int8 s,const void *buf, kal_int32 len,kal_uint8 flags);
    kal_int32 soc_recv(kal_int8  s,void *buf, kal_int32 len,kal_uint8 flags);
    kal_int32 soc_recvfrom(kal_int8        s,
                            void            *buf,
                            kal_int32       len,
                            kal_uint8       flags,
                            sockaddr_struct *fromaddr);
    kal_int8 soc_shutdown(kal_int8 s, kal_uint8 how);
    kal_int8  soc_close(kal_int8 s);

    void open_scan_engine(pfncScanDone pfnx_scan_done);
    void trig_on_scan_engine(void);
    void close_scan_engine(void);

    void wgui_status_icon_show_status_icon(S16 icon_ID);
    void wgui_status_icon_hide_status_icon(S16 icon_ID);
    void wgui_status_icon_update_status_icons(void);
    void set_softkey_label(UI_string_type s, WGUI_SOFTKEY_ENUM key);

    PU8 get_image(U16 i);
    UI_string_type get_string(MMI_ID_TYPE i);
    U16 GetRootTitleIcon(U16 ItemId);

    
    int AddListSelItem(int idx, U8 ** strSels, int sels, int* pnVal,void (*HighlightListSel)(S32 ));
    int AddListFullEditItem(int idx, U16 * title, U16 * buff, int buf_size, int type, void (*fnxCostomize)(void));
    int AddListItem(int idx, U16 * text, int chars, int type);
    void ShowQinYiList(U8* title, int  (*fnxCbFillItem)(int *), void (*fnxCbHilit)(int),int (*fnxCbOnOk)(int),void (*fnxCbExit)(void),int  (*fnxCbConfirm)(int) );

    void ShowQinYiMenu(U8* title, U8 ** pmenustr, U8** pPopStr, int nitems,  int(*fsel)(int nsel), void (*pexit)(void) );
    void mmi_scan_display_popup(UI_string_type string, mmi_event_notify_enum event_id);

    U8 EntryNewScreen(U16 newscrnID, FuncPtr newExitHandler, FuncPtr newEntryHandler, void *flag);        
    U16 GetActiveScreenId(void);                     
    U8 GetHistory(U16 scrnID, history *ptrHistory);
    void GoBackHistory(void);
    U8 GoBackToHistory(U16 scrnid);
    U8 *GetCurrGuiBuffer(U16 scrnid);                
    U8 *GetCurrInputBuffer(U16 scrnid);
    U8 DeleteScreens(U16 start_scrnid, U16 end_scrnid);
    U32 DeleteHistory(U16 startScrId, U8 bIncStart, U16 count, U16 endScrId, U8 bIncEnd);
    void DeleteNHistory(U16 DeleteCount);
    U16 DeleteScreenIfPresent(U16 ScrId);
    MMI_BOOL IsScreenPresent(U16 scrnId);
    U8 *GetCurrNInputBuffer(U16 scrnid, U16 *size);
    U8 SetDelScrnIDCallbackHandler(U16 ScrnID, HistoryDelCBPtr funcPtr);
    U8 ClearDelScrnIDCallbackHandler(U16 ScrnID, HistoryDelCBPtr funcPtr);
    U16 DeleteBetweenScreen(U16 StartScrId, U16 EndScrId);

    MMI_BOOL GetPreviousScrnIdOf(U16 scrnId, U16 *previousScrnId);
    MMI_BOOL GetNextScrnIdOf(U16 scrnId, U16 *nextScrnId);
    U16 GetCurrScrnId(void);    
    
    void ClearAllKeyHandler(void);
    S32 GetHighlightedItem(void);
    void RegisterHighlightHandler(void (*f) (S32 item_index));
    void ClearHighlightHandler(void);
    void ChangeLeftSoftkey(U16 s, U16 i);
    void ChangeRightSoftkey(U16 s, U16 i);
    void SetLeftSoftkeyFunction(void (*f) (void), MMI_key_event_type k);
    void SetRightSoftkeyFunction(void (*f) (void), MMI_key_event_type k);
    void entry_full_screen(void);
    void leave_full_screen(void);

    void ExecuteCurrKeyHandler(S16 keyCode, S16 keyType);  
    void GetkeyInfo(U16 *keyCode, U16 *keyType); /* gives key code & key type of last key event */
    FuncPtr GetKeyHandler(U16 keyCode, U16 keyType);
    void SetKeyHandler(FuncPtr funcPtr, U16 keyCode, U16 keyType);  
    void SetGroupKeyHandler(FuncPtr funcPtr, PU16 keyCodes, U8 len, U16 keyType);   
    void ClearKeyHandler(U16 keyCode, U16 keyType);
    void PowerAndEndKeyHandler(void);              
    void ClearKeyEvents(void);
    
    void SetScanKeyHandler(FuncPtr ScanKeyHandler);
    FuncPtr GetScanKeyHandler(void);
    void SetDefaultScanKeyHandlers(void);

    
    UI_string_type get_softkey_label(WGUI_SOFTKEY_ENUM key);
    void set_softkey_icon(PU8 i, WGUI_SOFTKEY_ENUM key);
    PU8 get_softkey_icon(WGUI_SOFTKEY_ENUM key);
    void change_softkey(U16 s, U16 i, WGUI_SOFTKEY_ENUM key);
    void show_softkey(WGUI_SOFTKEY_ENUM key);
    void clear_softkey_handler(WGUI_SOFTKEY_ENUM key);
    
    void gdi_layer_lock_frame_buffer(void);
    void gdi_layer_unlock_frame_buffer(void);


    void wgui_update_inline_data(void);   
    void QyAdpTrace(char * fmt);
    void DisplayPopup(U8 *string, U16 imageId, U8 imageOnBottom, U32 popupDuration, U8 toneId);
    void DisplayConfirm(U16 LSK_str,U16 LSK_img,U16 RSK_str,U16 RSK_img,UI_string_type message,MMI_ID_TYPE message_image,U8 toneId);
    void RedrawCategory57Screen(void);
    void SetHighlightIndex(S32 nIndex);
    void RedrawListCategoryScreen(void);

    void InitializeCategory57Screen(void);
    void ExitCategory57Screen(void);
    void CloseCategory57Screen(void);
    void SetInlineItemActivation(InlineItem *item, S32 key_code, S32 key_event);
    void DisableInlineItem(InlineItem *item, S32 index);
    void EnableInlineItem(InlineItem *item, S32 index);
    void LeftJustifyInlineItem(InlineItem *i);
    void RightJustifyInlineItem(InlineItem *i);
    void CenterJustifyInlineItem(InlineItem *i);
    void SetInlineDoneFlag(PU8 history_buffer);
    void DisableCategory57ScreenDone(void);
    void EnableCategory57ScreenDone(void);
    void SetCategory57ScreenRSKClear(void);
    void SetCategory57LeftSoftkeyFunction(void (*LSK_function) (void));
    void SetCategory57RightSoftkeyFunctions(void (*done_function) (void), void (*back_function) (void));
    void SetCategory57Data(InlineItem *list_of_items, S32 number_of_items, PU8 data);

    void SetInlineItemTextEdit(InlineItem *item, PU8 buffer, S32 buffer_size, U32 input_type);
    void RegisterInlineTextEditValidationFunction(InlineItem *item, void (*f) (PU8 buffer, PU8 cursor, S32 text_length));
    void SetInlineTextEditCustomFunction(InlineItem *item, void (*f) (void));
    void ReConfigureInlineItemTextEdit(InlineItem *item, PU8 buffer, S32 buffer_size, U32 input_type);
    void inline_text_edit_set_RSK_label(UI_string_type inline_text_edit_RSK_label);
    void SetInlineItemFullScreenEdit(
            InlineItem *item,
            U16 title,
            U16 title_icon,
            PU8 buffer,
            S32 buffer_size,
            U32 input_type);
    void RegisterInlineFullScreenEditValidationFunction(InlineItem *item,void (*f) (PU8 buffer, PU8 cursor, S32 text_length));
    void SetInlineItemMultiLineEdit(InlineItem *item, PU8 buffer, PU8 title, S32 buffer_size, U32 input_type);
    void SetInlineMultiLineRdOnly(InlineItem *item, PU8 buffer, S32 buffer_size, U32 input_type, U8);
    void set_inscreen_multi_line_input_box_changed(void);

    void SetInlineItemImageText(
            InlineItem *item,
            PU8 text,
            PU8 image1,
            PU8 image2,
            PU8 image3,
            S32 buf_size,
            U16 title,
            U16 title_icon,
            U32 input_type);
    void SetInlineItemCaption(InlineItem *item, PU8 text_p);
    void SetInlineItemDisplayOnly(InlineItem *item, PU8 text_p);
    void SetInlineItemSelect(InlineItem *item, S32 n_items, PU8 *list_of_items, S32 *highlighted_item);
    void RegisterInlineSelectHighlightHandler(InlineItem *item, void (*f) (S32 item_index));
    S32 GetInlineSelectHighlightedItem(void);
    void SetInlineItemUserDefinedSelect(InlineItem *item, PU8 (*current_item_callback) (void),PU8 (*previous_item_callback) (void), PU8 (*next_item_callback) (void));
    void SetInlineItemDOWSelect(InlineItem *item, S32 item_index, PU8 list_of_states);
    void SetInlineItemDate(InlineItem *item, PU8 day_buffer, PU8 month_buffer, PU8 year_buffer,void (*f) (PU8 string_buffer, PU8 day_buffer, PU8 month_buffer, PU8 year_buffer));
    void SetInlineItemTime(InlineItem *item, PU8 hours_buffer, PU8 minutes_buffer, PU8 AM_PM_flag,void (*f) (PU8 string_buffer, PU8 hours_buffer, PU8 minutes_buffer, PU8 AM_PM_flag));
    void SetInlineItemIP4(InlineItem *item, PU8 b1, PU8 b2, PU8 b3, PU8 b4,void (*f) (PU8 string_buffer, PU8 b1, PU8 b2, PU8 b3, PU8 b4));
    void RegisterAttachmentLskFunction(InlineItem *item, void (*f) (PU8 image, UI_string_type str));
    void RegisterAttachmentRskFunction(InlineItem *item, void (*f) (PU8 image, UI_string_type str));
    void RegisterAttachmentHighlightedFunction(InlineItem * item, void (*f)(S32 index));
    void SetInlineItemImageAttachment(
                InlineItem *item,
                PU8 image1,
                PU8 image2,
                PU8 image3,
                U16 title,
                U16 title_icon,
                U8 highlight_image);
    void ClearAttachmentImage(InlineItem *item, S32 index);
    void AddEmailImageAttachmentUI(InlineItem *item, wgui_inline_images_detail *image_details);
    void ClearAllAttachmentImages(InlineItem *item, S32 attachments_present);
    void SetHighlightedAttachment(wgui_inline_item *inline_item, S32 index);
    void DisableInlineItemHighlight(InlineItem *i);
    void EnableInlineItemHighlight(InlineItem *item);
       
    void ShowCategory353Screen(
            U8 *title,
            U16 title_icon,
            U16 left_softkey,
            U16 left_softkey_icon,
            U16 right_softkey,
            U16 right_softkey_icon,
            S32 number_of_items,
            U8 **list_of_items,
            U16 *list_of_icons,
            U8 **list_of_descriptions,
            S32 flags,
            S32 highlighted_item,
            U8 *history_buffer);

    void ShowCategory57Screen_ex(
            U8*  title,
            U16 title_icon,
            U16 left_softkey,
            U16 left_softkey_icon,
            U16 right_softkey,
            U16 right_softkey_icon,
            S32 number_of_items,
            U16 *list_of_icons,
            InlineItem *list_of_items,
            S32 highlighted_item,
            U8 *history_buffer);    

    void ShowCategory79Screen(
            UI_string_type title,
            PU8 title_icon,
            UI_string_type left_softkey,
            PU8 left_softkey_icon,
            UI_string_type right_softkey,
            PU8 right_softkey_icon,
            MMI_BOOL need_scrollbar,
            MMI_BOOL is_r2l_display,
            UI_buffer_type buffer,
            S32 buffer_length,
            UI_buffer_type history_buffer);

    void ShowCategory111Screen(
            U16 left_softkey,
            U16 left_softkey_icon,
            U16 right_softkey,
            U16 right_softkey_icon,
            U16 message,
            U32 input_type,
            U8 *buffer,
            S32 buffer_size,
            U8 *message2,
            U8 *history_buffer);
    void SetCategory111RightSoftkeyFunction(void (*f) (void), MMI_key_event_type k);
    void wgui_inputs_register_validation_func(void (*f) (U8 *, U8 *, S32));
    int MtkSocketConnect( U8 * pIp, int port, int acount_id, int(*fnxCb)(void*, int));
    void FuncQyCheckHeap(void);
    void SetDateTimeEx(void * t);
    void mmi_frm_clear_protocol_event_handler(U16 eventID, PsIntFuncPtr funcPtr);
    void mmi_msg_send_ext_queue(MYQUEUE *message);
    void *mmi_construct_msg_local_para_int(U16 size, S8* file_ptr, U32 line);
    
    void GPIO_ModeSetup(kal_uint16 pin, kal_uint16 conf_dada);
    void GPIO_InitIO(char direction, char port);
    char GPIO_ReadIO(char port);
    void GPIO_WriteIO(char data, char port);
    
    void UART_SetOwner(UART_PORT port, module_type ownerid);
    kal_bool UART_Open(UART_PORT port, module_type ownerid);
    void UART_Close(UART_PORT port, module_type ownerid);
    void UART_SetBaudRate(UART_PORT port, UART_baudrate baud_rate, module_type ownerid);
    void UART_SetDCBConfig(UART_PORT port, UARTDCBStruct *UART_Config, module_type ownerid);
    void UART_ReadDCBConfig(UART_PORT port, UARTDCBStruct *DCB);
    kal_uint16 UART_GetBytes(UART_PORT port, kal_uint8 *Buffaddr, kal_uint16 Length, kal_uint8 *status, module_type ownerid);
    kal_uint16 UART_PutBytes(UART_PORT port, kal_uint8 *Buffaddr, kal_uint16 Length, module_type ownerid);
    kal_uint16 UART_SendData(UART_PORT port, kal_uint8 *Buffaddr, kal_uint16 Length,kal_uint8 mode,kal_uint8 escape_char, module_type ownerid );

    kal_uint8 L1SM_GetHandle(void);
    void L1SM_SleepEnable(kal_uint8 handle);
    void L1SM_SleepDisable(kal_uint8 handle);

    //Gloabal variables here
    int Globalbase                      =    GLOBAL_BASE,    
    int IdleAppResBase                  =    IDLE_APP_BASE,
    int MainMenuResBase                 =    MAIN_MENU_BASE,
    int MsgSocIdStart                   =    MSG_ID_SOC_CODE_BEGIN,
    int ModMMI                          =    MOD_MMI,                    //ModMMI;
    int SrcStart                        =    MENU_ID_QINYI_APP_END,      //SrcStart;
    int SrcEnd                          =    MENU_ID_QINYI_APP_START,    //SrcEnd;
    int TmIdStart                       =    QINYI_TIMER_ID_START,       //TmIdStart;
    int TmIdEnd                         =    QINYI_TIMER_ID_END,         //TmIdEnd;
    int SW_Ver                          =    QINYI_PROG_VERSION, 
    kal_int8 *socket_id                 =    &g_qy_socket_id,

    const U16 * pIndexIconsImageList    =    &gIndexIconsImageList[0],
    U8 *  pcurrentHighlightIndex        =    &currentHighlightIndex,
    void * gp_inline_items              =    &wgui_inline_items[0],
    void * pextern                      =    &g_pext,
    U8 * pLargeHeap                     =    &g_QyHeapBuff[0],

    QyFocusFnx * pFnxQyFocus            =    &g_QinYiFnxOnfocus,
    

     

#ifdef __cplusplus
}
#endif


