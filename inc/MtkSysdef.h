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





#endif /*QY_MTK_SYS_DEF_H*/

