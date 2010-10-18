/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2006
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/

/*******************************************************************************
 * Filename:
 * ---------
 * nvram_common_defs.h
 *
 * Project:
 * --------
 *   Maui
 *
 * Description:
 * ------------
 *   This file is for MTK to config/customize NVRAM settings.
 *
 * Author:
 * -------
 * -------
 *
 *==============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * 2010.03.30        lijf             PR00000615              Porting __TL_TELACOM_MODIFICATION__ 
 * 2010/04/07    linkai     PR00000672     UI移植
2010/04/09 		yangrn     PR00000679   porting TV code.
2010.04.14          yangrn      PR00000705          porting motion sensor features.
2010.04.15          yangrn      PR00000733          porting pray features and other featrues.
2010/04/21         hexw             PR00000784          优化TV
2010.04.21          yangrn      PR00000772          porting gfone customized and input mothod table support and other function.
 *2010/04/26    linkai     PR00000852     porting black list
2010/04/29          yangrn      PR00000874         porting gfone and telaocm some applications.
 * 2010/05/07    linkai     PR00000944     porting auto recorder and emergency SMS
2010.06.03	yangrn	PR00001168		porting vre code.
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *==============================================================================
 *******************************************************************************/
#ifndef NVRAM_COMMON_DEFS_H
#define NVRAM_COMMON_DEFS_H

#ifndef __MAUI_BASIC__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */ 
#include "kal_release.h"
#include "MMI_features.h"
#include "nvram_data_items.h"
#include "custom_nvram_sec.h"
#include "custom_nvram_config.h"
#include "nvram_lid_statistics.h"

#ifdef JATAAYU_SUPPORT
#include "custom_wap_config.h"
#endif 

#ifdef OBIGO_Q05A
#include "custom_wap_config.h"
#endif /* OBIGO_Q05A */

#include "uart_sw.h"
#include "drv_features.h"     
#include "adc.h"

#ifdef __MMI_OP11_HOMESCREEN__
/* under construction !*/
#endif /* __MMI_OP11_HOMESCREEN__ */

/**
 * Customized logical data item ID's.
 *
 */
#define NVRAM_LID_COMMAPP_BEGIN     NVRAM_EF_LAST_LID_CORE

