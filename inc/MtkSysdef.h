#ifndef QY_MTK_SYS_DEF_H
#define QY_MTK_SYS_DEF_H


typedef enum
{
    NONE_TONE,
    ERROR_TONE = 1,
    CONNECT_TONE,
    CAMP_ON_TONE,
    WARNING_TONE,
    INCOMING_CALL_TONE,        /*5*/
    ALARM_TONE,
    POWER_ON_TONE,
    POWER_OFF_TONE,
    COVER_OPEN_TONE,
    COVER_CLOSE_TONE,          /*10*/
    MESSAGE_TONE,
    KEYPAD_PLAY_TONE,
    SUCCESS_TONE,
    SAVE_TONE,
    EMPTY_LIST_TONE,           /*15*/
    GENERAL_TONE,
    SMS_IN_CALL_TONE,
    AUX_TONE,
    WARNING_TONE_IN_CALL,
    ERROR_TONE_IN_CALL,        /*20*/
    CONNECT_TONE_IN_CALL,
    SUCCESS_TONE_IN_CALL,
    BATTERY_LOW_TONE,
    BATTERY_WARNING_TONE,
    CALL_REMINDER_TONE,        /*25*/
    CCBS_TONE,
    CONGESTION_TONE,
    AUTH_FAIL_TONE,
    NUM_UNOBTAIN_TONE,
    CALL_DROP_TONE,            /*30*/
    IMPS_CONTACT_ONLINE_TONE,
    IMPS_NEW_MESSAGE_TONE,
    IMPS_CONTACT_INVITATION_TONE,
    IMPS_CHATROOM_NOTIFICATION_TONE,
    CARD2_INCOMING_CALL_TONE,  /*35*/
    CARD2_MESSAGE_TONE,
    FILE_ARRIVAL_TONE,

    /*for op11*/
    SENT_TONE,
    DELETED_TONE,
    PROBLEM_TONE,              /*40*/
    NETWORK_PROBLEM_TONE,
    CONFIRM_TONE,
    EXPLICITLY_SAVE_TONE,
    NOT_AVAILABLE_TONE,        /*Oops tone*/
    ANS_PHONE_TONE,            /*45*/
    SMS_TONE,
    MMS_TONE,
    EMAIL_TONE,
    VOICE_TONE,
    WAP_PUSH_TONE,             /*50*/
    REMIND_TONE,
#ifdef __PRAY_IN_SUPPORT__
    PRAY_TONE,
#endif
    TOTAL_TONE_NUM
}ALL_TONE_ENUM;

typedef int MMI_ID_TYPE;
typedef int module_type;
typedef int sap_type;
typedef int msg_type;
typedef U8(*HistoryDelCBPtr) (void *);
typedef void (*FuncPtr) (void);

typedef struct MYTIME
{
    kal_uint16 nYear;
    kal_uint8 nMonth;
    kal_uint8 nDay;
    kal_uint8 nHour;
    kal_uint8 nMin;
    kal_uint8 nSec;
    kal_uint8 DayIndex; /* 0=Sunday */
} MYTIME,applib_time_struct;


#define MAX_INPUT_BUFFER 1600
#define MAX_GUI_BUFFER           128

/* history information stuct */
typedef struct _history
{
    U16 scrnID;
    FuncPtr entryFuncPtr;
    U8 inputBuffer[MAX_INPUT_BUFFER];   /* running text data                   */
    U8 guiBuffer[MAX_GUI_BUFFER];       /* this includes hilite item, input mode & etc.. */
} history;



typedef enum
{
    MTK_IDLE_SCREEN_ID =  1,
    MTK_IDLE_SCREEN_ID_DUMMY, 
    MTK_IDLE_SCREEN_DIGIT_HANDLER_ID,
    MTK_IDLE_SCREEN_DIGIT_OPTIONS_ID,
    MTK_IDLE_SCREEN_SCREENSAVER_ID,
    MTK_IDLE_SCREEN_DUMMY_ID,
    MTK_SCREEN_SAVER_PARTIAL_ON_ID,
    MTK_POPUP_SCREENID,
    MTK_SCR_ID_NMGR_DUMMY,
    MTK_SCR_ID_NMGR_NOTIFY,
    MTKSCR_ID_NMGR_NOTIFY_ON_IDLE,
    

     MTK_SCR_ID_IDLE_END
} IDLE_SCR_ID_ENUM;

#define POPUP_SCREENID    (MTK_POPUP_SCREENID+IDLE_APP_BASE)
/*******************************************************************************
 * Macros Without Parameters
 *******************************************************************************/
#define LOCAL_PARA_HDR \
   kal_uint8	ref_count; \
   kal_uint16	msg_len;

#define PEER_BUFF_HDR \
   kal_uint16	pdu_len; \
   kal_uint8	ref_count; \
   kal_uint8   	pb_resvered; \
   kal_uint16	free_header_space; \
   kal_uint16	free_tail_space;


typedef struct peer_buff_struct {
   PEER_BUFF_HDR /* XXX!!!. Rex Luo - I don't like the usage */
} peer_buff_struct;

/*
 *  Local parameter header
 *  msg_len : Numbfer of bytes after the ref_count field.
 *             Length is in bytes.
 *  ref_count : This is useful if a module wants to retain
 *               a buffer. Protocol stack module should access
 *               this field by calling hold_local_para()
 */

typedef struct local_para_struct {
   LOCAL_PARA_HDR   /*XXX!!!. Rex Luo - I don't like the usage */
} local_para_struct;

typedef struct ilm_struct {
   module_type       src_mod_id;
   module_type       dest_mod_id;
   sap_type          sap_id;
   msg_type          msg_id;
   local_para_struct *local_para_ptr;
   peer_buff_struct  *peer_buff_ptr;
} ilm_struct;


/////////////////////////////////////////////////////////////////////////////////
// Uart 

typedef enum {
    uart_port1=0,
    uart_port2,
    uart_port3,
    uart_port_irda,
    uart_port_usb,
    uart_port_bluetooth,
    uart_port_swdbg,

    uart_max_port,      
    uart_port_null = 99	/* a dummy port for those who doesn't use physical port */
} UART_PORT;

typedef kal_uint32 UART_baudrate;

typedef enum {
      len_5=5,
      len_6,
      len_7,
      len_8
} UART_bitsPerCharacter;

typedef enum {
      sb_1=1,
      sb_2,
      sb_1_5
} UART_stopBits;

typedef enum {
      pa_none=0,
      pa_odd,
      pa_even,
      pa_space
} UART_parity;

typedef enum {
      fc_none=1,
      fc_hw,
      fc_sw
} UART_flowCtrlMode;

typedef struct
{
      UART_baudrate                 baud; 
      UART_bitsPerCharacter         dataBits;
      UART_stopBits                 stopBits;
      UART_parity                   parity;
      UART_flowCtrlMode             flowControl;
      kal_uint8                     xonChar;
      kal_uint8                     xoffChar;
      kal_bool                      DSRCheck;
} UARTDCBStruct;
/////////////////////////////////////////////////////////////////////////////////
// System Date Time
typedef struct {
    kal_uint8 rtc_sec;
    kal_uint8 rtc_min;
    kal_uint8 rtc_hour;
    kal_uint8 rtc_day;
    kal_uint8 rtc_mon;
    kal_uint8 rtc_wday;
    kal_uint8 rtc_year;
} rtc_format_struct;


#endif /*QY_MTK_SYS_DEF_H*/

