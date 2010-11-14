#ifndef _QINYI_APPTYPES_H
#define _QINYI_APPTYPES_H


#define VENDOR_ZHONGTONG    1
#define VENDOR_NENGDA       2   
#define VENDOR_MEIDA        3
#define VENDOR_NAME         VENDOR_ZHONGTONG  //VENDOR_MEIDA //VENDOR_NENGDA // 

#define CMD_LOGIN           1000
#define CMD_LOGIN_REQ       1
#define CMD_LOGIN_ACK       2

#define CMD_CHK_BILL        1001
#define CMD_CHKBILL_REQ     1

#define CMD_RECIVE_BILL     1007

#define CMD_SIGN_RECTP      1003
#define CMD_SRECTP_REQ      1
#define CMD_SRECTP_ACK      2

#define CMD_PROBLEM         1004
#define CMD_QRY_EXP_STATUS  1006
#define CMD_QRY_EPX_STA_REQ 1
#define CMD_QUERYUPDATE     1100
#define CMD_UPDATESW        1101
#define CMD_QUERYUPDATE_REQ 2

#define CMD_REDRAW_BILL     1005
#define CMD_NORMAL_REQ      1

#define CMD_NOORDER_BILL    1002

#define MAX_RDID_LEN        14
#define MAX_CLIENT_ID_LEN   9
#define DEF_ID_BUFF_SIZE    (64*sizeof(QY_RDID))

#define QY_MAX_CUSTID_LEN   8
#define QY_PSWD_MAX_LEN     8
#define QY_USER_MAX_LEN     16
#define QY_IPSTRING_LEN     16
#define QY_PHONE_MAX_LEN    20
#define MAX_GUID_LEN        29

#define QY_MAX_BARS         300

#define MAX_PER_FILE_SIZE   (1024*1024*4)

#define QY_HEAP_MEM_SIZE     (2*1024*1024)

#define SOCKET_TIMEOUT_TIMER  QINYI_TIMER_ID_START
#define EXIT_WINDOW_TIMER    (QINYI_TIMER_ID_START+1)
#define ASYN_CHECK           (QINYI_TIMER_ID_START+2)
#define ASYN_TASK            (QINYI_TIMER_ID_START+3)
#define MAX_LIST_TASK_NUM    (300)

#ifdef WIN32
#define MENU_TEXT   U8
#else
#define MENU_TEXT  __align(2) U8 
#endif

#ifndef offsetof
#define offsetof(s,m)   (size_t)&(((s *)0)->m)
#endif

#ifndef QY_MODULE
#define QY_MODULE   0
#endif

#define QyMalloc(sz)      FuncQyMalloc(sz, QY_MODULE, (unsigned short)__LINE__)
#define QyFree            FuncQyFree


#define  SRC_QINYI_SIGN_APP   SCR_QINYI_APP_WINDOW_19
#define  SRC_QINYI_LOGIN_APP  SCR_QINYI_APP_WINDOW_19
#define  SRC_SHOW_TASK_APP    SCR_QINYI_APP_WINDOW_19
#define  SRC_SETTING_AUTH     SCR_QINYI_APP_WINDOW_18
#define  SRC_SETTING_APP      SCR_QINYI_APP_WINDOW_19

#define SOC_EXT_MSG           0x10
#define ANY_SIZE  1

typedef U16 *  WSTR;

typedef enum qy_list_type_em
{
    QY_LIST_CAPTION = -1,
    QY_LIST_TEXT    = -2
}QY_LIST_TYPE_EM;


typedef enum storage_id
{
    QY_ROOT,
    QY_SETTING,
    QY_PROG,
    QY_USER,
    QY_TMP,
    QY_STORAGE_MAX
}QY_STORAGE_ID;

typedef enum te_Thread_status
{
    QYTSK_NOT_RUN,
    QYTSK_RUNNING,
    QYTSK_TERMINATE,
    QYTSK_SENDING  = 0x40,
    QYTSK_SUSPEND  = 0x80
}QYTHREAD_STATUS;


typedef enum te_new_bill_item
{
    NB_GUID = 0,
    NB_SEND_NAME,
    NB_SEND_ADDR,
    NB_SEND_PHONE,
    NB_GUID2,
    NB_GUID_STATE,
    MAX_NEW_BILL_ITEM 
}NEW_BILL_ITEM;

typedef enum te_redraw_item
{
    RD_GUID,
    RD_TYPE,
    RD_RESON,
    RD_NO,
    MAX_REDRAW_ITEM
}REDRAW_ITEM;


typedef enum authen_type
{
    UN_AUTHEN = 0,
    SERVER_AUTH,
    LOCAL_AUTH   ,
    QY_AUTHEND
}AUTHEN_TYPE;

