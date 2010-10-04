#ifndef QY_ADAPTOR_H
#define QY_ADAPTOR_H

typedef void (*FuncPtr) (void);

#ifdef __cplusplus
extern "C" {
#endif

    void ShowQinYiMenu(U8* title, U8 ** pmenustr, U8** pPopStr, int nitems,  int(*fsel)(int nsel), void (*pexit)(void) );
    void SetKeyHandler(FuncPtr funcPtr,U16 keyCode,U16 keyType);
    void mmi_scan_display_popup(UI_string_type string, mmi_event_notify_enum event_id);
    void QyAdpTrace(char * fmt, ...);

#ifdef __cplusplus
}
#endif

typedef struct tag_qy_adaptor
{
    void (*qy_ShowQinYiMenu)(U8* title, U8 ** pmenustr, U8** pPopStr, int nitems,  int(*fsel)(int nsel), void (*pexit)(void) );
    void (*qy_SetKeyHandler)(FuncPtr funcPtr,U16 keyCode,U16 keyType);
    void (*qy_mmi_scan_display_popup)(UI_string_type string, mmi_event_notify_enum event_id);
    void (*qy_QyAdpTrace)(char * fmt, ...);
}QY_ADAPTOR;


extern QY_ADAPTOR * g_pMtkAdp;

#define  QY_ADAPTO_ELEMENT  {\
    ShowQinYiMenu,  \
    SetKeyHandler,  \
    mmi_scan_display_popup,\
    QyAdpTrace,\
}

#endif /*QY_ADAPTOR_H*/