/**
 * Note:
 * This enumeration must begin from NVRAM_LID_CUST_BEGIN!!!
 * Besides, there must be at least one user-defined logical data item.
 */
    typedef enum
    {
        /* Belows are ID's of user defined logical data items. Could be assigned to any category  */
        NVRAM_EF_ADC_LID = NVRAM_LID_COMMAPP_BEGIN,
        NVRAM_EF_CUST_HW_LEVEL_TBL_LID,
        NVRAM_EF_UEM_MANUFACTURE_DATA_LID,
        NVRAM_EF_UEM_RMI_DATA_LID,
        NVRAM_EF_CUST_ACOUSTIC_DATA_LID,
        NVRAM_EF_AUDIO_PARAM_LID,
        NVRAM_EF_AUTOTEST_LID,
        NVRAM_EF_PORT_SETTING_LID,
        NVRAM_EF_BARCODE_NUM_LID,
        NVRAM_EF_SYS_CACHE_OCTET_LID,
        NVRAM_EF_CACHE_BYTE_LID,
        NVRAM_EF_CACHE_SHORT_LID,
        NVRAM_EF_CACHE_DOUBLE_LID,
        NVRAM_EF_IMEI_IMEISV_LID,
        NVRAM_EF_PHB_LID,
        NVRAM_EF_PHB_LN_ENTRY_LID,
        NVRAM_EF_PHONEBOOK_SOS_LID,
        NVRAM_EF_PHONEBOOK_SPEEDDIAL_LID,
        NVRAM_EF_PHB_IDS_LID,
        NVRAM_EF_PHB_FIELDS_LID,            /* !__MMI_PHB_NO_OPTIONAL_FIELD__ */
        NVRAM_EF_PHB_SETTINGS_LID,
        NVRAM_EF_PHB_CALLER_GROUPS_LID,
        NVRAM_EF_PHB_VCARD_LID,
        NVRAM_EF_PHB_EMAIL_SORT_LID,        /* __MMI_PHB_EMAIL_SORT__ */
        NVRAM_EF_PHB_VIDEO_LID,             /* __MMI_INCOMING_CALL_VIDEO__ */
        NVRAM_EF_PHB_LN_TYPE_SEQ_LID,
        NVRAM_EF_PHB_BIRTHDAY_LID,          /* __MMI_PHB_BIRTHDAY_FIELD__ */
        NVRAM_EF_PHB_INFO_LID,              /* __MMI_PHB_INFO_FIELD__ */
        NVRAM_EF_PHB_SNE_LID,               /* __MMI_PHB_USIM_FIELD__ */
        NVRAM_EF_PHB_IMPS_LID,              /* __MMI_PHB_IMPS_FIELD__ */
        NVRAM_EF_PHB_POC_LID,               /* __MMI_PHB_POC_FIELD__ */
        NVRAM_EF_PHB_VOIP_LID,              /* __MMI_VOIP__ */
        NVRAM_EF_SMS_LID,                   /* __MMI_MESSAGES_PREDEFINED_TEMPLATE__ */
        NVRAM_EF_SMS_CB_CHNL_LID,           /* __MOD_SMSAL__ */
        NVRAM_EF_SMS_CB_SMS_LID,
        NVRAM_EF_SMS_CB_SMS_INFO_LID,
        NVRAM_EF_EMS_MY_PICTURE_NAME_LID,   /* __DOWNLOAD__ */
        NVRAM_EF_EMS_MY_ANIMATION_NAME_LID,
        NVRAM_EF_EMS_MY_MELODY_NAME_LID,    /* __MMI_IMELODY_SUPPORT__ && __DOWNLOAD__ */
        NVRAM_EF_SMSAL_SMS_LID,
        NVRAM_EF_SMSAL_MAILBOX_ADDR_LID,
        NVRAM_EF_SMSAL_COMMON_PARAM_LID,
        NVRAM_EF_CB_DEFAULT_CH_LID,
        NVRAM_EF_SMSAL_SMSP_LID,
        NVRAM_EF_MSG_CLUB_LID,              /* __MMI_MESSAGES_CLUB__ */
        NVRAM_EF_MSG_CLUB_NUM_LID,          /* __MMI_MESSAGES_CLUB__ */
        NVRAM_EF_CALL_TIME_LID,
        NVRAM_EF_CAMERA_SETTING_LID,
        NVRAM_EF_VIDEO_SETTING_LID,         /* __MMI_VIDEO_RECORDER__ */
        NVRAM_EF_CAMERA_PARA_LID,           /* ISP_SUPPORT */
        NVRAM_EF_CAMERA_GAMMA_LID,          /* ISP_SUPPORT && ( DRV_ISP_6227_SERIES || MT6229 || MT6230) */
        NVRAM_EF_CAMERA_DEFECT_LID,         /* ISP_SUPPORT && ( DRV_ISP_6227_SERIES || MT6229 || MT6230 || MT6228) */
        NVRAM_EF_CAMERA_LENS_LID,           /* ISP_SUPPORT && ( DRV_ISP_6227_SERIES || MT6229 || MT6230 || MT6228) */
        NVRAM_EF_TCM_PDP_PROFILE_LID,
        NVRAM_EF_IP_NUMBER_LID,             /* __IP_NUMBER__ */
        NVRAM_EF_CSD_PROFILE_LID,           /* __TCPIP_OVER_CSD__ */
        NVRAM_EF_ABM_GPRS_PROFILE_LID,      /* __PS_SERVICE__ */
        NVRAM_EF_ALM_QUEUE_LID,
        NVRAM_EF_ALM_SPOF_DATA_LID,
        NVRAM_EF_ALM_ALARM_DATA_LID,
        NVRAM_EF_TODO_LIST_LID,             /* __MMI_TODOLIST__ */
        NVRAM_EF_SETTING_LID,
        NVRAM_EF_GROUPLIST_LID,
        NVRAM_EF_WPSS_FILENAME_LID,
        NVRAM_EF_SHORTCUTS_LID,
        NVRAM_EF_CALORIE_DATA_LID,
        NVRAM_EF_PROFILES_LID,
        NVRAM_EF_STOPWATCH_LID,             /* __MMI_STOPWATCH__ */
        NVRAM_PICTURE_EDITOR_LID,           /* __MMI_PICTURE_EDITOR_SUPPORT__ */
        NVRAM_EF_PHOTO_EDITOR_SETTING_LID,  /* __MMI_PHOTOEDITOR__ */
        NVRAM_EF_EXT_MELODY_INFO_LID,
        NVRAM_EF_FM_RADIO_LID,              /* __MMI_FM_RADIO__ */
        NVRAM_EF_FMSR_SETTING_LID,          /* __MMI_FM_RADIO_SCHEDULE_REC__ */
        NVRAM_EF_VRSD_TAG_LID,              /* __MMI_VRSD__ */
        NVRAM_EF_VRSI_TAG_LID,              /* __MMI_VRSI__ */
        NVRAM_EF_FMGR_FILEPATH_POOL_HEAD_LID,
        NVRAM_EF_FMGR_FILEPATH_POOL_TAIL_LID,
        NVRAM_EF_BT_INFO_LID,               /* __BT_SUPPORT__ */
        NVRAM_EF_BT_SYS_INFO_LID,           /* __BT_SUPPORT__ */
        NVRAM_EF_BTRADIO_RFMD3500_LID,   /* __BT_SUPPORT__,BTMTK */
        NVRAM_EF_BTRADIO_MT6601_LID,     /* __BT_SUPPORT__,BTMTK_MT6601 */
        NVRAM_EF_BTRADIO_MT6611_LID,     /* __BT_SUPPORT__,BTMTK_MT6611 */
        NVRAM_EF_BTRADIO_MT6612_LID,     /* __BT_SUPPORT__,BTMTK_MT6612 */
        NVRAM_EF_BTRADIO_MT6616_LID,     /* __BT_SUPPORT__,BTMTK_MT6616 */
        NVRAM_EF_BLACK_LIST_LID,            /* __MMI_CM_BLACK_LIST__ */
        NVRAM_EF_IMPS_LID,                  /* __MMI_IMPS__ */
        NVRAM_EF_AUDIO_EQUALIZER_LID,       /* __MMI_AUDIO_EQUALIZER__ */
        NVRAM_EF_POC_PROFILE_LID,
        NVRAM_EF_POC_HISTORY_LID,
        NVRAM_EF_POC_PRIVACY_LID,
        NVRAM_EF_THEMES_VALUES,             /* __MMI_THEMES_APPLICATION__ */
        NVRAM_EF_THEME_MANAGER_LID,         /* __MMI_DOWNLOADABLE_THEMES_SUPPORT__ */
        NVRAM_EF_THEME_DOWNLOAD_LIST_LID,   /* __MMI_DOWNLOADABLE_THEMES_SUPPORT__ */
        NVRAM_EF_MOTION_DICE_LID,           /* __MMI_MOTION_APP__ */
        NVRAM_EF_MOTION_DJ_LID,             /* __MMI_MOTION_APP__ */
        NVRAM_EF_EONS_INFO_LID,             /* __MMI_EONS_SUPPORT__ */
        NVRAM_EF_USER_CTRL_PLMN_LID,        /* __MMI_USER_CTRL_PLMN_SUPPORT__ */
        NVRAM_EF_BGSND_SETTING_LID,         /* __MMI_BG_SOUND_EFFECT__ */
        NVRAM_EF_BGSND_FILEPATH_LID,        /* __MMI_BG_SOUND_EFFECT__ */
        
    #ifdef JATAAYU_SUPPORT
        /* JATAAYU_SUPPORT */
        /* for JBrowser */
        NVRAM_EF_BRW_BOOKMARK_TITLE_LID,
        NVRAM_EF_BRW_BOOKMARK_URL_LID,
    #endif /* JATAAYU_SUPPORT */
    
        NVRAM_EF_BRW_ADDRESS_HISTORY_TITLE_LID,
        NVRAM_EF_BRW_ADDRESS_HISTORY_URL_LID,
        
    #ifdef JATAAYU_SUPPORT  
        /* for JMMS  */
        NVRAM_EF_JMMS_COMPOSE_SETTINGS_LID,
        NVRAM_EF_JMMS_SENDING_SETTINGS_LID,
        NVRAM_EF_JMMS_INBOX_READ_UNREAD_LID,
    #endif /* JATAAYU_SUPPORT */
    
        /* PROVISIONING */
        NVRAM_EF_WAP_PROFILE_CONTENT_LID,
        NVRAM_EF_MMS_PROFILE_CONTENT_LID,
        NVRAM_EF_WAP_PROFILE_NAMES_LID,
        NVRAM_EF_MMS_PROFILE_NAMES_LID,

	/* __MMI_EBOOK_READER__ */
        NVRAM_EF_EBOOK_SETTINGS_LID,
        NVRAM_EF_EBOOK_DEFAULT_SETTINGS_LID,

        NVRAM_EF_BARCODEREADER_SETTING_LID,

        /* SIM-ME Lock */
        NVRAM_EF_SML_LID,

        NVRAM_EF_SYNCML_SETTING_LID,
        NVRAM_EF_SYNCML_PROFILE_LID,

        /* Audio Player Bluetooth Settings */
        NVRAM_EF_A2DP_SETTINGS_LID,
        NVRAM_EF_VOIP_PROF_LID,             /* __MMI_VOIP__*/
        NVRAM_EF_VOIP_SETTING_LID,          /* __MMI_VOIP__*/
        NVRAM_EF_WLAN_SETTING_LID,
        NVRAM_EF_WLAN_PROFILE_LID,        

        NVRAM_EF_EM_NW_EVENT_RINGS_LID,
        /*NITZ PLMN */
        NVRAM_EF_NITZ_NW_NAME_LID,

        NVRAM_EF_DM_FWU_TFTP_SETTING_LID,
        NVRAM_EF_DM_FWU_HTTP_SETTING_LID,

        NVRAM_EF_MS_SECURITY_LID,
        NVRAM_EF_RAC_PREFERENCE_LID,
        NVRAM_EF_AVATAR_SETTING_LID,
        NVRAM_EF_CSB_SETTINGS_LID,

        /* Generic Browser */
        NVRAM_EF_BRW_LAST_WEB_ADDR_LID,
        NVRAM_EF_PUSH_SETTING_LID,

        NVRAM_EF_VIDEO_PREDEFINED_URL_LID,  /* __MMI_VIDEO_STREAM__ */
        NVRAM_EF_VIDEO_HISTORY_URL_LID,     /* __MMI_VIDEO_STREAM__ */
        NVRAM_EF_DRM_SETTING_LID,
        NVRAM_EF_DRM_STIME_LID,
        NVRAM_EF_DRM_CERPATH_LID,
        NVRAM_EF_DM_SR_NUMBER_LID,	    /* __MMI_DM_SELF_REGISTER_SUPPORT__ */
        NVRAM_EF_CUSTSER_SETTING_LID,       /* __MMI_CUSTOMER_SERVICE__*/
        NVRAM_EF_UMMS_COMPOSE_SETTINGS_LID,
        NVRAM_EF_UMMS_SENDING_SETTINGS_LID,
        NVRAM_EF_EMAIL_TEMPLATE_LID,        /* __MMI_EMAIL_TEMPLATE__ */
        NVRAM_EF_LANGLN_LK_SETTING_LID,
        NVRAM_EF_LANGLN_PRESEL_INFO_LID,

        NVRAM_EF_MOBILE_TV_PLAYER_SETTING_LID,  /* __MMI_MOBILE_TV_PLAYER__ */

        NVRAM_EF_LANGLN_BSK_SETTING_LID,
        NVRAM_EF_SLIDE_SHOW_SETTING_LID,    /* __MMI_SLIDESHOW__ */
        NVRAM_EF_VT_SETTING_LID,
        NVRAM_EF_MMS_BGSR_MSG_STRUCT_LID,   /* FOR BGSR */
        NVRAM_EF_BT_BIP_SETTING_LID, /* __MMI_BIP_SUPPORT__ */
        NVRAM_EF_GIS_GPS_SETTING_DATA_LID,
        NVRAM_EF_GPS_SETTING_DATA_LID, 
        NVRAM_EF_MNL_SETTING_DATA_LID, 
        NVRAM_EF_BARCODEREADER_OP11_SETTING_LID,

        NVRAM_EF_CARD2_CB_CHNL_LID,
        NVRAM_EF_CARD2_CB_SMS_LID,
        NVRAM_EF_CARD2_CB_SMS_INFO_LID,
        
        NVRAM_EF_VIDEO_NETWORK_PROFILE_LID,      
        NVRAM_EF_DCD_SETTING_DATA_LID, /*__MMI_OP01_DCD__*/ 
	/* 6238 camera */
        NVRAM_EF_CAMERA_PARA1_LID,
        NVRAM_EF_CAMERA_PARA2_LID,
        NVRAM_EF_CAMERA_DEFECT1_LID,
        NVRAM_EF_CAMERA_DEFECT2_LID,
        NVRAM_EF_CAMERA_SHADING1_LID,
        NVRAM_EF_CAMERA_SHADING2_LID,
        NVRAM_EF_CAMCO_MAIN_SETTING_LID, 
        NVRAM_EF_CAMCO_MAIN_SETTING_SCENE_SEL_LID,

        NVRAM_EF_AGPS_CURRENT_PROFILE_LID,
        NVRAM_EF_AGPS_SETTING_LID,
        NVRAM_EF_AGPS_EM_SETTING_LID,
        NVRAM_EF_TIME_SYNC_SETTING_LID,
        NVRAM_EF_AGPS_PROFILE_LID,
        NVRAM_EF_AGPS_EM_STATUS_LID,

        NVRAM_EF_AUDPLY_LAST_PLAYLIST_PATH_LID,  

        /* phonebook vip contact */
        NVRAM_EF_PHB_HS_VIP_CONTACT_LID,
        /* phonebook vip contact */
        
        NVRAM_EF_SMS_EMAIL_LID, /* __MMI_MESSAGES_SMS_EMAIL__ */
        NVRAM_EF_HOMESCREEN_CNTX_LID,   /* __MMI_OP11_HOMESCREEN__ */

        NVRAM_EF_WAP_PROF_WAP_PROFILE_CONTENT_LID,
        NVRAM_EF_WAP_PROF_MMS_PROFILE_CONTENT_LID,
        NVRAM_EF_WAP_PROF_WAP_SIM1_PROFILE_NAMES_LID,   /* USIM */
        NVRAM_EF_WAP_PROF_MMS_SIM1_PROFILE_NAMES_LID,   /* USIM */
        NVRAM_EF_WAP_PROF_WAP_SIM2_PROFILE_NAMES_LID,   /* USIM */
        NVRAM_EF_WAP_PROF_MMS_SIM2_PROFILE_NAMES_LID,   /* USIM */
        NVRAM_EF_BT_DEFDEVICE_LID,

		NVRAM_EF_TDL_BR_LID,

		NVRAM_EF_SMS_RECENT_EVENT_BITMAP_LID,	/* __MMI_OP11_HOMESCREEN__ */
		NVRAM_EF_SMS_VOICEMAIL_TIME_LID,        /* __MMI_OP11_HOMESCREEN__ __MMI_OP12_TOOLBAR__*/

        NVRAM_EF_CHIST_MISS_ACCUM_TIMES_LID,    /* __MMI_OP11_HOMESCREEN__ */
        NVRAM_EF_CHIST_MISS_EVENT_CHECK_LID,    /* __MMI_OP11_HOMESCREEN__ */
        NVRAM_EF_VS_SETTING_LID,
        NVRAM_EF_IPSEC_POLICY_LID,
        NVRAM_EF_IPSEC_IKE_LID,
        NVRAM_EF_PHB_OG_SET_DEFAULT_NUMBER_LID,

        NVRAM_EF_PHB_ICE_CONTACT_LID,

        NVRAM_EF_SMS_UD_TMEP_LID,                       /* __MMI_MESSAGES_USERDEFINED_TEMPLATE__ */

        NVRAM_EF_SYNCML_VIEW_LOG_LID,
        NVRAM_EF_BCR_SETTING_LID, /*bcr setting id*/
        NVRAM_EF_ANSWER_MACHINE_SETTING_LID,

        NVRAM_EF_TOOLBAR_CNTX_LID,      /* __MMI_OP12_TOOLBAR__ */
        
        NVRAM_EF_MEDPLY_SETTINGS_LID,
        NVRAM_EF_MEDPLY_SETTINGS_NETWORK_PROFILE_LID,
        NVRAM_EF_MEDPLY_LAST_PLAYLIST_PATH_LID,        
        NVRAM_EF_MEDPLY_HISTORY_URL_LID,   
        NVRAM_EF_PHB_INFO_OCCUPIED_LID, 
		NVRAM_EF_PUSH_GEN_SETTING_LID,
		NVRAM_EF_PUSH_BLACK_LIST_LID,
		NVRAM_EF_PUSH_WHITE_LIST_LID,
		        
        NVRAM_EF_INET_CUSTPACK_LID, /* Internet Application */
        NVRAM_EF_IPSEC_PROFILE_NAME_LID,

        NVRAM_EF_PICTBRIDGE_LID, /* pictbridge */

        NVRAM_EF_SYNCML_DEV_SETTING_LID,	/* Syncml Device */
        NVRAM_EF_SYNCML_DEV_ACCOUNT_LID,
        NVRAM_EF_SYNCML_DEV_SYNC_LOG_LID,
        NVRAM_EF_WAP_BOOKMARK_LIST_LID,
        NVRAM_EF_WHITE_LIST_LID,            /* __MMI_CM_WHITE_LIST__ */
		NVRAM_EF_SIM_LOCK_LID, /* __SMART_PHONE_MODEM__ */
        NVRAM_EF_FMRDO_SCHEDULER_LID,          /* __MMI_FM_RADIO_SCHEDULER__ */
        NVRAM_EF_BCR_FIELD_SET_LID, 
        NVRAM_EF_BT_BIP_SET_FOLDER_LID, /* __MMI_BIP_SUPPORT__ */

        NVRAM_EF_TCM_EXT_CALL_HISTORY_LID, // __TCM_EXT_CALL_HISTORY_SUPPORT__
        NVRAM_EF_MEDPLY_PREDEFINED_URL_LID, 
        NVRAM_EF_A8BOX_SETTING_LID,
       
        NVRAM_EF_CAMERA_PARA1_MAIN_LID,
        NVRAM_EF_CAMERA_PARA2_MAIN_LID,
        NVRAM_EF_CAMERA_DEFECT1_MAIN_LID,
        NVRAM_EF_CAMERA_DEFECT2_MAIN_LID,
        NVRAM_EF_CAMERA_SHADING1_MAIN_LID,
        NVRAM_EF_CAMERA_SHADING2_MAIN_LID,   
        NVRAM_EF_CAMERA_PARA1_SUB_LID,
        NVRAM_EF_CAMERA_PARA2_SUB_LID,
        NVRAM_EF_CAMERA_DEFECT1_SUB_LID,
        NVRAM_EF_CAMERA_DEFECT2_SUB_LID,
        NVRAM_EF_CAMERA_SHADING1_SUB_LID,
        NVRAM_EF_CAMERA_SHADING2_SUB_LID,   
        NVRAM_EF_CAMERA_PARA1_MAIN_BAK1_LID,
        NVRAM_EF_CAMERA_PARA2_MAIN_BAK1_LID,
        NVRAM_EF_CAMERA_DEFECT1_MAIN_BAK1_LID,
        NVRAM_EF_CAMERA_DEFECT2_MAIN_BAK1_LID,
        NVRAM_EF_CAMERA_SHADING1_MAIN_BAK1_LID,
        NVRAM_EF_CAMERA_SHADING2_MAIN_BAK1_LID,               
        NVRAM_EF_CAMERA_PARA1_SUB_BAK1_LID,
        NVRAM_EF_CAMERA_PARA2_SUB_BAK1_LID,
        NVRAM_EF_CAMERA_DEFECT1_SUB_BAK1_LID,
        NVRAM_EF_CAMERA_DEFECT2_SUB_BAK1_LID,
        NVRAM_EF_CAMERA_SHADING1_SUB_BAK1_LID,
        NVRAM_EF_CAMERA_SHADING2_SUB_BAK1_LID,                      
        NVRAM_EF_CAMERA_MAIN_SENSOR_ID_LID,
        NVRAM_EF_CAMERA_SUB_SENSOR_ID_LID,
        NVRAM_EF_CAMCO_APP_INFO_LID,
        NVRAM_EF_CAMCO_SUB_SETTING_LID, 
        NVRAM_EF_CAMCO_SUB_SETTING_SCENE_SEL_LID,
        NVRAM_EF_EMAIL_DATA_ACCOUNT_LID,    /* Email Data Account */
        NVRAM_EF_ECOMPASS_LID,        
        NVRAM_EF_CAMERA_PARA_MAIN_LID,
        NVRAM_EF_CAMERA_PARA_MAIN_BAK1_LID,
        NVRAM_EF_SYNCML_ACCOUNT_LID,
#if 1 //def __VRE_V2X__
    	NVRAM_EF_VRE_APP_BAN_LIST_LID,
    	NVRAM_EF_VRE_PKEY_LIST_LID,
    	NVRAM_EF_VRE_SYM_ENTRY_LIST_LID,
    	NVRAM_EF_VRE_SYM_CONF_LIST_LID,
    	NVRAM_EF_VRE_PAY_CHANNEL_ORG_LIST_LID,
    	NVRAM_EF_VRE_PAY_CHANNEL_LIST_LID,
    	NVRAM_EF_VRE_PAY_CHANNEL_LIST2_LID,
    	NVRAM_EF_VRE_PAY_CHANNEL_LIST3_LID,
    	NVRAM_EF_VRE_PAY_CHANNEL_LIST4_LID,
    	NVRAM_EF_VRE_APP_STATE_LIST_LID,
    	NVRAM_EF_VRE_APPSTORE_CONFIG_LIST_LID,
#endif
	#ifdef __VRE_V30__
		NVRAM_EF_VRE_APP_BAN_LIST_EXT_LID,
		NVRAM_EF_VRE_PKEY_LIST_EXT_LID,
		NVRAM_EF_VRE_SYM_ENTRY_LIST_EXT_LID,
		NVRAM_EF_VRE_SYM_CONF_LIST_EXT_LID,
		NVRAM_EF_VRE_PAY_CHANNEL_LIST_EXT_LID,
		NVRAM_EF_VRE_PAY_CHANNEL_LIST2_EXT_LID,
		NVRAM_EF_VRE_PAY_CHANNEL_LIST3_EXT_LID,
		NVRAM_EF_VRE_PAY_CHANNEL_LIST4_EXT_LID,
		NVRAM_EF_VRE_APP_STATE_LIST_EXT_LID,
		NVRAM_EF_VRE_APPSTORE_CONFIG_LIST_EXT_LID,
		NVRAM_EF_VRE_APPSTORE3_CONFIG_LIST_EXT_LID,
		NVRAM_EF_VRE_FIRST_RUNNING_LID,
		NVRAM_EF_VRE_CHARGE_DETAIL_LIST_EXT_LID,
		NVRAM_EF_VRE_CHARGE_SMS_DETAIL_LIST_EXT_LID,
		NVRAM_EF_VRE_PAY_CONFIG_EXT_LID,
		NVRAM_EF_VRE_OPERATOR_CODE_EXT_LID,
	#endif
	#ifdef __VRE30_AM__
		NVRAM_EF_AM_HS_SHORTCUT_LIST_LID,
	#endif
		NVRAM_EF_NOTE_APP_LID,  /* __MMI_NOTE_APP__ */

        NVRAM_EF_SEARCH_WEB_HISTORY_LID,    /* __MMI_SEARCH_WEB__ */
        NVRAM_EF_SEARCH_WEB_BAIDU_UID_LID,  /* __MMI_SEARCH_WEB_BAIDU__ */

        NVRAM_EF_VENUS_HS_CNTX_LID,                 /* __MMI_VUI_HOMESCREEN__ */
        NVRAM_EF_VENUS_HS_WIDGET_MEMO_CNTX_LID,     /* Venus home screen Memo widget */
        NVRAM_EF_VENUS_MM_LID,                       /* __MMI_VUI_MAINMENU__ */
        NVRAM_EF_VENUS_PHOTO_FILEPATH_LID,          /* __MMI_VUI_HOMESCREEN_PHOTO__ */

        NVRAM_EF_CBM_CALL_HISTORY_LID,
        NVRAM_EF_DCD_EM_PARAM_DATA_LID, /*__MMI_EM_MISC_DCD__*/ 
        NVRAM_EF_ZAKAT_CALCULATOR_LID,
        NVRAM_EF_ABM_PS_QOS_PROFILE_LID,      /* __PS_SERVICE__ */
        NVRAM_EF_AZAAN_ALARM_LID,                   /* __MMI_AZAAN_ALARM__ */
        NVRAM_EF_IVEX_SETTINGS_LID,        /* __MMI_IMAGE_VIEWER_EX__ */

        NVRAM_EF_WAP_PROF_WAP_WLAN_PROFILE_NAMES_LID,   /* USIM */
        NVRAM_EF_DM_APP_SCOMO_REPORT_INFO_LID,
        NVRAM_EF_BWCS_SETTING_DATA_LID,    /* __WIFI_BT_SINGLE_ANTENNA_SUPPORT__ */

    #ifdef __OCSP_SUPPORT__
        NVRAM_EF_CERTMAN_OCSP_URL_LID,
    #endif   /*__OCSP_SUPPORT__*/

        /*TV*/
#ifdef __TV_IN_SUPPORT__
        NVRAM_EF_TV_CH_LIST,
        NVRAM_EF_TV_CH_NAME_LIST,
        NVRAM_EF_TV_ADJUST_CH_LIST,
        NVRAM_EF_TV_SETTING_VOL,
	NVRAM_EF_TV_SETTING_AREA,
#endif
#ifdef __PRAY_IN_SUPPORT__
    NVRAM_EF_ALM_PRAY_LID,
    NVRAM_EF_ALM_PRAY_CUSTOM_LID,
    NVRAM_EF_ALM_PRAY_PICTURE_LID,
    NVRAM_EF_ALM_PRAY_VIDEO_LID,
#endif
#ifdef __TL_SMS_BLACK_LIST__
        NVRAM_EF_SMS_BLACK_LIST_LID,            /* __TL_SMS_BLACK_LIST__ */
#endif

#if defined(__MMI_EMERGENCY_SMS__)
    NVRAM_EF_EMERGENCY_SMS_LID,
    NVRAM_EF_EMERGENCY_SMS_CONTENT_LID,
#endif
#if defined( __TV_IN_SUPPORT__) 
    #if defined(TLG1170)
    NVRAM_EF_TV_TLG1170_CH_LIST,
    #endif
#endif

/**************************************************************************
 *   Add new entry in the tail with its compile optoin                    *
 *   Add new entry in the tail with its compile optoin                    *
 *   Add new entry in the tail with its compile optoin                    *
 **************************************************************************/
        NVRAM_EF_LAST_LID_COMMAPP
    } nvram_lid_commapp_enum;

