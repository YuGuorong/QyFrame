#ifndef QY_ADAPTOR_H
#define QY_ADAPTOR_H

#include "QinYiprot.h"
#include "QinYiAdpStruct.h"

#ifdef QY_PIKE_PROJ   
#include "QinYiFnxDef.h"
#else
#include "QinYiExportFnx.h"
#endif



#define MOD_MMI                     (g_pMtk->ModMMI)
#define MENU_ID_QINYI_APP_END       (g_pMtk->SrcStart)
#define MENU_ID_QINYI_APP_START     (g_pMtk->SrcEnd)
#define QINYI_TIMER_ID_START        (g_pMtk->TmIdStart)
#define QINYI_TIMER_ID_END          (g_pMtk->TmIdEnd)

#define SCR_QINYI_APP_MAIN          (g_pMtk->SrcStart)
#define SCR_QINYI_APP_WINDOW_1      (g_pMtk->SrcStart+1) 
#define SCR_QINYI_APP_WINDOW_2      (g_pMtk->SrcStart+2) 
#define SCR_QINYI_APP_WINDOW_18     (g_pMtk->SrcStart+18)  
#define SCR_QINYI_APP_WINDOW_19     (g_pMtk->SrcStart+19)  
#define SCR_QINYI_APP_MAX           (g_pMtk->SrcEnd)  

#define QY_RES(res)                 (g_pMtk->Globalbase + res)
#define IDLE_SCREEN_ID              (g_pMtk->IdleAppResBase + 1)

#define wgui_inline_items           ((wgui_inline_item*)g_pMtk->gp_inline_items)
#define gIndexIconsImageList        (g_pMtk->pIndexIconsImageList)
#define currentHighlightIndex       (*g_pMtk->pcurrentHighlightIndex)

#define set_left_softkey_label(S)   set_softkey_label(S, MMI_LEFT_SOFTKEY)
#define set_right_softkey_label(S)  set_softkey_label(S, MMI_RIGHT_SOFTKEY)

#define set_left_softkey_icon(ICON)  set_softkey_icon(ICON, MMI_LEFT_SOFTKEY)
#define set_right_softkey_icon(ICON) set_softkey_icon(ICON, MMI_RIGHT_SOFTKEY)


#define UI_POPUP_NOTIFYDURATION_TIME            1000
#define EM_NOTIFY_DURATION             UI_POPUP_NOTIFYDURATION_TIME

#endif /*QY_ADAPTOR_H*/

