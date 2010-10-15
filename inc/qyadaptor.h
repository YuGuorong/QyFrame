#ifndef QY_ADAPTOR_H
#define QY_ADAPTOR_H
#include "soc_consts.h"
typedef struct 
{
    socket_type_enum	sock_type; /* socket type */
    kal_int16	addr_len; /* address length */
    kal_uint16	port; /* port number */
    kal_uint8	addr[MAX_SOCK_ADDR_LEN];
    /* IP address. For keep the 4-type boundary, 
     * please do not declare other variables above "addr"
    */
} sockaddr_struct;
typedef int (*PsIntFuncPtr)(void *);

#include "QinYiGenprot.h"
#include "QinYiAdpStruct.h"

#ifdef QY_PIKE_PROJ   
#include "QinYiFnxDef.h"
#else
#include "QinYiExportFnx.h"
#endif

#define wgui_inline_items           ((wgui_inline_item*)g_pMtk->gp_inline_items)
#define gIndexIconsImageList        (g_pMtk->pIndexIconsImageList)

#define SCR_QINYI_APP_MAIN          (g_pMtk->SrcStart)
#define SCR_QINYI_APP_WINDOW_1      (g_pMtk->SrcStart+1) 
#define SCR_QINYI_APP_WINDOW_2      (g_pMtk->SrcStart+2) 
#define SCR_QINYI_APP_WINDOW_18     (g_pMtk->SrcStart+18)  
#define SCR_QINYI_APP_WINDOW_19     (g_pMtk->SrcStart+19)  
#define SCR_QINYI_APP_MAX           (g_pMtk->SrcEnd)  

#define QY_RES(res)                 (g_pMtk->Globalbase + res)
#define IDLE_SCREEN_ID              (g_pMtk->IdleAppResBase + 1)

#define g_qy_socket_id              (*g_pMtk->socket_id)
#define currentHighlightIndex       (*g_pMtk->pcurrentHighlightIndex)
#define gIndexIconsImageList      	(g_pMtk->pIndexIconsImageList) 

#define RES_SOC_MSG(msg)            (msg + MSG_ID_SOC_CODE_BEGIN)

#define set_left_softkey_label(S)   set_softkey_label(S, MMI_LEFT_SOFTKEY)
#define set_right_softkey_label(S)  set_softkey_label(S, MMI_RIGHT_SOFTKEY)

#define set_left_softkey_icon(ICON)  set_softkey_icon(ICON, MMI_LEFT_SOFTKEY)
#define set_right_softkey_icon(ICON) set_softkey_icon(ICON, MMI_RIGHT_SOFTKEY)


#define UI_POPUP_NOTIFYDURATION_TIME            1000
#define EM_NOTIFY_DURATION             UI_POPUP_NOTIFYDURATION_TIME
#define SetProtocolEventHandler(func, event)   \
        mmi_frm_set_protocol_event_handler(event, (PsIntFuncPtr)func, MMI_FALSE)

#endif /*QY_ADAPTOR_H*/