typedef struct tag_usreinfo
{
    U16 name[QY_USER_MAX_LEN];
    U16 pwd[QY_PSWD_MAX_LEN];
}USER_INFO;

typedef struct tag_qysetting
{
    USER_INFO user_info;
    U16       pwd[QY_PSWD_MAX_LEN+1];
    U8        Host_ip[4];
    S32       Host_port;
    S32       AutoConnectTime;
    S32       BinHost_port;
    S32       ProgFLen;
    S32       ProgRamSize;
    S16       UpgradeMode;
}QY_SETTING_PROF;


typedef int (*FuncCmdAck)(int );
typedef enum te_file_type
{
    QYF_UNKOWN  = 0,
    QYF_RECIVE  = 1,
    QYF_SIGN    = 2 ,
    QYF_PROBLEM   = 3,
    QYF_MAX_TYPE,
    QYF_FILE_MASK = 0x0F,
    
    QYF_FAILE  = 0x40, //Asychonize send faile
    QYF_SENT   = 0x80,
    QYF_ACCEPT = 0x100,
    QYF_REJECT = 0x200,
    QYF_FWORD  = 0x400,
    QYF_CREATE = 0x800
}QYFILE_TYPE;

typedef struct _SIGN_JUNOR
{
    U16 name[QY_USER_MAX_LEN];
}SIGN_JUNOR;

typedef struct _PROBLEM_JOUNOR
{
    U16 ProblemID[4];
    U16 strOther[100];
}PROBLEM_JOUNOR;

typedef struct tagRecptNoBillProp
{
    BYTE Barcode[MAX_RDID_LEN+1];  /*运单号        变长,10或12个     */ 
    BYTE payeway;      /*支付类型      定长 2个          */
    UINT cost;         /*运费(原金额)  变长,最大13个     */  
    UINT cash;         /*代收货款金额  变长,最大13个     */    
    UINT insurence;    /*保价金额      变长,最大13个     */  
    UINT water;        /*流水号        定长,3个          */  
    BYTE sms_no[QY_PHONE_MAX_LEN];   /*短信通知号码  变长,最大20个 */    
}BILL_PROPERTY;

typedef struct tagBillInput
{
    int PayMethodSel;
    U16 ClientId[MAX_CLIENT_ID_LEN+1];    
    U16 en_water;
    U16 barcode[MAX_RDID_LEN+1];
    U16 bar_del[MAX_RDID_LEN+1];
    U16 water[3 + 1];
    U16 payway[2 + 1];
    U16 cost[13 +1];
    U16 cash[13+1];
    U16 insurence[13 + 1];
    U16 curency[13+1];
    U16 SMS_num[QY_PHONE_MAX_LEN+1];
}BILL_PREP_INPUT ;

typedef struct tag_BillPrepTbl
{
    BYTE guid[MAX_GUID_LEN+1];
    U16  type;
    int  Total;
    MYTIME gentime;
    BILL_PROPERTY prep[1];
}BILL_PREP_TBL;



typedef  U8  TYPE_RDID;

typedef struct _QY_RDID
{
    TYPE_RDID LaserId[MAX_RDID_LEN+2];
}QY_RDID;

typedef struct QY_STORE_INFO
{
    BYTE version;
    BYTE pad;
    U16  rdid_size;
}STORE_INFO;

typedef struct _TASK_HEADER
{   
    U32         tsksize;
    U16         filetype;
    U16         taskname[MAX_RDID_LEN+1];
    U16         totals;
    U16         MaxItms;
    MYTIME      GenTime;
    union{
        MYTIME  SendTime;
        STORE_INFO info;
    }u;
    U32         LenJunor;
    void     *  pJunor;
    void     *  pRdId;
}TASK_HEADER;

typedef enum te_QY_ERR
{
    QY_ERROR = -100,
    ERR_NOMORE_MEMORY,
    ERR_RDID_REPEAT,
    ERR_INVLD_PARMA,
    ERR_NOT_FONTD,
    ERR_FILE_NOT_OPEN,
    ERR_FILE_WRITING,
    ERR_NOT_AUTHENT,

    QY_SUCCESS = 0, 
    QY_FALSE = 0,
    QY_TRUE =1
}QY_ERR;


typedef enum te_NET_ERROR
{
    NET_ESTAB_FAIL = -3,
    NET_DATA_TIMOUT = -2,
    NET_CLOSE =  0,
    NET_DATA_IN = 1 
}NET_ERR;