/**
 * System Cache OCTET : This is a special NVRAM data item used for storage purpose.
 *                                   Please note that the default value is ALWAYS 0x00
 */
#define NVRAM_EF_SYS_CACHE_OCTET_SIZE        8
#define NVRAM_EF_SYS_CACHE_OCTET_TOTAL     20

typedef enum
{
    NVRAM_SYS_CACHE_BEGIN = 1,
    NVRAM_SYS_FLIGHTMODE_STATE,
    NVRAM_SYS_DSP_PATCH,
    NVRAM_SYS_SIM_PLUS_SETTING,
    NVRAM_SYS_FIXED_GAIN_MECH_FOR_HELIOS2,
    NVRAM_SYS_FACTORY_FLAG,
    NVRAM_SYS_LAST_FAT_STATUS,
    NVRAM_SYS_INFO,
    NVRAM_SYS_PHB_COMPARE_DIGIT,
    NVRAM_SYS_SVN,
    NVRAM_SYS_USB_BOOT_MODE,
    NVRAM_SYS_CACHE_MAX
} nvram_sys_cache_enum;

/* MS unique ID */
#define UNI_ID   NVRAM_EF_IMEI_IMEISV_LID

/**
 * For each logical data item, defines its constants of `size' and `number of records'
 * For linear-fixed, TOTAL is greater than 1, and SIZE is size of each record;
 * for transparent, TOTAL must be exaclty 1, and SIZE is size of entire data item.
 *
 * Each logical data item must be:
 * Size of default value must be equal to the logical data item's size.
 */

/************************************
 * Custom MMI Define Start
 ************************************/
/* for mmi cache *//* Move to other file */
#define NVRAM_CACHE_SIZE               512      /* For Cache file */
#define NVRAM_CACHE_TOTAL              1        /* For Cache file */

#define NVRAM_CSB_SETTINGS_SIZE			60
#define NVRAM_CSB_SETTINGS_TOTAL		1

#define NVRAM_EF_CUST_SIZE             16
#define NVRAM_EF_CUST_TOTAL            2

#define NVRAM_DOWNLOAD_IMAGE_RECORD_SIZE     40
#define NVRAM_DOWNLOAD_IMAGE_RECORD_TOTAL    1

#define NVRAM_DOWNLOAD_TONE_RECORD_SIZE      40
#define NVRAM_DOWNLOAD_TONE_RECORD_TOTAL     1

#define NVRAM_DOWNLOAD_MELODY_RECORD_SIZE    40
#define NVRAM_DOWNLOAD_MELODY_RECORD_TOTAL   1

#define NVRAM_EF_TEST_1_SIZE                 10
#define NVRAM_EF_TEST_1_TOTAL                2

#define NVRAM_EF_PHONEBOOK_SIZE        16
#define NVRAM_EF_PHONEBOOK_TOTAL       2

#if 1//def __TV_IN_SUPPORT__
#define NVRAM_EF_TV_SETTING_TOTAL               1
#define NVRAM_EF_TV_SETTING_SIZE                1
#define NVRAM_EF_TV_CH_LIST_TOTAL               1
#ifdef __TL_APPENDED_LIST_NUMBER_ICON__    //需要注意tlg1170里的SERVICE_TABLE_SIZE的大小要一致!!!!!!!!!!!!!!!!!!!!!!!!!!
#define NVRAM_EF_TV_CH_LIST_SIZE                50
#else
#define NVRAM_EF_TV_CH_LIST_SIZE                70
#endif
#ifdef __TL_APPENDED_LIST_NUMBER_ICON__    
#define NVRAM_EF_TV_CH_NAME_SIZE                1250
#else
#define NVRAM_EF_TV_CH_NAME_SIZE                1750
#endif
#define NVRAM_EF_TV_ADJUSTU_CH_SIZE                140
#if defined(TLG1170)
#define NVRAM_TVPLY_TLG1170_EPGCHANNEL_SIZE    184
#define NVRAM_TVPLY_TLG1170_EPGCHANNEL_TOTAL   40
#endif
#endif

#ifdef __MMI_THEMES_APPLICATION__
#ifdef __MMI_THEMES_V2_SUPPORT__
#define NVRAM_THEMES_VALUES_SIZE       124
#else 
#define NVRAM_THEMES_VALUES_SIZE       8
#endif 
#define NVRAM_THEMES_VALUES_RECORDS    1
#endif /* __MMI_THEMES_APPLICATION__ */ 

#define NVRAM_THEMES_DOWNLOAD_SIZE        1282
#define NVRAM_THEMES_DOWNLOAD_RECORDS     1

#define NVRAM_MAX_GROUP_NAME_SIZE      36
#define NVRAM_MAX_GROUP_NAME_TOTAL     12

#define NVRAM_MAX_POC_HISTORY_SIZE        1361
#define NVRAM_MAX_POC_HISTORY_TOTAL    1

#define NVRAM_MAX_POC_PRIVACY_SIZE        95
#define NVRAM_MAX_POC_PRIVACY_TOTAL       1

#define NVRAM_MAX_POC_PROFILE_SIZE        336
#define NVRAM_MAX_POC_PROFILE_TOTAL       3

#define NVRAM_COMPOSE_RINGTONE_TOTAL   1
#define NVRAM_COMPOSE_RINGTONE_SIZE    40*5

#define NVRAM_IP_NUMBER_TOTAL          1
#define NVRAM_IP_NUMBER_SIZE           22*3

#ifdef __MMI_CALORIE__
/* under construction !*/
/* under construction !*/
#endif  /*__MMI_CALORIE__ */
#if (defined __TL_MMI_IDLESCREEN_SHORTCUTS__)
#define NVRAM_SHORTCUTS_SIZE           750
#else
#define NVRAM_SHORTCUTS_SIZE           250
#endif
#define NVRAM_SHORTCUTS_TOTAL       2

#ifdef __MMI_CUSTOMER_SERVICE__
/* under construction !*/
/* under construction !*/
#endif

#ifdef __MMI_MESSAGES_PREDEFINED_TEMPLATE__
#define NVRAM_SMS_TEMPL_RECORD_SIZE    84
#define NVRAM_SMS_RECORD_TOTAL         31
#endif /* __MMI_MESSAGES_PREDEFINED_TEMPLATE__ */ 

#ifdef __MMI_MESSAGES_USERDEFINED_TEMPLATE__
#define NVRAM_SMS_UD_TEMPL_RECORD_SIZE    324
#define NVRAM_SMS_UD_RECORD_TOTAL         11
#endif /* __MMI_MESSAGES_USERDEFINED_TEMPLATE__ */ 

#ifdef __MMI_EMAIL_TEMPLATE__
#define NVRAM_EMAIL_TEMPL_RECORD_SIZE    84
#define NVRAM_EMAIL_RECORD_TOTAL         31
#endif /* __MMI_EMAIL_TEMPLATE__ */ 

#ifdef __MOD_SMSAL__
#define NVRAM_SMS_MAX_DIGITS_SMS        21
#define NVRAM_SMS_CB_CHNL_NAME_LEN      10
#define NVRAM_SMS_CB_CHNL_TOTAL_NUM     40

#define NVRAM_SMS_CB_CHNL_RECORD_SIZE  sizeof(nvram_sms_cb_channel_nvram_struct)
#define NVRAM_SMS_CB_CHNL_RECORD_TOTAL 1

#define NVRAM_SMS_CB_SMS_RECORD_SIZE   826      /* 824 */
#define NVRAM_SMS_CB_SMS_RECORD_TOTAL  1

#define NVRAM_SMS_CB_MAX_STORE_CB_MSG     5
#define NVRAM_SMS_CB_SMS_PAGE_SIZE        94

#ifdef LOW_COST_SUPPORT
#define NVRAM_SMS_CB_SMS_PAGE_NUM_TOTAL   15
#else /* LOW_COST_SUPPORT */
#define NVRAM_SMS_CB_SMS_PAGE_NUM_TOTAL   30
#endif /* LOW_COST_SUPPORT */

#define NVRAM_SMS_CB_SMS_INFO_SIZE        sizeof(nvram_sms_cb_sms_info_struct)
#define NVRAM_SMS_CB_SMS_INFO_TOTAL       1
#endif /* __MOD_SMSAL__ */ 


#ifdef __MMI_MESSAGES_SMS_EMAIL__
#define NVRAM_SMS_EMAIL_RECORD_SIZE         sizeof(nvram_sms_email_address_struct)
#define NVRAM_SMS_EMAIL_RECORD_TOTAL        4
#endif /* __MMI_MESSAGES_SMS_EMAIL__ */

#define NVRAM_MSG_CLUB_RECORD_SIZE     16
#define NVRAM_MSG_CLUB_RECORD_TOTAL    1

#define NVRAM_MSG_CLUB_NUM_RECORD_SIZE 8
#define NVRAM_MSG_CLUB_NUM_RECORD_TOTAL   1

#ifdef __DOWNLOAD__
#define NVRAM_EMS_MY_PICTURE_NAME_RECORD_SIZE      140
#define NVRAM_EMS_MY_PICTURE_NAME_RECORD_TOTAL  1

#define NVRAM_EMS_MY_ANIMATION_NAME_RECORD_SIZE  140
#define NVRAM_EMS_MY_ANIMATION_NAME_RECORD_TOTAL    1
#ifdef __MMI_IMELODY_SUPPORT__
#define NVRAM_EMS_MY_MELODY_NAME_RECORD_SIZE     140
#define NVRAM_EMS_MY_MELODY_NAME_RECORD_TOTAL           1
#endif /* __MMI_IMELODY_SUPPORT__ */ 
#endif /* __DOWNLOAD__ */ 
    /* NVRAM for Data Account Application. */
#define NVRAM_DATA_ACCOUNT_RECORD_SIZE    200
#define NVRAM_DATA_ACCOUNT_RECORD_TOTAL   4

    /* NVRAM for Call Time */
#define NVRAM_CALL_TIME_RECORD_SIZE       8
#ifdef __MMI_DUAL_SIM_MASTER__
#define NVRAM_CALL_TIME_RECORD_TOTAL      6
#else /* __MMI_DUAL_SIM_MASTER__ */
#ifdef __MMI_VOIP__
#define NVRAM_CALL_TIME_RECORD_TOTAL      6
#else /* __MMI_VOIP__ */
#define NVRAM_CALL_TIME_RECORD_TOTAL      3
#endif /* __MMI_VOIP__ */
#endif /* __MMI_DUAL_SIM_MASTER__ */

#ifdef __TCPIP_OVER_CSD__
/**
 * CSD profile
 */
/*[MAUI_00778420]*/
#if defined(__L4_MAX_NAME_60__)
#define NVRAM_EF_CSD_PROFILE_SIZE               216    
#else 
#define NVRAM_EF_CSD_PROFILE_SIZE               186    
#endif 
#define NVRAM_EF_CSD_PROFILE_TOTAL              10
#endif /* __TCPIP_OVER_CSD__ */ 

/**
 * External Melody
 */
#define NVRAM_EF_EXT_MELODY_INFO_SIZE              1748 /* 1696 */
#define NVRAM_EF_EXT_MELODY_INFO_TOTAL             1

/**
 * PHB
 */

#if defined(__L4_MAX_NAME_60__)
#define NVRAM_EF_PHB_SIZE                  116
#else 
#define NVRAM_EF_PHB_SIZE                  86
#endif 
#define NVRAM_EF_PHB_TOTAL                MAX_PHB_PHONE_ENTRY

#if defined(__L4_MAX_NAME_60__)
#define NVRAM_EF_PHB_LN_ENTRY_SIZE_TEMP     1244
#elif defined(__L4_MAX_NAME_20__)
#define NVRAM_EF_PHB_LN_ENTRY_SIZE_TEMP      824
#else 
#define NVRAM_EF_PHB_LN_ENTRY_SIZE_TEMP      924
#endif 

#ifdef __VOIP__
#define NVRAM_EF_PHB_LN_ENTRY_SIZE (NVRAM_EF_PHB_LN_ENTRY_SIZE_TEMP + (VOIP_URI_LEN - 41)*10)
#else 
#define NVRAM_EF_PHB_LN_ENTRY_SIZE (NVRAM_EF_PHB_LN_ENTRY_SIZE_TEMP)
#endif 

#if (MAX_PHB_LN_ENTRY > 20)
#define NVRAM_EF_PHB_LN_ENTRY_TOTAL    ((((MAX_PHB_LN_ENTRY+9)/10)*3)*NVRAM_DUAL_RECORD)
#else 
#define NVRAM_EF_PHB_LN_ENTRY_TOTAL    (6*NVRAM_DUAL_RECORD)
#endif 

#define NVRAM_EF_PHB_LN_TYPE_SEQ_SIZE (NVRAM_EF_PHB_LN_ENTRY_TOTAL*10/NVRAM_DUAL_RECORD)       /* same as NVRAM_EF_PHB_LN_TYPE_SEQ_ENTRY_SIZE */
#define NVRAM_EF_PHB_LN_TYPE_SEQ_TOTAL (1*NVRAM_DUAL_RECORD)

#if defined(__MMI_OP11_HOMESCREEN__) || defined(__MMI_OP12_TOOLBAR__) || defined(__MMI_VUI_HOMESCREEN__)
#define NVRAM_EF_CHIST_MISS_ACCUM_TIMES_SIZE MAX_PHB_LN_ENTRY
#define NVRAM_EF_CHIST_MISS_ACCUM_TIMES_TOTAL 1

#define NVRAM_EF_CHIST_MISS_EVENT_CHECK_SIZE MAX_PHB_LN_ENTRY
#define NVRAM_EF_CHIST_MISS_EVENT_CHECK_TOTAL 1
#endif /* defined(__MMI_OP11_HOMESCREEN__) || defined(__MMI_OP12_TOOLBAR__) || defined(__MMI_VUI_HOMESCREEN__) */

#ifdef __MMI_PHB_ICE_CONTACT__
#define NVRAM_EF_PHB_ICE_CONTACT_SIZE   ((MAX_PB_NUMBER_LENGTH + 1 + 1) * MMI_PHB_ICE_CONTACT_COUNT * 2)
#define NVRAM_EF_PHB_ICE_CONTACT_TOTAL  1
#endif /* __MMI_PHB_ICE_CONTACT__ */

#if !defined(__MMI_PHB_NO_OPTIONAL_FIELD__)
#ifdef __MMI_PHB_OPTIONAL_FIELDS_2ND_EMAIL__
#define NVRAM_PHB_FIELDS_SIZE          (169 + MAX_PB_EMAIL_LENGTH * 2)
#else /* __MMI_PHB_OPTIONAL_FIELDS_2ND_EMAIL__ */
#define NVRAM_PHB_FIELDS_SIZE          (169 + MAX_PB_EMAIL_LENGTH)
#endif /* __MMI_PHB_OPTIONAL_FIELDS_2ND_EMAIL__ */
#endif /* !defined(__MMI_PHB_NO_OPTIONAL_FIELD__) */

#define NVRAM_PHB_FIELDS_TOTAL         MAX_PHB_PHONE_ENTRY
#define NVRAM_PHB_SIM_TOTAL            MAX_PHB_SIM_ENTRY

#define NVRAM_PHB_IDS_RECORD_COUNT     85
#define NVRAM_PHB_IDS_SIZE             510      /* For 85 entries in one NVRAM record. */

#if defined(__MMI_PHB_CALLERGROUP_IN_SIM__)
#define NVRAM_PHB_IDS_TOTAL            ((NVRAM_PHB_FIELDS_TOTAL+NVRAM_PHB_SIM_TOTAL-1) /  NVRAM_PHB_IDS_RECORD_COUNT + 1)
#else 
#define NVRAM_PHB_IDS_TOTAL             ((NVRAM_PHB_FIELDS_TOTAL-1) /  NVRAM_PHB_IDS_RECORD_COUNT + 1)
#endif 

