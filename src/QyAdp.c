
#include <string.h>
#include <stdio.h>
#include "QinYiApp.h"

QY_ADAPTOR * g_pMtkAdp;

void ShowQinYiMenu(U8* title, U8 ** pmenustr, U8** pPopStr, int nitems,  int(*fsel)(int nsel), void (*pexit)(void) )
{
    g_pMtkAdp->qy_ShowQinYiMenu(title,pmenustr,pPopStr,nitems ,fsel, pexit);
} 

void SetKeyHandler(FuncPtr funcPtr,U16 keyCode,U16 keyType)
{
    g_pMtkAdp->qy_SetKeyHandler(funcPtr,keyCode,keyType);
}
void mmi_scan_display_popup(UI_string_type string, mmi_event_notify_enum event_id)
{
    g_pMtkAdp->qy_mmi_scan_display_popup(string, event_id);
}

void QyAdpTrace(char * fmt, ...)
{
    g_pMtkAdp->qy_QyAdpTrace(fmt);
}


