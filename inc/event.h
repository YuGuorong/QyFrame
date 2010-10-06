#ifndef QY_EVENT_H
#define QY_EVENT_H
typedef enum
{
   MMI_EVENT_FAILURE,   /* Basic popup failure type */
   MMI_EVENT_INFO,      /* Basic popup infomation type */
   MMI_EVENT_WARNING,   /* Basic popup warning type */
   MMI_EVENT_SUCCESS,   /* Basic popup success type */
   MMI_EVENT_PROGRESS,  /* Basic popup progress type */
   MMI_EVENT_QUERY,     /* Basic popup query type */
   MMI_EVENT_MESSAGE_SENT,          /* __OP11__ */
   MMI_EVENT_PROPLEM,               /* __OP11__ */
   MMI_EVENT_EXPLICITLY_SAVED,      /* __OP11__ */
   MMI_EVENT_EXPLICITLY_DELETED,    /* __OP11__ */
   MMI_EVENT_CONFIRM,               /* __OP11__ */
   MMI_EVENT_BATTERY_WARNING,       /* __OP11__ */
   MMI_EVENT_NOT_AVAILABLE,         /* __OP11__ */
   MMI_EVENT_ANSPHONE,              /* __OP11__ */
   MMI_EVENT_REMIND,                /* __OP11__ */
   MMI_EVENT_BATTERY_NOTIFY,        /* __OP11__ */
   MMI_EVENT_TOTAL_NUM							/* total event*/
} mmi_event_notify_enum;

/* mmi key type */
typedef enum
{
    KEY_FULL_PRESS_DOWN,
    KEY_EVENT_DOWN = KEY_FULL_PRESS_DOWN,
    KEY_EVENT_UP,
    KEY_LONG_PRESS,
    KEY_REPEAT,
    KEY_HALF_PRESS_DOWN,
    KEY_HALF_PRESS_UP,
    MAX_KEY_TYPE
} mmi_key_types_enum;

#define ENCODING_LENGTH       2
#define MMI_ATTACHMENT_FILE_NAME_SIZE           12 * ENCODING_LENGTH

typedef struct _wgui_inline_images_detail
{
    U8 image_file_name[MMI_ATTACHMENT_FILE_NAME_SIZE];
    U8 type_of_image;
    PU8 image1;
} wgui_inline_images_detail;


typedef struct _wgui_inline_item
{
    U32 flags;
    S32 key_code;
    S32 key_event;
    PU8 text_p;
    PU8 side_img;
    U8 show_img_flag;
    void *item;
    void (*handler) (S32 x, S32 y, S32 width, S32 height, S32 key_code, S32 key_event, PU8 *text_p, void *item,
                     U32 flags, PU8 history_buffer);
} wgui_inline_item;

typedef wgui_inline_item InlineItem;