#if defined(__MMI_INCOMING_CALL_VIDEO__)
#define NVRAM_EF_PHB_VIDEO_COUNT    500
#define NVRAM_EF_PHB_VIDEO_SIZE     1000
#define NVRAM_EF_PHB_VIDEO_TOTAL    ((NVRAM_PHB_FIELDS_TOTAL-1) /  NVRAM_EF_PHB_VIDEO_COUNT + 1)
#endif /* defined(__MMI_INCOMING_CALL_VIDEO__) */ 

#if defined(__MMI_PHB_BIRTHDAY_FIELD__)
#define NVRAM_EF_PHB_BIRTHDAY_COUNT 250 /* 250 item in each record */
#define NVRAM_EF_PHB_BIRTHDAY_SIZE     1000     /* 4 bytes for each item, 4*250 = 1000 */
#define NVRAM_EF_PHB_BIRTHDAY_TOTAL    ((NVRAM_PHB_FIELDS_TOTAL-1) /  NVRAM_EF_PHB_BIRTHDAY_COUNT + 1)
#endif /* defined(__MMI_PHB_BIRTHDAY_FIELD__) */ 

#if defined(__MMI_PHB_INFO_FIELD__)
#define NVRAM_EF_PHB_INFO_SIZE         597
#define NVRAM_EF_PHB_INFO_TOTAL        MAX_PHB_PHONE_ENTRY
#define NVRAM_EF_PHB_INFO_OCCUPIED_SIZE         1
#define NVRAM_EF_PHB_INFO_OCCUPIED_TOTAL        MAX_PHB_PHONE_ENTRY
#endif /* defined(__MMI_PHB_INFO_FIELD__) */ 
#if defined(__MMI_PHB_USIM_FIELD__)
#define NVRAM_EF_PHB_SNE_SIZE          62
#define NVRAM_EF_PHB_SNE_TOTAL         MAX_PHB_PHONE_ENTRY
#endif /* defined(__MMI_PHB_USIM_FIELD__) */ 
#if defined(__MMI_IMPS__) /* for phb imps field */
#define NVRAM_EF_PHB_IMPS_SIZE            62
#define NVRAM_EF_PHB_IMPS_TOTAL        MAX_PHB_PHONE_ENTRY
#endif /* defined(__MMI_IMPS__) */ 

#if defined(__MMI_PHB_POC_FIELD__)
#define NVRAM_EF_PHB_POC_SIZE          64
#define NVRAM_EF_PHB_POC_TOTAL         MAX_PHB_PHONE_ENTRY
#endif /* defined(__MMI_PHB_POC_FIELD__) */ 

#if defined(__MMI_VOIP__)
#define NVRAM_EF_PHB_VOIP_SIZE         VOIP_URI_LEN
#define NVRAM_EF_PHB_VOIP_TOTAL        MAX_PHB_PHONE_ENTRY
#endif /* defined(__MMI_VOIP__) */ 

#ifdef __MMI_PHB_GROUP_10_ITEMS__
#define NVRAM_PHB_CALLER_GROUPS_SIZE         (260*2)
#else  /* __MMI_PHB_GROUP_10_ITEMS__ */
#define NVRAM_PHB_CALLER_GROUPS_SIZE         260
#endif /* __MMI_PHB_GROUP_10_ITEMS__ */

#define NVRAM_PHB_CALLER_GROUPS_TOTAL     1

#if defined(__MMI_PHB_EMAIL_SORT__)
#if defined(__MMI_PHB_USIM_FIELD__)
#define NVRAM_PHB_EMAIL_SORT_SIZE         ((NVRAM_PHB_FIELDS_TOTAL+NVRAM_PHB_SIM_TOTAL)*2)
#else 
#define NVRAM_PHB_EMAIL_SORT_SIZE         NVRAM_PHB_FIELDS_TOTAL*2
#endif 
#define NVRAM_PHB_EMAIL_SORT_TOTAL     1
#endif /* defined(__MMI_PHB_EMAIL_SORT__) */ 

#ifdef __MMI_PHB_MAX_NAME_60__
#ifdef __MMI_PHB_OPTIONAL_FIELDS_2ND_EMAIL__
#define NVRAM_PHB_VCARD_LID_SIZE (338 + MAX_PB_EMAIL_LENGTH * 2)
#else
#define NVRAM_PHB_VCARD_LID_SIZE        (338 + MAX_PB_EMAIL_LENGTH)
#endif /* __MMI_PHB_OPTIONAL_FIELDS_2ND_EMAIL__ */
#else /* __MMI_PHB_MAX_NAME_60__ */
#ifdef __MMI_PHB_OPTIONAL_FIELDS_2ND_EMAIL__
#define NVRAM_PHB_VCARD_LID_SIZE (278 + MAX_PB_EMAIL_LENGTH * 2)
#else 
#define NVRAM_PHB_VCARD_LID_SIZE        (278 + MAX_PB_EMAIL_LENGTH)
#endif /* __MMI_PHB_OPTIONAL_FIELDS_2ND_EMAIL__ */
#endif /* __MMI_PHB_MAX_NAME_60__ */

#define NVRAM_PHB_VCARD_LID_TOTAL       1

#define NVRAM_PHONEBOOK_SOS_RECORD_SIZE            86
#define NVRAM_PHONEBOOK_SOS_RECORD_TOTAL        10

#if defined(__MMI_PHB_MAX_NAME_60__)
#define NVRAM_PHONEBOOK_SPEEDDIAL_RECORD_SIZE      1680
#else 
#define NVRAM_PHONEBOOK_SPEEDDIAL_RECORD_SIZE      1200
#endif 
#define NVRAM_PHONEBOOK_SPEEDDIAL_RECORD_TOTAL  1

#if defined(__MMI_EMERGENCY_SMS__)
#define NVRAM_EMERGENCY_SMS_RECORD_SIZE      1200
#define NVRAM_EMERGENCY_SMS_RECORD_TOTAL  1
#define NVRAM_EMERGENCY_SMS_CONTENT_SIZE (200 * ENCODING_LENGTH)
#define NVRAM_EMERGENCY_SMS_CONTENT_TOTAL 1
#endif

#define NVRAM_PHB_SETTINGS_SIZE        20       /* Phonebook may use less setting fields than this value */
#define NVRAM_PHB_SETTINGS_TOTAL       1

#ifdef __MMI_AVATAR__
/**
 * AVATAR Settings
 */
#define NVRAM_EF_AVATAR_SETTING_TOTAL       1
#define NVRAM_EF_AVATAR_SETTING_SIZE        512
#endif

#ifdef __MMI_MOBILE_TV_PLAYER__
/**
 * Mobile TV Player Settings
 */
#define NVRAM_EF_MOBILE_TV_PLAYER_SETTING_TOTAL       1
#define NVRAM_EF_MOBILE_TV_PLAYER_SETTING_SIZE       52
#endif

#ifdef __MMI_BARCODEREADER__
/**
 * Barcode Reader Settings
 */
#define NVRAM_EF_BARCODEREADER_SETTING_TOTAL       1
#define NVRAM_EF_BARCODEREADER_SETTING_SIZE        30

#if defined(__MMI_OP11_BARCODEREADER__)
/* under construction !*/
/* under construction !*/
    #endif
#endif

#ifdef __MMI_BCR__
/**
 * BCR Settings
 */
#define NVRAM_EF_BCR_SETTING_TOTAL       1
#define NVRAM_EF_BCR_SETTING_SIZE        32

#define NVRAM_EF_BCR_FIELD_SET_TOTAL     1
#define NVRAM_EF_BCR_FIELD_SET_SIZE      32

#endif

#ifdef __MMI_IPSEC__
/**
 * IPSec Settings MMI
 */
#define NVRAM_EF_IPSEC_POLICY_TOTAL                 3
#define NVRAM_EF_IPSEC_POLICY_SIZE                  sizeof(nvram_ef_ipsec_policy_struct)
#define NVRAM_EF_IPSEC_IKE_TOTAL                    3
#define NVRAM_EF_IPSEC_IKE_SIZE                     sizeof(nvram_ef_ipsec_ike_struct) 
#endif /* __MMI_IPSEC__ */

#if defined (__MMI_CAMERA__) && !defined(__MMI_CAMCORDER__)
/**
 * Camera Settings
 */
#define NVRAM_EF_CAMERA_SETTING_TOTAL              1
#define NVRAM_EF_CAMERA_SETTING_SIZE               84
#endif /* defined (__MMI_CAMERA__) && !defined(__MMI_CAMCORDER__) */

#if defined (__MMI_VIDEO_RECORDER__) && !defined(__MMI_CAMCORDER__)
/**
 * Video Settings
 */
#define NVRAM_EF_VIDEO_SETTING_TOTAL               1
#define NVRAM_EF_VIDEO_SETTING_SIZE                135
#endif /* defined (__MMI_VIDEO_RECORDER__) && !defined(__MMI_CAMCORDER__) */ 

#ifdef __MMI_PHOTOEDITOR__
/**
 * Photo Editor Settings
 */
#define NVRAM_EF_PHOTO_EDITOR_SETTING_TOTAL        1
#define NVRAM_EF_PHOTO_EDITOR_SETTING_SIZE         200
#endif /* __MMI_PHOTOEDITOR__ */ 


#ifdef __VRE_V2X__
#define	NVRAM_EF_VRE_PKEY_LIST_SIZE  1824
#define	NVRAM_EF_VRE_PKEY_LIST_TOTAL 2

#define	NVRAM_EF_VRE_APP_BAN_LIST_SIZE  1048
#define	NVRAM_EF_VRE_APP_BAN_LIST_TOTAL 1

#define	NVRAM_EF_VRE_SYM_ENTRY_LIST_SIZE 1604
#define	NVRAM_EF_VRE_SYM_ENTRY_LIST_TOTAL 1

#define	NVRAM_EF_VRE_SYM_CONF_LIST_SIZE  	128
#define	NVRAM_EF_VRE_SYM_CONF_LIST_TOTAL	1

#define	NVRAM_EF_VRE_PAY_CHANNEL_ORG_LIST_SIZE	604
#define	NVRAM_EF_VRE_PAY_CHANNEL_ORG_LIST_TOTAL 	1

#define	NVRAM_EF_VRE_PAY_CHANNEL_LIST_SIZE		1920
#define	NVRAM_EF_VRE_PAY_CHANNEL_LIST_TOTAL	1

#define	NVRAM_EF_VRE_APP_STATE_LIST_SIZE	1600
#define	NVRAM_EF_VRE_APP_STATE_LIST_TOTAL	5

#define	NVRAM_EF_VRE_APPSTORE_CONFIG_LIST_SZIE 8
#define	NVRAM_EF_VRE_APPSTORE_CONFIG_LIST_TOTAL 1
#endif
#ifdef __VRE_V30__
#define	NVRAM_EF_VRE_PKEY_LIST_EXT_SIZE  1832
#define	NVRAM_EF_VRE_PKEY_LIST_EXT_TOTAL 2

#define	NVRAM_EF_VRE_APP_BAN_LIST_EXT_SIZE  1056
#define	NVRAM_EF_VRE_APP_BAN_LIST_EXT_TOTAL 1

#define	NVRAM_EF_VRE_SYM_ENTRY_LIST_EXT_SIZE 1608
#define	NVRAM_EF_VRE_SYM_ENTRY_LIST_EXT_TOTAL 1

#define	NVRAM_EF_VRE_SYM_CONF_LIST_EXT_SIZE  	136
#define	NVRAM_EF_VRE_SYM_CONF_LIST_EXT_TOTAL	1

#define	NVRAM_EF_VRE_PAY_CHANNEL_LIST_EXT_SIZE		1928
#define	NVRAM_EF_VRE_PAY_CHANNEL_LIST_EXT_TOTAL	2

#define	NVRAM_EF_VRE_APP_STATE_LIST_EXT_SIZE	1608
#define	NVRAM_EF_VRE_APP_STATE_LIST_EXT_TOTAL	5

#define	NVRAM_EF_VRE_APPSTORE_CONFIG_LIST_EXT_SIZE 16
#define	NVRAM_EF_VRE_APPSTORE_CONFIG_LIST_EXT_TOTAL 1

#define	NVRAM_EF_VRE_APPSTORE3_CONFIG_LIST_EXT_SIZE 32
#define	NVRAM_EF_VRE_APPSTORE3_CONFIG_LIST_EXT_TOTAL 1

#define	NVRAM_EF_VRE_FIRST_RUNNING_SIZE 1
#define	NVRAM_EF_VRE_FIRST_RUNNING_TOTAL 1

#define	NVRAM_EF_VRE_CHARGE_DETAIL_LIST_EXT_SIZE 1032
#define	NVRAM_EF_VRE_CHARGE_DETAIL_LIST_EXT_TOTAL 1

#define	NVRAM_EF_VRE_CHARGE_SMS_DETAIL_LIST_EXT_SIZE 1800
#define	NVRAM_EF_VRE_CHARGE_SMS_DETAIL_LIST_EXT_TOTAL 1

#define	NVRAM_EF_VRE_PAY_CONFIG_EXT_SIZE 24
#define	NVRAM_EF_VRE_PAY_CONFIG_EXT_TOTAL 1

#define	NVRAM_EF_VRE_OPERATOR_CODE_EXT_SIZE 264
#define	NVRAM_EF_VRE_OPERATOR_CODE_EXT_TOTAL 1
#endif

#ifdef __VRE30_AM__
#define	NVRAM_EF_AM_HS_SHORTCUT_LIST_SIZE sizeof(nvram_am_hs_shortcut_t)
#define	NVRAM_EF_AM_HS_SHORTCUT_LIST_TOTAL 5
#endif
/**
 * File Manager FilePath Pool Settings
 */
#if defined (__MMI_CAMERA__) || defined(__MMI_CAMCORDER__)
#define NVRAM_EF_FMGR_FILEPATH_CAMERA             1
#else
#define NVRAM_EF_FMGR_FILEPATH_CAMERA             0
#endif

#if defined(__MMI_VIDEO_PLAYER__) || (defined(__MMI_VIDEO_RECORDER__) || defined(__MMI_CAMCORDER__))
#define NVRAM_EF_FMGR_FILEPATH_VIDEO              1
#else
#define NVRAM_EF_FMGR_FILEPATH_VIDEO              0
#endif

#ifdef __MMI_PHOTOEDITOR__
#define NVRAM_EF_FMGR_FILEPATH_PHOEDT             1
#else
#define NVRAM_EF_FMGR_FILEPATH_PHOEDT             0
#endif

#ifdef __MMI_VIDEO_STREAM__
#define NVRAM_EF_FMGR_FILEPATH_VIDEO_STREAM       1
#else
#define NVRAM_EF_FMGR_FILEPATH_VIDEO_STREAM       0
#endif

#ifdef __MMI_VIDEO_EDITOR__
#define NVRAM_EF_FMGR_FILEPATH_VDOEDT            1
#else
#define NVRAM_EF_FMGR_FILEPATH_VDOEDT            0
#endif /* __MMI_VIDEO_EDITOR__ */

#ifdef __MMI_SLIDESHOW__
#define NVRAM_EF_FMGR_FILEPATH_SLIDESHOW          2
#else
#define NVRAM_EF_FMGR_FILEPATH_SLIDESHOW          0
#endif

#if defined(__MMI_IMAGE_VIEWER__) || defined(__MMI_FILE_MANAGER__)
#define NVRAM_EF_FMGR_FILEPATH_IMAGE_VIEWER          2
#else
#define NVRAM_EF_FMGR_FILEPATH_IMAGE_VIEWER          0
#endif

