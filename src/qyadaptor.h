#ifndef QY_ADAPTOR_H
#define QY_ADAPTOR_H

typedef void (*FuncPtr) (void);
typedef void (*oslTimerFuncPtr) (void*);

#ifdef __cplusplus
extern "C" {
#endif
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

    void ShowQinYiMenu(U8* title, U8 ** pmenustr, U8** pPopStr, int nitems,  int(*fsel)(int nsel), void (*pexit)(void) );
    void SetKeyHandler(FuncPtr funcPtr,U16 keyCode,U16 keyType);
    void mmi_scan_display_popup(UI_string_type string, mmi_event_notify_enum event_id);
    void QyAdpTrace(char * fmt);

    void StopTimer(U16 timerid);
    void StartTimer(U16 timerid, U32 delay, FuncPtr funcPtr);
    void StartTimerEx(U16 timerid, U32 delay, oslTimerFuncPtr funcPtr, void* arg);
    void applib_dt_get_date_time(applib_time_struct *t);

    
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
    
            #ifndef QY_PIKE_PROJ    
    void kal_wsprintf(WCHAR *outstr, char *fmt,...);
    void kal_prompt_trace(module_type type, const kal_char *fmt,...);
            #endif /*QY_PIKE_PROJ */

#ifdef __cplusplus
}
#endif

typedef struct tag_qy_adaptor
{
    int    (*qy_kal_wstrlen)(const WCHAR *wstr);
    WCHAR *(*qy_kal_wstrcpy)(WCHAR *to, const WCHAR *from);
    WCHAR *(*qy_kal_wstrncpy)(WCHAR *to, const WCHAR *from, int n);
    int    (*qy_kal_wstrcmp)(const WCHAR *s1, const WCHAR *s2);
    int    (*qy_kal_wstrncmp)(const WCHAR *s1, const WCHAR *s2, int n);
    WCHAR *(*qy_kal_wstrcat)(WCHAR *s1, const WCHAR *s2);
    WCHAR *(*qy_kal_wstrncat)(WCHAR *s1, const WCHAR *s2, int n);
    WCHAR *(*qy_kal_wstrchr)(const WCHAR *s, int c);
    WCHAR *(*qy_kal_wstrrchr)(const WCHAR *str, int ch);
    
    
    S32  (*qy_mmi_ucs2toi)(const S8 *strSrc, S32 *out_num, S32 *read_length);
    S32  (*qy_mmi_ucs2tox)(const S8 *strSrc, S32 *out_num, S32 *read_length);
    U16  (*qy_mmi_asc_to_wcs)(U16 *pOutBuffer, S8 *pInBuffer);
    U16  (*qy_mmi_asc_n_to_wcs)(U16 *pOutBuffer, S8 *pInBuffer, U32 len);
    U16  (*qy_mmi_wcs_to_asc)(S8 *pOutBuffer, U16 *pInBuffer);
    U16  (*qy_mmi_wcs_n_to_asc)(S8 *pOutBuffer, U16 *pInBuffer, U32 len);
    U16  (*qy_mmi_asc_to_wcs_ex)(U16 *dest, S8 *src, U32 *src_end_pos);
    U16  (*qy_mmi_asc_n_to_wcs_ex)(U16 *dest, S8 *src, U32 len, U32 *src_end_pos);
    U16 *(*qy_mmi_wcslwr)(U16 *string);
    U16 *(*qy_mmi_wcsupr)(U16 *string);
    S32  (*qy_mmi_wcsicmp)(const U16 *str_src, const U16 *str_dst);
    S32  (*qy_mmi_wcsnicmp)(const U16 *str_src, const U16 *str_dst, U32 count);

    void *(*qy_FuncQyMalloc)(unsigned int size);
    void  (*qy_FuncQyFree)(void *ptr);
    
    void (*qy_ShowQinYiMenu)(U8* title, U8 ** pmenustr, U8** pPopStr, int nitems,  int(*fsel)(int nsel), void (*pexit)(void) );
    void (*qy_SetKeyHandler)(FuncPtr funcPtr,U16 keyCode,U16 keyType);
    void (*qy_mmi_scan_display_popup)(UI_string_type string, mmi_event_notify_enum event_id);
    void (*qy_QyAdpTrace)(char * fmt);
    
    void (*qy_StopTimer)(U16 timerid);
    void (*qy_StartTimer)(U16 timerid, U32 delay, FuncPtr funcPtr);
    void (*qy_StartTimerEx)(U16 timerid, U32 delay, oslTimerFuncPtr funcPtr, void* arg);
    void (*qy_applib_dt_get_date_time)(applib_time_struct *t); //GetDateTime

    int (*qy_FS_Open)(const WCHAR * FileName, UINT Flag);
    int (*qy_FS_Close)(FS_HANDLE FileHandle);
    int (*qy_FS_Read)(FS_HANDLE FileHandle, void * DataPtr, UINT Length, UINT * Read);
    int (*qy_FS_Write)(FS_HANDLE FileHandle, void * DataPtr, UINT Length, UINT * Written);
    int (*qy_FS_Seek)(FS_HANDLE FileHandle, int Offset, int Whence);
    int (*qy_FS_Commit)(FS_HANDLE FileHandle);
    int (*qy_FS_GetFileSize)(FS_HANDLE FileHandle, UINT * Size);
    int (*qy_FS_GetFilePosition)(FS_HANDLE FileHandle, UINT * Position);
    int (*qy_FS_Delete)(const WCHAR * FileName);
    int (*qy_FS_CheckFile)(const WCHAR * FileName);
    int (*qy_FS_GetCurrentDir)(WCHAR * DirName, UINT MaxLength);
    int (*qy_FS_SetCurrentDir)(const WCHAR * DirName);
    int (*qy_FS_CreateDir)(const WCHAR * DirName);
    int (*qy_FS_RemoveDir)(const WCHAR * DirName);
    int (*qy_FS_Rename)(const WCHAR * FileName, const WCHAR * NewName);
    int (*qy_FS_XDelete)(const WCHAR * FullPath, UINT Flag, BYTE *RecursiveStack, const UINT StackSize);
    
    void (*qy_kal_wsprintf)(WCHAR *outstr, char *fmt,...);
    void (*qy_kal_prompt_trace)(module_type types, const kal_char *fmt,...);


}QY_ADAPTOR;


