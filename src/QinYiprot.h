typedef void (*FuncPtr) (void);
typedef void (*oslTimerFuncPtr) (void*);
typedef S32         MMI_key_code_type;
typedef S32         MMI_key_event_type;
typedef U16         UI_string_ID_type;
typedef U16         UI_image_ID_type;
typedef U16         UI_audio_ID_type;
typedef MYTIME      UI_time;
typedef void (*pfncScanDone)(U16 *strcode);

#ifndef UpdateStatusIcons
#define ShowStatusIcon          wgui_status_icon_show_status_icon
#define HideStatusIcon          wgui_status_icon_hide_status_icon
#define UpdateStatusIcons       wgui_status_icon_update_status_icons
#endif

#ifdef __cplusplus
extern "C" {
#endif
            #ifndef QY_PIKE_PROJ    
    void kal_wsprintf(WCHAR *outstr, char *fmt,...);
    void kal_prompt_trace(module_type type, const kal_char *fmt,...);
            #endif /*QY_PIKE_PROJ */
            
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

    void *FuncQyMalloc(unsigned int size);
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

    kal_int32 QySocketConnect(void);
    kal_int32 soc_send( kal_int8 s,const void *buf, kal_int32 len,kal_uint8 flags);
    kal_int32 soc_recv(kal_int8  s,void *buf, kal_int32 len,kal_uint8 flags);
    kal_int8  soc_close(kal_int8 s);

    void open_scan_engine(pfncScanDone pfnx_scan_done);
    void trig_on_scan_engine(void);
    void close_scan_engine(void);

    void wgui_status_icon_show_status_icon(S16 icon_ID);
    void wgui_status_icon_hide_status_icon(S16 icon_ID);
    void wgui_status_icon_update_status_icons(void);


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

    void gdi_layer_lock_frame_buffer(void);
    void gdi_layer_unlock_frame_buffer(void);


    void wgui_update_inline_data(void);   
    void QyAdpTrace(char * fmt);
    void DisplayPopup(U8 *string, U16 imageId, U8 imageOnBottom, U32 popupDuration, U8 toneId);
    void DisplayConfirm(U16 LSK_str,U16 LSK_img,U16 RSK_str,U16 RSK_img,UI_string_type message,MMI_ID_TYPE message_image,U8 toneId);
    void RedrawCategory57Screen(void);

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

    

    

#ifdef __cplusplus
}
#endif