typedef enum
{
/* * The key code sequency cannot be changed. */
    KEY_0 = 0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_LSK,
    KEY_RSK,
    KEY_CSK,
    KEY_UP_ARROW,
    KEY_DOWN_ARROW,
    KEY_LEFT_ARROW,
    KEY_RIGHT_ARROW,
    KEY_SEND,
    KEY_END,
    KEY_CLEAR,
    KEY_STAR,
    KEY_POUND,
    KEY_VOL_UP,
    KEY_VOL_DOWN,
    KEY_CAMERA,
    KEY_QUICK_ACS = KEY_CAMERA,
    KEY_ENTER,
    KEY_WAP = KEY_ENTER,
    KEY_IP = KEY_ENTER,
    KEY_EXTRA_1,
    KEY_EXTRA_2,
    KEY_PLAY_STOP,
    KEY_FWD,
    KEY_BACK,
    KEY_POWER,
    KEY_EXTRA_A,
    KEY_EXTRA_B,
   /*
    * the second call key is define for MERCURY dual mode
    * KEY_SEND means KEY_SEND1 and KEY_SEND2
    * But the application could set the individual key handler in using KEY_SEND1 and KEY_SEND2
    * KEY_SEND1 has its KEY_SEND1's entry in nKeyPadMap[]
    * KEY_SEND2 has its KEY_SEND2's entry in nKeyPadMap[]
    */
    KEY_SEND1,
    KEY_SEND2,
    KEY_BACKQUOTE,
    KEY_DASH,
    KEY_EQUAL,
    KEY_OPEN_PARENS,
    KEY_CLOSE_PARENS,
    KEY_OPEN_SQUARE,
    KEY_CLOSE_SQUARE,
    KEY_OPEN_BRACE,
    KEY_CLOSE_BRACE,
    KEY_BACKSLASH,
    KEY_SEMICOLON,
    KEY_SLASH,
    KEY_DOLLAR,
    KEY_PERCENT,
    KEY_CARET,
    KEY_AND,
    KEY_QUOTE,
    KEY_PLUS,
    KEY_LESS_THAN,
    KEY_GREAT_THAN,
    KEY_UNDERSCORE,
    KEY_PIPE,
    KEY_TILDE,
    KEY_CAPS_LOCK,
    
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_SPACE,
    KEY_TAB,
    KEY_DEL,
    KEY_ALT,
    KEY_CTRL,
    KEY_WIN,
    KEY_SHIFT,
    KEY_QUESTION,
    KEY_PERIOD,
    KEY_COMMA,
    KEY_EXCLAMATION,
    KEY_APOSTROPHE,
    KEY_AT,
    KEY_BACKSPACE,
    KEY_QWERTY_ENTER,
    KEY_FN,
    KEY_SYMBOL,
    KEY_NUM_LOCK,
    KEY_EMAIL,
    KEY_MESSAGE,
    KEY_ESC,
    KEY_QWERTY_MENU,
    KEY_OK,
    KEY_GPS,

    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,

    KEY_HOME,
    KEY_CALENDAR,
    KEY_CALLLIST,
    KEY_SHIFT1,
    KEY_TV,
    KEY_LOCK,
    KEY_PBOOK,
    KEY_BROWSER,

    KEY_NONE,  /* none key mapping. __TL_TELACOM_MODIFICATION__ */
    
    MAX_QWERTY_KEYS,
    MAX_KEYS = MAX_QWERTY_KEYS,

    KEY_INVALID = 0xFE
} mmi_keypads_enum;
 
typedef enum
{
    IMM_INPUT_TYPE_NONE = 0,
    IMM_INPUT_TYPE_NUMERIC = 0x1,
    IMM_INPUT_TYPE_PHONE_NUMBER = (0x1 << 1),
    IMM_INPUT_TYPE_DECIMAL_NUMERIC = (0x1 << 2),
    IMM_INPUT_TYPE_SIGNED_NUMERIC = (0x1 << 3),
    IMM_INPUT_TYPE_SIGNED_DECIMAL_NUMERIC = (0x1 << 4),
    IMM_INPUT_TYPE_URL = (0x1 << 5), /* for url input */
    IMM_INPUT_TYPE_QUICK_SEARCH = (0x1 << 6), /* for quick search */
    IMM_INPUT_TYPE_SENTENCE = (0x1 << 7), /* all kind of character are allowed to input. */
    IMM_INPUT_TYPE_ENGLISH_SENTENCE = (0x1 << 8), /* only English character are allowed. */
    IMM_INPUT_TYPE_USER_SPECIFIC = (0x1 << 9), /* APP define the input method he want */
    IMM_INPUT_TYPE_KEYPAD_NUMERIC = (0x1 << 10),
    IMM_INPUT_TYPE_SIM_NUMERIC = (0x1 << 11),
    IMM_INPUT_TYPE_ENGLISH_SENTENCE_UPPERCASE = (0x1 << 12) ,
    IMM_INPUT_TYPE_ENGLISH_SENTENCE_LOWERCASE = (0x1 << 13) ,
    IMM_INPUT_TYPE_EMAIL = (0x01 << 14),
    IMM_INPUT_TYPE_PHONE_NUMBER_WILDCHAR = (0x01 << 15),
    IMM_INPUT_TYPE_NUMERIC_SYMBOL = (0x01 << 16),
    IMM_INPUT_TYPE_ASCII_CHAR = (0x01 << 17),
    IMM_INPUT_TYPE_MAX
} mmi_imm_input_type_enum;