extern QY_ADAPTOR * g_pMtkAdp;

#define QY_ADAPTO_ELEMENT  {\
    kal_wstrlen,\
    kal_wstrcpy,\
    kal_wstrncpy,\
    kal_wstrcmp,\
    kal_wstrncmp,\
    kal_wstrcat,\
    kal_wstrncat,\
    kal_wstrchr,\
    kal_wstrrchr,\
    \
    mmi_ucs2toi,\
    mmi_ucs2tox,\
    mmi_asc_to_wcs,\
    mmi_asc_n_to_wcs,\
    mmi_wcs_to_asc,\
    mmi_wcs_n_to_asc,\
    mmi_asc_to_wcs_ex,\
    mmi_asc_n_to_wcs_ex,\
    mmi_wcslwr,\
    mmi_wcsupr,\
    mmi_wcsicmp,\
    mmi_wcsnicmp,\
    \
    FuncQyMalloc,\
    FuncQyFree,\
    \
    ShowQinYiMenu,\
    SetKeyHandler,\
    mmi_scan_display_popup,\
    QyAdpTrace,\
    \
    StopTimer,\
    StartTimer,\
    StartTimerEx,\
    applib_dt_get_date_time,\
    \
    FS_Open,\
    FS_Close,\
    FS_Read,\
    FS_Write,\
    FS_Seek,\
    FS_Commit,\
    FS_GetFileSize,\
    FS_GetFilePosition,\
    FS_Delete,\
    FS_CheckFile,\
    FS_GetCurrentDir,\
    FS_SetCurrentDir,\
    FS_CreateDir,\
    FS_RemoveDir,\
    FS_Rename,\
    FS_XDelete,\
    \
    kal_wsprintf,\
    kal_prompt_trace,\
}

#endif /*QY_ADAPTOR_H*/