#if defined(MOTION_SENSOR_SUPPORT)
#define NVRAM_EF_FMGR_FILEPATH_MOTION_WP       1
#else
#define NVRAM_EF_FMGR_FILEPATH_MOTION_WP       0
#endif


#define NVRAM_EF_FMGR_FILEPATH_COUNT              (NVRAM_EF_FMGR_FILEPATH_CAMERA + \
                                                   NVRAM_EF_FMGR_FILEPATH_VIDEO + \
                                                   NVRAM_EF_FMGR_FILEPATH_PHOEDT + \
                                                   NVRAM_EF_FMGR_FILEPATH_VIDEO_STREAM + \
                                                   NVRAM_EF_FMGR_FILEPATH_VDOEDT + \
                                                   NVRAM_EF_FMGR_FILEPATH_SLIDESHOW + \
                                                   NVRAM_EF_FMGR_FILEPATH_IMAGE_VIEWER)

#define NVRAM_EF_FMGR_FILEPATH_POOL_HEAD_TOTAL     NVRAM_EF_FMGR_FILEPATH_COUNT
#define NVRAM_EF_FMGR_FILEPATH_POOL_HEAD_SIZE      510
#define NVRAM_EF_FMGR_FILEPATH_POOL_TAIL_TOTAL     NVRAM_EF_FMGR_FILEPATH_COUNT
#define NVRAM_EF_FMGR_FILEPATH_POOL_TAIL_SIZE      10

#ifdef __PS_SERVICE__
/**
 * ABM_GPRS_PROFILE
 */
#ifdef __MMI_OP01_GPRS_DATACFG__
/* under construction !*/
#else
#if 0  //def __SLIM_NWK_PROFILE__
#define NVRAM_EF_ABM_GPRS_PROFILE_TOTAL            5
#else
    //#ifdef __TL_NVRAM_CUSTOM_WAP_MMS_NUM__
    //    #define NVRAM_EF_ABM_GPRS_PROFILE_TOTAL    __TL_NVRAM_CUSTOM_WAP_MMS_NUM__
    //#else
#define NVRAM_EF_ABM_GPRS_PROFILE_TOTAL            10
    //#endif
#endif
#endif /* __MMI_OP01_GPRS_DATACFG__ */

#define NVRAM_EF_ABM_GPRS_PROFILE_SIZE             252
#define NVRAM_EF_ABM_PS_QOS_PROFILE_TOTAL          2
#define NVRAM_EF_ABM_PS_QOS_PROFILE_SIZE             56

#endif /* __PS_SERVICE__ */ 

    /* changes for the Greeting Text */
#define NVRAM_SETTING_SIZE                      60
#define NVRAM_SETTING_TOTAL                     1

/**
 * IMEI/IMEISV
 */
#define NVRAM_EF_IMEI_IMEI_SIZE           8
#define NVRAM_EF_IMEI_IMEISV_SIZE         10
#define NVRAM_EF_IMEI_IMEISV_TOTAL        (1 * NVRAM_DUAL_RECORD)

/**
 * ADC
 */

#define NVRAM_EF_ADC_SIZE        (ADC_MAX_CHANNEL * 8)


#define NVRAM_EF_ADC_TOTAL      1

/**
 * Serial Number
 */
#define NVRAM_EF_BARCODE_NUM_SIZE       64
#define NVRAM_EF_BARCODE_NUM_TOTAL    1

/**
 * UEM Manufacturer data
 */
#define NVRAM_EF_UEM_MANUFACTURE_DATA_SIZE         240
#define NVRAM_EF_UEM_MANUFACTURE_DATA_TOTAL        1

/**
 * UEM RMI data
 */
#define NVRAM_EF_UEM_RMI_DATA_SIZE                 216  /* 182 */
#define NVRAM_EF_UEM_RMI_DATA_TOTAL                1

/**
 * SMSAL common parameters
 */
#define NVRAM_EF_SMSAL_COMMON_PARAM_SIZE           16
#define NVRAM_EF_SMSAL_COMMON_PARAM_TOTAL          (1 * NVRAM_DUAL_RECORD)

/**
 * SMSAL mailbox addresses
 */
#define NVRAM_EF_SMSAL_MAILBOX_ADDR_SIZE           34
#define NVRAM_EF_SMSAL_MAILBOX_ADDR_TOTAL          (2 * NVRAM_DUAL_RECORD)

/**
 * SMSAL short messages
 */
#define NVRAM_EF_SMSAL_SMS_SIZE              184
/*#if defined(LOW_COST_SUPPORT)
#define NVRAM_EF_SMSAL_SMS_TOTAL             (10 * NVRAM_DUAL_RECORD)
#else
#define NVRAM_EF_SMSAL_SMS_TOTAL             (200 * NVRAM_DUAL_RECORD)
#endif // LOW_COST_SUPPORT
*/
#define NVRAM_EF_SMSAL_SMS_TOTAL    (SMS_PHONE_ENTRY * NVRAM_DUAL_RECORD)

/**
 * CB Default Channel Setting
 */
#define NVRAM_EF_CB_DEFAULT_CH_SIZE          20
#define NVRAM_EF_CB_DEFAULT_CH_TOTAL         (1 * NVRAM_DUAL_RECORD)

/**
 * SMSAL short message service parameters
 */
#define NVRAM_EF_SMSAL_SMSP_SIZE           40   /* 28(SMSAL_SMSP_LEN)+10 */
#define NVRAM_EF_SMSAL_SMSP_TOTAL          (2 * NVRAM_DUAL_RECORD)

#if defined (__PS_SERVICE__) && defined (__MOD_TCM__)
/**
 * TCM PDP profile
 */
#define NVRAM_EF_TCM_PDP_PROFILE_SIZE          (sizeof(nvram_ef_tcm_PDP_profile_record_struct)) //erica 20070112
#define NVRAM_EF_TCM_PDP_PROFILE_TOTAL       11
#endif // ~ #if defined (__PS_SERVICE__) && defined (__MOD_TCM__)

#if defined (__PS_SERVICE__) && defined (__MOD_TCM__) && defined (__TCM_EXT_CALL_HISTORY_SUPPORT__)
/**
 * TCM external ps call history
 */
#define NVRAM_EF_TCM_EXT_CALL_HISTORY_SIZE (sizeof(nvram_ef_tcm_ext_call_history_struct))
#define NVRAM_EF_TCM_EXT_CALL_HISTORY_TOTAL (1 * NVRAM_DUAL_RECORD)
#endif // ~ #if defined (__PS_SERVICE__) && defined (__MOD_TCM__) && defined (__TCM_EXT_CALL_HISTORY_SUPPORT__)

/**
 * Camera parameters for driver layers
 */
#if defined(ISP_SUPPORT) && (!defined(DRV_ISP_6238_SERIES)) && (!defined(BACKUP_SENSOR_SUPPORT))
#define NVRAM_EF_CAMERA_PARA_SIZE      sizeof(nvram_camera_para_struct)
#define NVRAM_EF_CAMERA_PARA_TOTAL     1
#endif /* defined(ISP_SUPPORT) && (!defined(DRV_ISP_6238_SERIES)) && (!defined(BACKUP_SENSOR_SUPPORT)) */ 

#if defined(ISP_SUPPORT) && defined(DRV_ISP_6235_SERIES) && defined(BACKUP_SENSOR_SUPPORT)
#define NVRAM_EF_CAMERA_PARA_MAIN_SIZE          sizeof(nvram_camera_para_struct)
#define NVRAM_EF_CAMERA_PARA_MAIN_TOTAL         1
#define NVRAM_EF_CAMERA_PARA_MAIN_BAK1_SIZE     sizeof(nvram_camera_para_struct)
#define NVRAM_EF_CAMERA_PARA_MAIN_BAK1_TOTAL    1
#endif /* defined(ISP_SUPPORT) && defined(DRV_ISP_6235_SERIES) && defined(BACKUP_SENSOR_SUPPORT) */

#if defined(ISP_SUPPORT) && (defined(DRV_ISP_6227_SERIES) || defined(DRV_ISP_6229_SERIES))
#define NVRAM_EF_CAMERA_GAMMA_SIZE     sizeof(nvram_camera_gamma_struct)
#define NVRAM_EF_CAMERA_GAMMA_TOTAL    1
#endif /* defined(ISP_SUPPORT) && (defined(DRV_ISP_6227_SERIES) || defined(DRV_ISP_6229_SERIES)) */ 
#if defined(ISP_SUPPORT) && (defined(DRV_ISP_6227_SERIES) || defined(DRV_ISP_6229_SERIES) || defined(DRV_ISP_6228_SERIES))
#define NVRAM_EF_CAMERA_DEFECT_SIZE   sizeof(nvram_camera_defect_struct)
#define NVRAM_EF_CAMERA_DEFECT_TOTAL   1
#endif /* defined(ISP_SUPPORT) && (defined(DRV_ISP_6227_SERIES) || defined(DRV_ISP_6229_SERIES) || defined(DRV_ISP_6228_SERIES)) */ 
#if defined(ISP_SUPPORT) && (defined(DRV_ISP_6227_SERIES) || defined(DRV_ISP_6229_SERIES) || defined(DRV_ISP_6228_SERIES))
#define NVRAM_EF_CAMERA_LENS_SIZE     sizeof(nvram_camera_lens_struct)
#define NVRAM_EF_CAMERA_LENS_TOTAL     1
#endif /* defined(ISP_SUPPORT) && (defined(DRV_ISP_6227_SERIES) || defined(DRV_ISP_6229_SERIES) || defined(DRV_ISP_6228_SERIES)) */ 

/* 6238 camera */
#if (defined(ISP_SUPPORT) && defined(DRV_ISP_6238_SERIES))
#if(!(defined(DUAL_CAMERA_SUPPORT) || defined(BACKUP_SENSOR_SUPPORT)))
#define NVRAM_EF_CAMERA_PARA1_SIZE      sizeof(nvram_camera_para_struct)
#define NVRAM_EF_CAMERA_PARA1_TOTAL     1
#define NVRAM_EF_CAMERA_PARA2_SIZE      sizeof(nvram_camera_3a_struct)
#define NVRAM_EF_CAMERA_PARA2_TOTAL     1
#define NVRAM_EF_CAMERA_DEFECT1_SIZE      sizeof(nvram_camera_defect1_struct)
#define NVRAM_EF_CAMERA_DEFECT1_TOTAL     1
#define NVRAM_EF_CAMERA_DEFECT2_SIZE      sizeof(nvram_camera_defect2_struct)
#define NVRAM_EF_CAMERA_DEFECT2_TOTAL     1
#define NVRAM_EF_CAMERA_SHADING1_SIZE      sizeof(nvram_camera_shading1_struct)
#define NVRAM_EF_CAMERA_SHADING1_TOTAL     1
#define NVRAM_EF_CAMERA_SHADING2_SIZE      sizeof(nvram_camera_shading2_struct)
#define NVRAM_EF_CAMERA_SHADING2_TOTAL     1
#else
#define NVRAM_EF_CAMERA_PARA1_MAIN_SIZE         sizeof(nvram_camera_para_struct)
#define NVRAM_EF_CAMERA_PARA1_MAIN_TOTAL        1
#define NVRAM_EF_CAMERA_PARA2_MAIN_SIZE         sizeof(nvram_camera_3a_struct)
#define NVRAM_EF_CAMERA_PARA2_MAIN_TOTAL        1
#define NVRAM_EF_CAMERA_DEFECT1_MAIN_SIZE       sizeof(nvram_camera_defect1_struct)
#define NVRAM_EF_CAMERA_DEFECT1_MAIN_TOTAL      1
#define NVRAM_EF_CAMERA_DEFECT2_MAIN_SIZE       sizeof(nvram_camera_defect2_struct)
#define NVRAM_EF_CAMERA_DEFECT2_MAIN_TOTAL      1
#define NVRAM_EF_CAMERA_SHADING1_MAIN_SIZE      sizeof(nvram_camera_shading1_struct)
#define NVRAM_EF_CAMERA_SHADING1_MAIN_TOTAL     1
#define NVRAM_EF_CAMERA_SHADING2_MAIN_SIZE      sizeof(nvram_camera_shading2_struct)
#define NVRAM_EF_CAMERA_SHADING2_MAIN_TOTAL     1

#if (defined(CMOS_SENSOR_SUB)) /*keep this sequence*/
#define NVRAM_EF_CAMERA_PARA1_SUB_SIZE          sizeof(nvram_camera_para_struct)
#define NVRAM_EF_CAMERA_PARA1_SUB_TOTAL         1
#define NVRAM_EF_CAMERA_PARA2_SUB_SIZE          sizeof(nvram_camera_3a_struct)
#define NVRAM_EF_CAMERA_PARA2_SUB_TOTAL         1
#define NVRAM_EF_CAMERA_DEFECT1_SUB_SIZE        sizeof(nvram_camera_defect1_struct)
#define NVRAM_EF_CAMERA_DEFECT1_SUB_TOTAL       1
#define NVRAM_EF_CAMERA_DEFECT2_SUB_SIZE        sizeof(nvram_camera_defect2_struct)
#define NVRAM_EF_CAMERA_DEFECT2_SUB_TOTAL       1
#define NVRAM_EF_CAMERA_SHADING1_SUB_SIZE       sizeof(nvram_camera_shading1_struct)
#define NVRAM_EF_CAMERA_SHADING1_SUB_TOTAL      1
#define NVRAM_EF_CAMERA_SHADING2_SUB_SIZE       sizeof(nvram_camera_shading2_struct)
#define NVRAM_EF_CAMERA_SHADING2_SUB_TOTAL      1
#endif

#if (defined(CMOS_SENSOR_BAK1)) /*keep this sequence*/
#define NVRAM_EF_CAMERA_PARA1_MAIN_BAK1_SIZE        sizeof(nvram_camera_para_struct)
#define NVRAM_EF_CAMERA_PARA1_MAIN_BAK1_TOTAL       1
#define NVRAM_EF_CAMERA_PARA2_MAIN_BAK1_SIZE        sizeof(nvram_camera_3a_struct)
#define NVRAM_EF_CAMERA_PARA2_MAIN_BAK1_TOTAL       1
#define NVRAM_EF_CAMERA_DEFECT1_MAIN_BAK1_SIZE      sizeof(nvram_camera_defect1_struct)
#define NVRAM_EF_CAMERA_DEFECT1_MAIN_BAK1_TOTAL     1
#define NVRAM_EF_CAMERA_DEFECT2_MAIN_BAK1_SIZE      sizeof(nvram_camera_defect2_struct)
#define NVRAM_EF_CAMERA_DEFECT2_MAIN_BAK1_TOTAL     1
#define NVRAM_EF_CAMERA_SHADING1_MAIN_BAK1_SIZE     sizeof(nvram_camera_shading1_struct)
#define NVRAM_EF_CAMERA_SHADING1_MAIN_BAK1_TOTAL    1
#define NVRAM_EF_CAMERA_SHADING2_MAIN_BAK1_SIZE     sizeof(nvram_camera_shading2_struct)
#define NVRAM_EF_CAMERA_SHADING2_MAIN_BAK1_TOTAL    1
#endif