#define    IMM_INPUT_TYPE_MASK                                   0xf80000 
#define    IMM_INPUT_TYPE_EXT_PASSWORD                    0x800000
#define    IMM_INPUT_TYPE_OVERRIDE_DEFAULT              0x400000
#define    IMM_INPUT_TYPE_EXT_MULTITAP                      0x200000
#define    IMM_INPUT_TYPE_ADD_NEW_WORD                      0x100000
#define    IMM_INPUT_TYPE_EXT_ENGLISH_UPPERCASE             0x080000
#define    IMM_INPUT_TYPE_SAT_NUMERIC_PASSWORD      (IMM_INPUT_TYPE_KEYPAD_NUMERIC |IMM_INPUT_TYPE_EXT_PASSWORD)
#define    IMM_INPUT_TYPE_DECIMAL_NUMERIC_PASSWORD  (IMM_INPUT_TYPE_DECIMAL_NUMERIC | IMM_INPUT_TYPE_EXT_PASSWORD)
#define    IMM_INPUT_TYPE_SIGNED_NUMERIC_PASSWORD   (IMM_INPUT_TYPE_SIGNED_NUMERIC | IMM_INPUT_TYPE_EXT_PASSWORD)
#define    IMM_INPUT_TYPE_SIGNED_DECIMAL_NUMERIC_PASSWORD (IMM_INPUT_TYPE_SIGNED_DECIMAL_NUMERIC | IMM_INPUT_TYPE_EXT_PASSWORD)
#define    IMM_INPUT_TYPE_NUMERIC_PASSWORD                (IMM_INPUT_TYPE_NUMERIC | IMM_INPUT_TYPE_EXT_PASSWORD)
#define    IMM_INPUT_TYPE_ALPHANUMERIC_PASSWORD       (IMM_INPUT_TYPE_ENGLISH_SENTENCE | IMM_INPUT_TYPE_EXT_PASSWORD)
#define    IMM_INPUT_TYPE_ASCII_PASSWORD              (IMM_INPUT_TYPE_ASCII_CHAR | IMM_INPUT_TYPE_EXT_PASSWORD)
#define    IMM_INPUT_TYPE_MULTITAP_SENTENCE             (IMM_INPUT_TYPE_EXT_MULTITAP | IMM_INPUT_TYPE_SENTENCE)

#define MMI_IMM_MAX_INPUT_METHOD_NUM  100

#define INLINE_ITEM_ACTIVATE_WITHOUT_KEY_EVENT  0x000000FE


typedef enum
{
    DEFAULT,    /* Cannot be changed to list,matrix,circular */
    DISP_LIST,
    DISP_MATRIX,
    DISP_CIRCULAR_3D,
    DISP_PAGE,
    DISP_ANI_BG_LIST,
    DISP_MATRIX_EMS,
    DISP_ROTATE,
    DISP_MOTION,
    DISP_LIST_MATRIX,
    DISP_MATRIX_PAGE,
    DISP_FIXED_GRID
} DISPATTRIBUTE;

#define LIST_MENU           DISP_LIST
#define MATRIX_MENU         DISP_MATRIX
#define CIRCULAR_3D_MENU    DISP_CIRCULAR_3D
#define PAGE_MENU           DISP_PAGE
#define ANI_BG_LIST_MENU    DISP_ANI_BG_LIST
#define MATRIX_MENU_EMS     DISP_MATRIX_EMS
#define ROTATE_MENU         DISP_ROTATE
#define LIST_MATRIX_MENU    DISP_LIST_MATRIX
#define MOTION_MENU         DISP_MOTION
#define MATRIX_PAGE_MENU    DISP_MATRIX_PAGE
#define MMI_MENU_TYPES      DISPATTRIBUTE

/* Enum values which are used to describe different types of softkey. */
typedef enum
{
    /* Is an enum value which represents the left softkey */
    MMI_LEFT_SOFTKEY,
    /* Is an enum value which represents the right softkey */
        MMI_RIGHT_SOFTKEY,

    /* Is an enum value which represents the center softkey */
        MMI_CENTER_SOFTKEY,

    /* DOM-NOT_FOR_SDK-BEGIN */
    /* Is the max count of all softkeys */
        WGUI_MAX_SOFTKEYS
    /* DOM-NOT_FOR_SDK-END */
} WGUI_SOFTKEY_ENUM;

#endif /*QY_EVENT_H*/