typedef struct _QY_ALL_TASKINFO
{
    int Totls; 
    U8  findex[MAX_LIST_TASK_NUM];
    U32 offset[MAX_LIST_TASK_NUM];
    U8 *TitlePtr[MAX_LIST_TASK_NUM];
    U16 TitleBuff[MAX_LIST_TASK_NUM*(MAX_RDID_LEN+1)];    
}QY_ALL_TASKINFO; //34 * max size

typedef struct _NOB_ACK_INFO
{
    int result;
    int cmd;
    int err;
    int field;
    int buflen;
    void * pbuf;
}NOB_ACK;

extern QY_SETTING_PROF * g_SettingProf;

extern U16 g_QyFolders[][24];
void GetQyPathFile(U16 * buff, QY_STORAGE_ID qid, U16* filename);
int OpenQyFile(QY_STORAGE_ID qid, U16* filename, int mode);
int DeleteQyFile(QY_STORAGE_ID qid, U16* filename);
S32 OpenQyDir(QY_STORAGE_ID dir);
const U16 * GetQyDirName(QY_STORAGE_ID dir);
void InitStorage(void);
void SetQyLoginAuthenStatus(AUTHEN_TYPE  QyLogStatus);

int LoadQySetting(QY_SETTING_PROF *  pSetting);
int SaveQySettingProfile(QY_SETTING_PROF * psetting);

int QySendLoginCmd(U16 * user , U16 * pwd, int (*f)(int ret));
int GetAckTime(void *hack, MYTIME * tmack);
int QyGetAckLen(void);
int QyGetAckData(void * buff, int len); 
void * GetAckHandle( int * pcmd,int * perr, int * pFieldTotal, int * buflen);
void FreeAckHandle(void * packHandle);
int QySendSignRecptCmd(U16 * SignName, int totals, QY_RDID * pIds, FuncCmdAck f);

TASK_HEADER * CreateTask(QYFILE_TYPE ftype, int nInitalIdMax);
int  SetTaskJunor(TASK_HEADER * ptask, void * pJunor, int len_junor);
void * GetTaskJunor(TASK_HEADER * ptask);
int  AppendRdId(TASK_HEADER * ptask, U16 * pStrRDID);
int  RemoveRdId(TASK_HEADER * ptask, U16 * pStrRDID);
int  SaveTask(TASK_HEADER * ptask);
int  SendTask(TASK_HEADER * ptask, int bpromopt, FuncCmdAck f);
TASK_HEADER *  LoadTask(int ftype, int index);
void FreeTask(TASK_HEADER * ptask);

void StartQyAsySendThread(void);
void SuspendQyAsySendThread(void);
void ResumeQyAsySendThread(void);

U16 * QureyErrorString(int errcode);
void CancelNet(void);
void DisableKeyEvent(void);

void QyShowMessage(U16 * title, U16 * Info, FuncPtr fncExit);


void * FuncQyMalloc(unsigned int size, unsigned short MOD, unsigned short line);
void *FuncQyCalloc(unsigned int nmemb, unsigned int size);
void FuncQyFree(void *ptr);
unsigned int FuncQyMallocSetBlockSize(unsigned int blocksz);
void FuncInitQyHeap(void * buff, int len);

//U8 SetDelScrnIDCallbackHandler(U16 ScrnID, HistoryDelCBPtr funcPtr)
U16 GetCurScrnID(void);
int DeleleTask(int ftype, int index);
int QySocketConnect( U8 * pIp, int port, int(*fnxCb)(void*));
int OnUiUpdateStart(void);
void OnUiUpdateEnd(U16 srcid, int result);
int SendNextTask(void);
void QueryStatuByExpId(U16 * strExpId);
void OnUiCmdFinsh(NOB_ACK * nob_ack);
void * GetAckHandleEx( NOB_ACK * pack_info);
U16 * GetFeild(void * buff, int len, int idx);


int GetBillName(BYTE * buff, int total,  WSTR *pname);
int GetBillTotal(BYTE * buff);
void NewBillLookupDone(int fsh, int isErase);
int FindNexNewBill(int fsh, UINT * bill_size);
void LoadNewBillDetail(BYTE * buff, int index,int totals , WSTR * pdetail, U16 ftypeFilter);
int LoadNextNewBill(int fsh, BYTE * buff, UINT buf_size, UINT * read, U16 ftypeFilter);
int FindNewBill(UINT * bill_size);
int SaveNewBill(BYTE * pbuff, UINT len);
int SendRecptCmd(WSTR * redraw_item, int (*f)(int ));
int DeleteNewBill(WSTR  strGUID ,U16 FlagFilt, U16 DelWays)  ;

int ChkNewBill(FuncCmdAck f);
int OnChkNeBillCmdAck(int ret);
S32 mmi_ucs2toCurrency(const U16 *strSrc, S32 *out_num);

#endif /*_QINYI_APPTYPES_H*/