#if (defined(CMOS_SENSOR_SUB_BAK1)) /*keep this sequence*/
#define NVRAM_EF_CAMERA_PARA1_SUB_BAK1_SIZE         sizeof(nvram_camera_para_struct)
#define NVRAM_EF_CAMERA_PARA1_SUB_BAK1_TOTAL        1
#define NVRAM_EF_CAMERA_PARA2_SUB_BAK1_SIZE         sizeof(nvram_camera_3a_struct)
#define NVRAM_EF_CAMERA_PARA2_SUB_BAK1_TOTAL        1
#define NVRAM_EF_CAMERA_DEFECT1_SUB_BAK1_SIZE       sizeof(nvram_camera_defect1_struct)
#define NVRAM_EF_CAMERA_DEFECT1_SUB_BAK1_TOTAL      1
#define NVRAM_EF_CAMERA_DEFECT2_SUB_BAK1_SIZE       sizeof(nvram_camera_defect2_struct)
#define NVRAM_EF_CAMERA_DEFECT2_SUB_BAK1_TOTAL      1
#define NVRAM_EF_CAMERA_SHADING1_SUB_BAK1_SIZE      sizeof(nvram_camera_shading1_struct)
#define NVRAM_EF_CAMERA_SHADING1_SUB_BAK1_TOTAL     1
#define NVRAM_EF_CAMERA_SHADING2_SUB_BAK1_SIZE      sizeof(nvram_camera_shading2_struct)
#define NVRAM_EF_CAMERA_SHADING2_SUB_BAK1_TOTAL     1
#endif
#endif /* !(defined(DUAL_CAMERA_SUPPORT) || defined(BACKUP_SENSOR_SUPPORT))) */
#endif /* defined(ISP_SUPPORT) && 6238 */ 

#define NVRAM_EF_CAMERA_MAIN_SENSOR_ID_SIZE     4
#define NVRAM_EF_CAMERA_MAIN_SENSOR_ID_TOTAL    1
#if defined(DUAL_CAMERA_SUPPORT)
#define NVRAM_EF_CAMERA_SUB_SENSOR_ID_SIZE      4
#define NVRAM_EF_CAMERA_SUB_SENSOR_ID_TOTAL     1
#endif
/**
 * Wallpaper and Screensaver file name
 */
#define NVRAM_EF_WPSS_FILENAME_SIZE    1228
#define NVRAM_EF_WPSS_FILENAME_TOTAL      5     /* diamond, 2005/05/09 for sub-LCD wallpaper */

#define   NVRAM_EF_AUTOTEST_SIZE           250
#define   NVRAM_EF_AUTOTEST_TOTAL        2

/**
 * Port Setting
 */
#define NVRAM_EF_PORT_SETTING_SIZE         sizeof(port_setting_struct)
#define NVRAM_EF_PORT_SETTING_TOTAL        1

#ifdef __MMI_STOPWATCH__
    /*
     * Stopwatch
     */
#ifdef __UCS2_ENCODING
#define NVRAM_EF_STOPWATCH_RECORD_SIZE  1152
#else 
#define NVRAM_EF_STOPWATCH_RECORD_SIZE  980
#endif 
#define NVRAM_EF_STOPWATCH_RECORD_TOTAL   1
#endif /* __MMI_STOPWATCH__ */ 

#ifdef __MMI_PICTURE_EDITOR_SUPPORT__
#define NVRAM_PICTURE_EDITOR_TOTAL 1
#define NVRAM_PICTURE_EDITOR_SIZE  40*5
#endif /* __MMI_PICTURE_EDITOR_SUPPORT__ */ 

#ifdef __UCS2_ENCODING
#define NVRAM_EF_THEME_MANAGER_RECORD_SIZE  1840
#else 
#define NVRAM_EF_THEME_MANAGER_RECORD_SIZE   580
#endif 
#define NVRAM_EF_THEME_MANAGER_RECORD_TOTAL  1

#ifdef __MMI_VRSD__
    /*
     * Voice Recognition - SD
     */
#define NVRAM_EF_VRSD_TAG_SIZE      80
#define NVRAM_EF_VRSD_TAG_TOTAL     1
#endif /* __MMI_VRSD__ */ 

#ifdef __MMI_VRSI__
    /*
     * Voice Recognition - SI
     */
#define NVRAM_EF_VRSI_TAG_SIZE      120
#define NVRAM_EF_VRSI_TAG_TOTAL     1
#endif /* __MMI_VRSI__ */ 
    /*
     * Bluetooth
     */
#ifdef __BT_SUPPORT__
#define NVRAM_EF_BT_INFO_SIZE        2000
#define NVRAM_EF_BT_SYS_INFO_SIZE    60
#define NVRAM_EF_BT_INFO_TOTAL     1

#define NVRAM_EF_BTRADIO_RFMD3500_TOTAL		 1
#ifdef  __NVRAM_EF_BTRADIO_RFMD3500_STRUCT__
   #define NVRAM_EF_BTRADIO_RFMD3500_SIZE       sizeof(nvram_ef_btradio_rfmd3500_struct)
#else
   #define NVRAM_EF_BTRADIO_RFMD3500_SIZE       150
#endif

#define NVRAM_EF_BTRADIO_MT6601_TOTAL		 1
#ifdef  __NVRAM_EF_BTRADIO_MT6601_STRUCT__
   #define NVRAM_EF_BTRADIO_MT6601_SIZE       sizeof(nvram_ef_btradio_mt6601_struct)
#else
   #define NVRAM_EF_BTRADIO_MT6601_SIZE       141
#endif
#define NVRAM_EF_BTRADIO_MT6611_TOTAL		 1
#ifdef  __NVRAM_EF_BTRADIO_MT6611_STRUCT__
   #define NVRAM_EF_BTRADIO_MT6611_SIZE       sizeof(nvram_ef_btradio_mt6611_struct)
#else
   #define NVRAM_EF_BTRADIO_MT6611_SIZE       46
#endif

#define NVRAM_EF_BTRADIO_MT6612_TOTAL		 1
#ifdef  __NVRAM_EF_BTRADIO_MT6612_STRUCT__
   #define NVRAM_EF_BTRADIO_MT6612_SIZE       sizeof(nvram_ef_btradio_mt6612_struct)
#else
   #define NVRAM_EF_BTRADIO_MT6612_SIZE       46
#endif

#define NVRAM_EF_BTRADIO_MT6616_TOTAL		 1
#ifdef  __NVRAM_EF_BTRADIO_MT6616_STRUCT__
   #define NVRAM_EF_BTRADIO_MT6616_SIZE       sizeof(nvram_ef_btradio_mt6616_struct)
#else
   #define NVRAM_EF_BTRADIO_MT6616_SIZE       46
#endif

#endif /* __BT_SUPPORT__ */ 

#ifdef __MMI_CM_BLACK_LIST__
    /*
     * Black list
     */
#define NVRAM_EF_BLACK_LIST_SIZE    44*20
#define NVRAM_EF_BLACK_LIST_TOTAL      1
#endif /* __MMI_CM_BLACK_LIST__ */ 

#ifdef __TL_SMS_BLACK_LIST__
    /*
     * Black list
     */
#define NVRAM_EF_SMS_BLACK_LIST_SIZE    44*20
#define NVRAM_EF_SMS_BLACK_LIST_TOTAL      1
#endif /* __TL_SMS_BLACK_LIST__ */ 

#ifdef __MMI_CM_WHITE_LIST__
    /*
     * White list
     */
#define NVRAM_EF_WHITE_LIST_SIZE    44*20
#define NVRAM_EF_WHITE_LIST_TOTAL      1
#endif /* __MMI_CM_WHITE_LIST__ */ 

#ifdef __MMI_ECOMPASS__
#define NVRAM_EF_ECOMPASS_SIZE       1000
#define NVRAM_EF_ECOMPASS_TOTAL      2
#endif /* __MMI_ECOMPASS__ */ 

#if defined(__MMI_IMPS__)
    /*
     * IMPS
     */
#define NVRAM_EF_IMPS_SIZE    1600
#define NVRAM_EF_IMPS_TOTAL      1
#endif /* defined(__MMI_IMPS__) */ 

#if defined __MMI_PICT_BRIDGE_SUPPORT__
#define NVRAM_EF_PICTBRIDGE_SIZE    100
#define NVRAM_EF_PICTBRIDGE_TOTAL      1
#endif /* __MMI_PICT_BRIDGE_SUPPORT__ */

#ifdef __MMI_AUDIO_EQUALIZER__
    /*
     * Audio Equalizer Settings
     */
#define NVRAM_EF_AUDIO_EQUALIZER_COUNT    8
#define NVRAM_EF_AUDIO_EQUALIZER_SIZE     500
#define NVRAM_EF_AUDIO_EQUALIZER_TOTAL    1
#endif /* __MMI_AUDIO_EQUALIZER__ */ 

    /*
     * Schedule FM Radio Settings
     */
#ifdef __MMI_FM_RADIO_SCHEDULE_REC__
#define NVRAM_EF_FMSR_SETTING_SIZE     300
#define NVRAM_EF_FMSR_SETTING_TOTAL    4
#endif /* __MMI_FM_RADIO_SCHEDULE_REC__ */ 
    /*
     * Motion App
     */
#ifdef __MMI_MOTION_APP__
#define NVRAM_EF_MOTION_DICE_SIZE   636
#define NVRAM_EF_MOTION_DICE_TOTAL  10

#define NVRAM_EF_MOTION_DJ_SIZE     16
#define NVRAM_EF_MOTION_DJ_TOTAL    6
#endif /* __MMI_MOTION_APP__ */ 

/**
 * EONS
 */
#if defined(__MMI_EONS_SUPPORT__)
#define NVRAM_EF_EONS_INFO_SIZE     400 /* 50*8 */
#define NVRAM_EF_EONS_INFO_TOTAL    (1 * NVRAM_DUAL_RECORD)
#endif /* defined(__MMI_EONS_SUPPORT__) */ 

/**
 * User Control PLMN
 */
#ifdef __MMI_USER_CTRL_PLMN_SUPPORT__
#define NVRAM_EF_USER_CTRL_PLMN_SIZE    480 /* 20*24 */
#define NVRAM_EF_USER_CTRL_PLMN_TOTAL   1
#endif

#define NVRAM_PROFILES_RECORD_SIZE     532
#define NVRAM_PROFILES_RECORD_TOTAL    2

/**
 * Calling Background Sound Effect
 */
#ifdef __MMI_BG_SOUND_EFFECT__
#define NVRAM_EF_BGSND_SETTING_SIZE       20
#define NVRAM_EF_BGSND_SETTING_TOTAL      1

#define NVRAM_EF_BGSND_FILEPATH_SIZE      520
#define NVRAM_EF_BGSND_FILEPATH_TOTAL     10    /* Shall same as "BGSND_MAX_EXT_EFFECT" in "BGSoundType.h" */
#endif /* __MMI_BG_SOUND_EFFECT__ */ 

#define NVRAM_EF_CUST_HW_LEVEL_TBL_SIZE     440
#define NVRAM_EF_CUST_HW_LEVEL_TBL_TOTAL   1
    extern const kal_uint32 NVRAM_EF_CUST_HW_LEVEL_TBL_DEFAULT[NVRAM_EF_CUST_HW_LEVEL_TBL_SIZE];

    /* OBIGOQO5 */
#define NVRAM_UMMS_COMPOSE_SETTINGS_SIZE		1844
#define NVRAM_UMMS_COMPOSE_SETTINGS_RECORDS     1
#define NVRAM_UMMS_SENDING_SETTINGS_SIZE        20
#define NVRAM_UMMS_SENDING_SETTINGS_RECORDS     1

#ifdef JATAAYU_SUPPORT
    /* for JBrowser */
#define TITLES_PER_RECORD  20
#define URLS_PER_RECORD    5

#define NVRAM_EF_BRW_BOOKMARK_RECORD_TITLE_SIZE    (42 * TITLES_PER_RECORD)
#define NVRAM_EF_BRW_BOOKMARK_RECORD_URL_SIZE      (256 * URLS_PER_RECORD)
#define NVRAM_EF_BRW_BOOKMARK_TITLE_RECORDS        ((WAP_CUSTOM_CFG_N_NBR_BOOKMARKS%TITLES_PER_RECORD) ? ((WAP_CUSTOM_CFG_N_NBR_BOOKMARKS/TITLES_PER_RECORD) +1) : (WAP_CUSTOM_CFG_N_NBR_BOOKMARKS/TITLES_PER_RECORD))
#define NVRAM_EF_BRW_BOOKMARK_URL_RECORDS       ((WAP_CUSTOM_CFG_N_NBR_BOOKMARKS%URLS_PER_RECORD) ? ((WAP_CUSTOM_CFG_N_NBR_BOOKMARKS/URLS_PER_RECORD) +1) : (WAP_CUSTOM_CFG_N_NBR_BOOKMARKS/URLS_PER_RECORD))

#define NVRAM_EF_BRW_ADDRESS_HISTORY_RECORD_TITLE_SIZE      (42 * TITLES_PER_RECORD)
#define NVRAM_EF_BRW_ADDRESS_HISTORY_RECORD_URL_SIZE     (256 * URLS_PER_RECORD)
#define NVRAM_EF_BRW_ADDRESS_HISTORY_TITLE_RECORDS       ((CUSTOM_WAP_CFG_N_NBR_HISTORY%TITLES_PER_RECORD) ? ((CUSTOM_WAP_CFG_N_NBR_HISTORY/TITLES_PER_RECORD) +1) : (CUSTOM_WAP_CFG_N_NBR_HISTORY/TITLES_PER_RECORD))
#define NVRAM_EF_BRW_ADDRESS_HISTORY_URL_RECORDS         ((CUSTOM_WAP_CFG_N_NBR_HISTORY%URLS_PER_RECORD) ? ((CUSTOM_WAP_CFG_N_NBR_HISTORY/URLS_PER_RECORD) +1) : (CUSTOM_WAP_CFG_N_NBR_HISTORY/URLS_PER_RECORD))

    /* JMMS */
#define NVRAM_JMMS_COMPOSE_SETTINGS_SIZE        272
#define NVRAM_JMMS_COMPOSE_SETTINGS_RECORDS        1
#define NVRAM_JMMS_SENDING_SETTINGS_SIZE        16
#define NVRAM_JMMS_SENDING_SETTINGS_RECORDS        1
#define NVRAM_JMMS_INBOX_READ_STATUS_RECORDS    1
#define	NVRAM_MAX_READ_UNREAD_STATUS_BYTES		   ((((((WAP_CUSTOM_CFG_MAX_NBR_MMS_MSG/8)+1)+3)/4)*4))

/*for Browser profile*/
#define NVRAM_EF_WAP_PROFILE_CONTENT_SIZE		sizeof(nvram_wap_profile_content_struct)
#define NVRAM_EF_WAP_PROFILE_CONTENT_TOTAL		10
#define NVRAM_EF_WAP_PROFILE_NAMES_SIZE			sizeof(nvram_wap_profile_name_array_struct)
#define NVRAM_EF_WAP_PROFILE_NAMES_TOTAL		1

/*for MMS profile*/
#define NVRAM_EF_MMS_PROFILE_CONTENT_SIZE		sizeof(nvram_mms_profile_content_struct)
#define NVRAM_EF_MMS_PROFILE_CONTENT_TOTAL		10
#define NVRAM_EF_MMS_PROFILE_NAMES_SIZE			sizeof(nvram_mms_profile_name_array_struct)
#define NVRAM_EF_MMS_PROFILE_NAMES_TOTAL		1

#endif /* JATAAYU_SUPPORT */ 

#ifdef __MMI_WAP_PROF__
/*for Browser profile*/
#define NVRAM_EF_WAP_PROF_WAP_PROFILE_CONTENT_SIZE		sizeof(nvram_wap_prof_profile_content_struct)
#define NVRAM_EF_WAP_PROF_WAP_PROFILE_NAMES_SIZE		sizeof(nvram_wap_prof_profile_name_array_struct)
#define NVRAM_EF_WAP_PROF_WAP_PROFILE_NAMES_TOTAL	1
#define NVRAM_EF_WAP_PROF_WAP_PROFILE_CONTENT_TOTAL	NVRAM_WAP_PROF_MAX_PROFILES

/*for MMS profile*/
#define NVRAM_EF_WAP_PROF_MMS_PROFILE_CONTENT_SIZE		sizeof(nvram_wap_prof_profile_content_struct)
#define NVRAM_EF_WAP_PROF_MMS_PROFILE_CONTENT_TOTAL	NVRAM_WAP_PROF_MAX_PROFILES
#define NVRAM_EF_WAP_PROF_MMS_PROFILE_NAMES_SIZE		sizeof(nvram_wap_prof_profile_name_array_struct)
#define NVRAM_EF_WAP_PROF_MMS_PROFILE_NAMES_TOTAL		1
#endif /* __MMI_WAP_PROF__ */

#ifdef WAP_SUPPORT
#define NVRAM_EF_PUSH_WHITE_LIST_SIZE      (sizeof(nvram_push_addr_struct) * NVRAM_PUSH_MAX_ENTRY_IN_ONE_RECORD)
#define NVRAM_EF_PUSH_WHITE_LIST_TOTAL     ((NVRAM_PUSH_MAX_NUM_WHITE_LIST/(NVRAM_PUSH_MAX_ENTRY_IN_ONE_RECORD + 1)) + 1)
#endif /* WAP_SUPPORT */

#ifdef OBIGO_Q05A
#define TITLES_PER_RECORD  20
#define URLS_PER_RECORD    7
#define NVRAM_EF_BRW_ADDRESS_HISTORY_RECORD_TITLE_SIZE      (42 * TITLES_PER_RECORD)
#define NVRAM_EF_BRW_ADDRESS_HISTORY_RECORD_URL_SIZE     (256 * URLS_PER_RECORD)
#define NVRAM_EF_BRW_ADDRESS_HISTORY_TITLE_RECORDS       ((CUSTOM_WAP_CFG_N_NBR_HISTORY%TITLES_PER_RECORD) ? ((CUSTOM_WAP_CFG_N_NBR_HISTORY/TITLES_PER_RECORD) +1) : (CUSTOM_WAP_CFG_N_NBR_HISTORY/TITLES_PER_RECORD))
#define NVRAM_EF_BRW_ADDRESS_HISTORY_URL_RECORDS         ((CUSTOM_WAP_CFG_N_NBR_HISTORY%URLS_PER_RECORD) ? ((CUSTOM_WAP_CFG_N_NBR_HISTORY/URLS_PER_RECORD) +1) : (CUSTOM_WAP_CFG_N_NBR_HISTORY/URLS_PER_RECORD))
#define	NVRAM_EF_BRW_LAST_WEB_ADDR_SIZE		1024
#define	NVRAM_EF_BRW_LAST_WEB_ADDR_RECORDS	1

#ifndef __MMI_WAP_PROF__
/*for Browser profile*/
#define NVRAM_EF_WAP_PROFILE_CONTENT_SIZE		sizeof(nvram_profile_content_struct)
#define NVRAM_EF_WAP_PROFILE_CONTENT_TOTAL	10
#define NVRAM_EF_WAP_PROFILE_NAMES_SIZE		sizeof(nvram_profile_name_array_struct)
#define NVRAM_EF_WAP_PROFILE_NAMES_TOTAL		1

/*for MMS profile*/
#define NVRAM_EF_MMS_PROFILE_CONTENT_SIZE		sizeof(nvram_profile_content_struct)
#define NVRAM_EF_MMS_PROFILE_CONTENT_TOTAL	10
#define NVRAM_EF_MMS_PROFILE_NAMES_SIZE		sizeof(nvram_profile_name_array_struct)
#define NVRAM_EF_MMS_PROFILE_NAMES_TOTAL		1
#endif /* __MMI_WAP_PROF__ */

/**** PUSH ****/
#define NVRAM_EF_PUSH_TRUST_LIST_SIZE     1293
#define NVRAM_EF_PUSH_TRUST_LIST_TOTAL	 1

#define NVRAM_EF_PUSH_GEN_SETTING_SIZE     sizeof(nvram_push_general_setting_struct)
#define NVRAM_EF_PUSH_GEN_SETTING_TOTAL    1
	
#define NVRAM_EF_PUSH_BLACK_LIST_SIZE      (sizeof(nvram_push_addr_struct) * NVRAM_PUSH_MAX_ENTRY_IN_ONE_RECORD) 
#define NVRAM_EF_PUSH_BLACK_LIST_TOTAL     ((NVRAM_PUSH_MAX_NUM_BLACK_LIST/(NVRAM_PUSH_MAX_ENTRY_IN_ONE_RECORD + 1)) + 1)

#endif /* OBIGO_Q05A */

#ifdef WAP_SUPPORT

#define NVRAM_EF_WAP_BOOKMARK_LIST_SIZE	           (sizeof(nvram_wap_bookmark_struct) * NVRAM_WAP_BOOKMARK_MAX_ENTRY_IN_ONE_RECORD)
#define NVRAM_EF_WAP_BOOKMARK_LIST_TOTAL_RECORDS   ((NVRAM_WAP_BOOKMARK_MAX_NUM_BOOKMARKS/(NVRAM_WAP_BOOKMARK_MAX_ENTRY_IN_ONE_RECORD + 1)) + 1)

#endif /* WAP_SUPPORT */

#ifdef __MMI_FM_RADIO_SCHEDULER__
#define NVRAM_EF_FMRDO_SCHEDULER_SIZE  250
#define NVRAM_EF_FMRDO_SCHEDULER_TOTAL  1
#endif /* __MMI_FM_RADIO_SCHEDULER__ */ 

#define NVRAM_EF_EBOOK_SETTING_SIZE    93
#define NVRAM_EF_EBOOK_SETTING_TOTAL   1

/*
 * SIM-ME Lock
 */
#define NVRAM_EF_SML_SIZE   sizeof(nvram_sml_context_struct)
#define NVRAM_EF_SML_TOTAL  (1 * NVRAM_DUAL_RECORD)

#ifdef  __SMART_PHONE_MODEM__
#define NVRAM_EF_SIM_LOCK_SIZE sizeof(nvram_sml_context_struct)
#define NVRAM_EF_SIM_LOCK_TOTAL (1 * NVRAM_DUAL_RECORD)
#endif

/*
 * MS Security
 */
#define NVRAM_EF_MS_SECURITY_SIZE         (38)
#define NVRAM_EF_MS_SECURITY_TOTAL        (1 * NVRAM_DUAL_RECORD)

#ifdef __SYNCML_SUPPORT__
/* 
 * 	byte 0: profile,
 *	byte 1: applications, 
 * 	byte 2: regularity, 
 *	byte 3: power on snyc, 
 *	byte 4: type, 
 *	byte 5: sas, 	
 *	byte 6: report, 
 *	byte 7- last anchors
 */
#define NVRAM_EF_SYNCML_APP_NUM 6

#ifdef __MMI_SYNCML_VIEW_LOG_SUPPORT__
#define NVRAM_EF_SYNCML_VIEW_LOG_SIZE    sizeof(nvram_ef_syncml_view_log_struct)
#define NVRAM_EF_SYNCML_VIEW_LOG_TOTAL   (MAX_SYNCML_SV_PROFILES)
#endif /* __MMI_SYNCML_VIEW_LOG_SUPPORT__ */

#ifdef __MMI_SYNCML_DEVICE_SYNC__
/* Device Sync */
#define NVRAM_EF_SYNCML_DEV_SETTING_TOTAL    1
#define NVRAM_EF_SYNCML_DEV_SETTING_SIZE     sizeof(nvram_ef_syncml_device_setting_struct)

#define NVRAM_EF_SYNCML_DEV_ACCOUNT_TOTAL    MAX_SYNCML_DEV_NUM
#define NVRAM_EF_SYNCML_DEV_ACCOUNT_SIZE     sizeof(nvram_ef_syncml_device_account_struct)

#ifdef __MMI_SYNCML_VIEW_LOG_SUPPORT__
#define NVRAM_EF_SYNCML_DEV_SYNC_LOG_TOTAL    MAX_SYNCML_DEV_NUM
#define NVRAM_EF_SYNCML_DEV_SYNC_LOG_SIZE     sizeof(nvram_ef_syncml_view_log_struct)
#endif /*__MMI_SYNCML_VIEW_LOG_SUPPORT__ */
#endif /* __MMI_SYNCML_DEVICE_SYNC__ */

#define NVRAM_EF_SYNCML_ACCOUNT_SIZE    sizeof(nvram_ef_syncml_account_struct)
#define NVRAM_EF_SYNCML_ACCOUNT_TOTAL   MAX_SYNCML_SV_PROFILES

#endif /* __SYNCML_SUPPORT__ */ 

/* for VoIP settings */
#define MMI_VOIP_MAX_PROFILE_NAME_LEN       (33) /* 32 unicode + 1 null terminator */
#define VOIP_DISP_NAME_LEN                  (17) /* Length of display name + Null terminate */
#define VOIP_URI_LEN                        (41) /* Length of URI in bytes +	Null terminate */
#define VOIP_USERNAME_LEN                   (41) /* Length of username in bytes + Null terminate */
#define VOIP_PASSWORD_LEN                   (17) /* Length of password in bytes + Null terminate */
#define MMI_VOIP_MAX_IP_SEG                 (4)
#define VOIP_MAX_CALLER_PREFERENCE          (3)  /* Maximum caller preference settings */


#define NVRAM_EF_VOIP_PROF_SIZE			568
#define NVRAM_EF_VOIP_PROF_TOTAL		10

#define NVRAM_EF_VOIP_SETTING_SIZE      142
#define NVRAM_EF_VOIP_SETTING_TOTAL     1

#ifdef __WIFI_SUPPORT__
#define NVRAM_MAX_WLAN_SETTING_SIZE			8
#define NVRAM_MAX_WLAN_SETTING_TOTAL		1

#ifndef __CERTMAN_SUPPORT__
#ifdef __WAPI_SUPPORT__
#define NVRAM_MAX_WLAN_PROFILE_SIZE			(1948 + 78)
#else
#define NVRAM_MAX_WLAN_PROFILE_SIZE			1948
#endif
#else
#ifdef __WAPI_SUPPORT__
#define NVRAM_MAX_WLAN_PROFILE_SIZE			(392 + 78)
#else
#define NVRAM_MAX_WLAN_PROFILE_SIZE			392 
#endif
#endif /* __CERTMAN_SUPPORT__ */

#ifdef __WAPI_SUPPORT__
#define NVRAM_MAX_WLAN_PROFILE_TOTAL		31
#else
#define NVRAM_MAX_WLAN_PROFILE_TOTAL		30
#endif

#endif /* __WIFI_SUPPORT__*/

#ifdef __OCSP_SUPPORT__
#define NVRAM_EF_CERTMAN_OCSP_URL_SIZE    512
#define NVRAM_EF_CERTMAN_OCSP_URL_TOTAL    1
#define NVRAM_EF_CERTMAN_OCSP_URL_LID_VERNO   "000"
#endif /* __OCSP_SUPPORT__ */

#if defined(__EM_MODE__) && defined(__MMI_ENGINEER_MODE__)
/* Max no of event: 100, store ring_id (2 bytes) for each event */
#define NVRAM_EF_EM_NW_EVENT_RINGS_SIZE     sizeof(nvram_ef_em_nw_event_setting_struct)  
#define NVRAM_EF_EM_NW_EVENT_RINGS_TOTAL    1
#endif /* defined(__EM_MODE__) && defined(__MMI_ENGINEER_MODE__) */ 


#if defined(__MMI_FWU_VIA_TFTP__)
#define NVRAM_EF_DM_FWU_TFTP_SETTING_SIZE     sizeof(nvram_ef_dm_fwu_tftp_setting_struct)  
#define NVRAM_EF_DM_FWU_TFTP_SETTING_TOTAL    1
#endif /* #if defined(__MMI_FWU_VIA_TFTP__) */

#if defined(__MMI_FWU_VIA_HTTP__)
#define NVRAM_EF_DM_FWU_HTTP_SETTING_SIZE     sizeof(nvram_ef_dm_fwu_http_setting_struct)  
#define NVRAM_EF_DM_FWU_HTTP_SETTING_TOTAL    1
#endif /* #if defined(__MMI_FWU_VIA_HTTP__) */


/**
 * RAC preference
 */
#ifdef __MTK_3G_MRAT_ARCH__ /* for RAC2 */
/* support 3G multiband for MT6268 */ 
#define NVRAM_EF_RAC_PREFERENCE_SIZE         7 /* 4+2 (3g band) +1 (gprs_transfer_preference) */
#define NVRAM_EF_RAC_PREFERENCE_TOTAL        (1 * NVRAM_DUAL_RECORD)
#else /* for RAC */ 
#define NVRAM_EF_RAC_PREFERENCE_SIZE         2
#define NVRAM_EF_RAC_PREFERENCE_TOTAL        (1 * NVRAM_DUAL_RECORD)
#endif // end of #ifdef __MTK_3G_MRAT_ARCH__


#ifdef __MMI_VIDEO_STREAM__
/**
 * Video Streaming URL 
 */
#ifdef DEMO_PROJECT   
#define NVRAM_EF_VIDEO_PREDEFINED_URL_COUNT   (2)  /* (1)YouTube, (2)MTK (sync with nvram_common_config.c */
#else
#define NVRAM_EF_VIDEO_PREDEFINED_URL_COUNT   (1)  /* (1)YouTube (sync with nvram_common_config.c */
#endif
#define NVRAM_EF_VIDEO_PREDEFINED_URL_SIZE    (sizeof(nvram_ef_video_predefined_url_struct) * NVRAM_EF_VIDEO_PREDEFINED_URL_COUNT)
#define NVRAM_EF_VIDEO_PREDEFINED_URL_TOTAL   (1)

#define NVRAM_EF_VIDEO_HISTORY_URL_SIZE       (sizeof(nvram_ef_video_history_url_struct))
#define NVRAM_EF_VIDEO_HISTORY_URL_TOTAL      (5)

#define NVRAM_EF_VIDEO_NETWORK_PROFILE_SIZE   (sizeof(nvram_ef_video_network_profile_struct))
#define NVRAM_EF_VIDEO_NETWORK_PROFILE_TOTAL  (5)
#endif /* __MMI_VIDEO_STREAM__ */ 

/*
 * __DRM_V02__
 */
#define NVRAM_EF_DRM_SETTING_SIZE 16
#define NVRAM_EF_DRM_SETTING_TOTAL 10

#define NVRAM_EF_DRM_STIME_SIZE  128
#define NVRAM_EF_DRM_STIME_TOTAL 1

#define NVRAM_EF_DRM_CERPATH_SIZE 1024
#define NVRAM_EF_DRM_CERPATH_TOTAL 1
/**
* DM Self-Register Number
*/
#ifdef __MMI_DM_SELF_REGISTER_SUPPORT__
#define NVRAM_EF_DM_SR_NUMBER_SIZE         	22
#define NVRAM_EF_DM_SR_NUMBER_TOTAL        	1
#endif /* __MMI_DM_SELF_REGISTER_SUPPORT__ */

#ifdef __MMI_LANGLN__
#define NVRAM_EF_LANGLN_PRESEL_INFO_SIZE  132
#define NVRAM_EF_LANGLN_PRESEL_INFO_TOTAL  10
#endif /* __MMI_LANGLN__ */

#ifdef __MMI_LANGLN_LK__
#define NVRAM_EF_LANGLN_LK_SETTING_SIZE  32
#define NVRAM_EF_LANGLN_LK_SETTING_TOTAL  1
#endif /*__MMI_LANGLN_LK__*/

#if defined(__MMI_LANGLN_SK__) || defined(__MMI_LANGLN_BK__)
#define NVRAM_EF_LANGLN_BSK_SETTING_SIZE        576
#define NVRAM_EF_LANGLN_BSK_SETTING_TOTAL       2
#endif /*__MMI_LANGLN_SK__*/

#ifdef __MMI_SLIDESHOW__
/**
 * SLIDESHOW Settings
 */
#define NVRAM_EF_SLIDE_SHOW_SETTING_TOTAL        1
#define NVRAM_EF_SLIDE_SHOW_SETTING_SIZE         64
#endif /* __MMI_SLIDESHOW__ */

#ifdef __MMI_VIDEO_TELEPHONY__
/**
 * MMI VT setting
 */
#define NVRAM_EF_VT_SETTING_TOTAL       1
#define NVRAM_EF_VT_SETTING_SIZE        520
#endif /* __MMI_VIDEO_TELEPHONY__ */
#ifdef __MMI_MMS_BGSR_SUPPORT__
#define NVRAM_BGSR_MSG_STRUCT_SIZE      24
#define NVRAM_BGSR_MSG_STRUCT_RECORDS   1
#define NVRAM_BGSR_MSG_STRUCT_TOTAL     100
#endif /*__MMI_MMS_BGSR_SUPPORT__*/

/*
 * BT_BIP
 */
#ifdef __BIP_PULL_SUPPORT__
#define NVRAM_EF_BT_BIP_SETTING_SIZE  520
#define NVRAM_EF_BT_BIP_SETTING_TOTAL 1
#endif

#ifdef __GPS_SUPPORT__

/* Telacom construction !*/

#endif /* __GPS_SUPPORT__ */

#ifdef __GPS_SUPPORT__

/* Telacom construction !*/

#endif /* __GPS_SUPPORT__ */


#ifdef __GPS_SUPPORT__

/* Telacom construction !*/

#endif /* __GPS_SUPPORT__ */

#ifdef __MMI_MEDIA_PLAYER__
/*
 * Media player
 */
#define NVRAM_EF_MEDPLY_SETTINGS_SIZE   (533+1 + 2 + 1)
#define NVRAM_EF_MEDPLY_SETTINGS_TOTAL  (1)

#if defined(__MMI_MEDIA_PLAYER_STREAM__) || defined (__MMI_KURO_SUPPORT__)
#define NVRAM_EF_MEDPLY_SETTINGS_NETWORK_PROFILE_SIZE    (sizeof(nvram_ef_medply_settings_profile_struct))
#define NVRAM_EF_MEDPLY_SETTINGS_NETWORK_PROFILE_TOTAL   (5)
#endif

#ifdef  __MMI_MEDIA_PLAYER_STREAM__
#ifdef DEMO_PROJECT   
#define NVRAM_EF_MEDPLY_VIDEO_PREDEFINED_URL_COUNT   (2)  /* (1)YouTube, (2)MTK (sync with nvram_common_config.c */
#else
#define NVRAM_EF_MEDPLY_VIDEO_PREDEFINED_URL_COUNT   (1)  /* (1)YouTube (sync with nvram_common_config.c */
#endif
#define NVRAM_EF_MEDPLY_VIDEO_PREDEFINED_URL_SIZE    (sizeof(nvram_ef_medply_video_predefined_url_struct) * NVRAM_EF_MEDPLY_VIDEO_PREDEFINED_URL_COUNT)
#define NVRAM_EF_MEDPLY_VIDEO_PREDEFINED_URL_TOTAL   (1)
#endif

#ifdef __MMI_MEDIA_PLAYER_PLST_MULTIPLE_STYLE__
#define NVRAM_EF_MEDPLY_HISTORY_URL_SIZE       			(sizeof(nvram_ef_medply_history_url_struct))
#define NVRAM_EF_MEDPLY_HISTORY_URL_TOTAL      			(20)
#endif

#define NVRAM_EF_MEDPLY_LIST_PLAYLIST_PATH_SIZE  520
#define NVRAM_EF_MEDPLY_LIST_PLAYLIST_PATH_TOTAL 1
#endif /* __MMI_MEDIA_PLAYER__ */

/*
 * DCD Setting profile
 */
#ifdef __MMI_OP01_DCD__
#define NVRAM_EF_DCD_SETTING_DATA_SIZE  6
#define NVRAM_EF_DCD_SETTING_DATA_TOTAL 1
#endif /*__MMI_OP01_DCD__*/

#ifdef __MMI_EM_MISC_DCD__
#define NVRAM_EF_DCD_EM_PARAM_DATA_SIZE  320
#define NVRAM_EF_DCD_EM_PARAM_DATA_TOTAL 1
#endif /* __MMI_EM_MISC_DCD__ */

#ifdef __MMI_CAMCORDER__
#define NVRAM_EF_CAMCO_APP_INFO_TOTAL 1
#define NVRAM_EF_CAMCO_APP_INFO_SIZE  (sizeof(nvram_ef_camco_app_info_struct))

#define NVRAM_EF_CAMCO_MAIN_SETTING_TOTAL 1
#define NVRAM_EF_CAMCO_MAIN_SETTING_SIZE  (sizeof(nvram_ef_camco_setting_struct))

#define NVRAM_EF_CAMCO_MAIN_SETTING_SCENE_SEL_TOTAL 1
#define NVRAM_EF_CAMCO_MAIN_SETTING_SCENE_SEL_SIZE  (sizeof(nvram_ef_camco_setting_scene_sel_struct))

#ifdef DUAL_CAMERA_SUPPORT
#define NVRAM_EF_CAMCO_SUB_SETTING_TOTAL 1
#define NVRAM_EF_CAMCO_SUB_SETTING_SIZE  (sizeof(nvram_ef_camco_setting_struct))

#define NVRAM_EF_CAMCO_SUB_SETTING_SCENE_SEL_TOTAL 1
#define NVRAM_EF_CAMCO_SUB_SETTING_SCENE_SEL_SIZE  (sizeof(nvram_ef_camco_setting_scene_sel_struct))
#endif /* DUAL_CAMERA_SUPPORT */
#endif /* __MMI_CAMCORDER__ */


#ifdef __MMI_AUDPLY_MULTIPLE_LIST__
#define NVRAM_EF_AUDPLY_LIST_PLAYLIST_PATH_SIZE  520
#define NVRAM_EF_AUDPLY_LIST_PLAYLIST_PATH_TOTAL 1
#endif  /* __MMI_AUDPLY_MULTIPLE_LIST__ */

/* phonebook vip contact */
#ifdef __MMI_OP11_HOMESCREEN__
/* under construction !*/
/* under construction !*/
#endif /* __MMI_OP11_HOMESCREEN__ */
/* phonebook vip contact */

#ifdef __MMI_PHB_DEFAULT_NUMBER__
#define NVRAM_EF_PHB_OG_SET_DEFAULT_NUMBER_RECORD_SIZE 510
#define NVRAM_EF_PHB_OG_SET_DEFAULT_NUMBER_TOTAL ((MAX_PHB_SIM_ENTRY + MAX_PHB_PHONE_ENTRY) / 510 + 1)
#endif

/*
 * Idle screen 
 */
#ifdef __MMI_OP11_HOMESCREEN__
/* under construction !*/
/* under construction !*/
#endif /* __MMI_OP11_HOMESCREEN__ */

#ifdef __MMI_OP12_TOOLBAR__
#define NVRAM_EF_TOOLBAR_CNTX_TOTAL     1
#define NVRAM_EF_TOOLBAR_CNTX_SIZE      6
#endif /* __MMI_OP12_TOOLBAR__ */

#ifdef __MMI_VUI_HOMESCREEN__
#define NVRAM_EF_VENUS_HS_CNTX_TOTAL    1
#define NVRAM_EF_VENUS_HS_CNTX_SIZE     286

#define NVRAM_EF_VENUS_HS_WIDGET_MEMO_CNTX_TOTAL    1
#define NVRAM_EF_VENUS_HS_WIDGET_MEMO_CNTX_SIZE     66
#endif /* __MMI_VUI_HOMESCREEN__ */

#ifdef __MMI_VUI_MAINMENU__
#define NVRAM_EF_VENUS_MM_TOTAL    1
#define NVRAM_EF_VENUS_MM_SIZE     12
#endif /*__MMI_VUI_MAINMENU__*/

#ifdef __MMI_VUI_HOMESCREEN_PHOTO__
#define NVRAM_EF_VENUS_PHOTO_FILEPATH_TOTAL 1
#define NVRAM_EF_VENUS_PHOTO_FILEPATH_SIZE  520
#endif

#ifdef __MMI_IMAGE_VIEWER_EX__
#define NVRAM_EF_IVEX_SETTINGS_SIZE    10
#define NVRAM_EF_IVEX_SETTINGS_TOTAL  1
#endif

#if defined (__WIFI_BT_SINGLE_ANTENNA_SUPPORT__)
#define NVRAM_EF_BWCS_SETTING_DATA_SIZE  80
#define NVRAM_EF_BWCS_SETTING_DATA_TOTAL 1
#endif

/*
 * Bluetooth Auto Prompt
 */
#ifdef __MMI_BT_AUTO_PROMPT_SWITCH__
#define NVRAM_EF_BT_DEFDEVICE_SIZE    (sizeof(nvram_ef_bt_defdev_struct))
#define NVRAM_EF_BT_DEFDEVICE_TOTAL   10
#endif /* __MMI_BT_AUTO_PROMPT_SWITCH__ */ 

#if defined(__MMI_OP11_HOMESCREEN__) || defined(__MMI_VUI_HOMESCREEN__)
#define NVRAM_EF_SMS_RECENT_EVENT_BITMAP_TOTAL		1
#define NVRAM_EF_SMS_RECENT_EVENT_BITMAP_SIZE		((CM_SMS_MAX_MSG_NUM + 7) / 8)
#endif /* __MMI_OP11_HOMESCREEN__ || __MMI_VUI_HOMESCREEN__ */

#if defined(__MMI_OP11_HOMESCREEN__) || defined(__MMI_OP12_TOOLBAR__)
#define NVRAM_EF_SMS_VOICEMAIL_TIME_TOTAL			2
#define NVRAM_EF_SMS_VOICEMAIL_TIME_SIZE			(sizeof(MYTIME))
#endif /* defined(__MMI_OP11_HOMESCREEN__) || defined(__MMI_OP12_TOOLBAR__) */

#ifdef __FLAVOR_VENDOR_SDK__
#define NVRAM_EF_VS_SETTING_TOTAL  1
#define NVRAM_EF_VS_SETTING_SIZE   (sizeof(nvram_ef_vs_setting_struct))
#endif


/*
 * Auto Answer Machine Settings
 */
#ifdef __MMI_AUTO_ANSWER_MACHINE__
#define NVRAM_EF_ANSWER_MACHINE_SETTING_SIZE     600
#define NVRAM_EF_ANSWER_MACHINE_SETTING_TOTAL    1
#endif /* __MMI_AUTO_ANSWER_MACHINE__ */ 


/* Internet Application */
#if defined(PLUTO_MMI) && !defined(__MMI_EM_INET_APP_SLIM__)
#define NVRAM_EF_INET_MAX_UA_STRING_LEN     (255)
#define NVRAM_EF_INET_MAX_UA_PROFILE_LEN    (255)
#define NVRAM_EF_INET_CUSTPACK_SIZE         sizeof(nvram_em_inet_custpack_struct)
#define NVRAM_EF_INET_CUSTPACK_TOTAL        (1)
#endif

#ifdef __MMI_IPSEC__
/**
 * IPSec Settings MMI profile name
 */
#define NVRAM_EF_IPSEC_PROFILE_NAME_SIZE  sizeof(nvram_ef_ipsec_profile_name_struct) 
#define NVRAM_EF_IPSEC_PROFILE_NAME_TOTAL 3
#endif /* __MMI_IPSEC__ */


#ifdef __A8BOX_SUPPORT__
#define NVRAM_EF_A8BOX_SETTING_SIZE			sizeof(nvram_ef_elf_audio_bt_settings_struct)
#define NVRAM_EF_A8BOX_SETTING_TOTAL		1
#endif

#ifdef __EMAIL__
/* Email Data Account */
#define NVRAM_EF_EMAIL_DATA_ACCOUNT_SIZE    sizeof(nvram_ef_email_data_account_struct)
#define NVRAM_EF_EMAIL_DATA_ACCOUNT_TOTAL   20
#endif /* __EMAIL__ */

#ifdef __MMI_NOTE_APP__
#define NVRAM_EF_NOTE_LIST_TOTAL			MMI_MAX_NOTE_ITEM
#define NVRAM_EF_NOTE_NODE_STRUCT_SIZE      sizeof(nvram_ef_note_app_node_struct)
#endif /* __MMI_NOTE_APP__ */

#ifdef __MMI_ZAKAT_CALCULATOR__
#define NVRAM_EF_ZAKAT_CALCULATOR_SIZE      sizeof(nvram_zakat_calculator_data_record_struct)
#define NVRAM_EF_ZAKAT_CALCULATOR_TOTAL     27
#endif /* __MMI_ZAKAT_CALCULATOR__ */

#ifdef __MMI_SEARCH_WEB__
#define NVRAM_EF_SEARCH_WEB_HISTORY_LID_VERNO           "000"
#define NVRAM_EF_SEARCH_WEB_HISTORY_VALID_MAGIC_NUMBER  0x642ba1d0
#define NVRAM_EF_SEARCH_WEB_HISTORY_MAX_STRING_LEN      32
#define NVRAM_EF_SEARCH_WEB_HISTORY_MAX_ENTRY_NUM       5
#define NVRAM_EF_SEARCH_WEB_HISTORY_SIZE                sizeof(nvram_ef_search_web_history_struct)
#define NVRAM_EF_SEARCH_WEB_HISTORY_TOTAL               1

#ifdef __MMI_SEARCH_WEB_BAIDU__
#define NVRAM_EF_SEARCH_WEB_BAIDU_UID_LID_VERNO         "000"
#define NVRAM_EF_SEARCH_WEB_BAIDU_UID_MAX_LEN           48
#define NVRAM_EF_SEARCH_WEB_BAIDU_UID_SIZE              sizeof(nvram_ef_search_web_baidu_uid_struct)
#define NVRAM_EF_SEARCH_WEB_BAIDU_UID_TOTAL             1
#endif

#endif
#ifdef __TCPIP__
#define NVRAM_EF_TCP_LAST_TOTAL_SIZE    sizeof(nvram_ef_cbm_tcp_history_struct)
#define NVRAM_EF_TCP_LAST_TOTAL_TOTAL   8
#endif
#ifdef __MMI_FM_RADIO__
#ifdef __TL_TELACOM_MODIFICATION__
#define NVRAM_EF_FM_RADIO_CHANNEL   30
#else
#define NVRAM_EF_FM_RADIO_CHANNEL   9 /* Better less than 30 channels, or it may exceed the maximum NVRAM record size */
#endif
#define NVRAM_EF_FM_RADIO_TOTAL     1
#define NVRAM_EF_FM_RADIO_SIZE      (NVRAM_EF_FM_RADIO_CHANNEL * 44) /* Same as "sizeof(mmi_fmrdo_channel_list_struct) */
#endif /* __MMI_FM_RADIO__ */
#ifdef __DM_SCOMO_SUPPORT__
#define NVRAM_EF_DM_MAX_ID_LEN      32
#define NVRAM_EF_DM_MAX_NAME_LEN    64
#define NVRAM_EF_DM_MAX_URL_LEN 128
#define NVRAM_EF_DM_APP_SCOMO_REPORT_INFO_SIZE sizeof(nvram_ef_dm_app_scomo_report_info_struct)
#define NVRAM_EF_DM_APP_SCOMO_REPORT_INFO_TOTAL 1
#endif /* __DM_SCOMO_SUPPORT__ */

#ifdef __cplusplus
}
#endif 

#endif /* __MAUI_BASIC__ */ 
#endif /* NVRAM_COMMON_DEFS_H */ 


