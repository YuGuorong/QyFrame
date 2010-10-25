#define QY_MODULE     0x1
#include "QinYiCommon.h"

 /*****************************************************************************/
static S32 OpenQyStrDir(PS8 filepath)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    S32 fs_ret;
    FS_HANDLE file_handle;
 
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    fs_ret = 0;

    file_handle = FS_Open((kal_uint16*) filepath, FS_OPEN_DIR | FS_READ_ONLY);

    /* path already exist */
    if (file_handle >= 0)
    {
        FS_Close(file_handle);
        return 0;   /* already exist , 0 measn success in FS */
    }
    else if (file_handle == FS_FAT_ALLOC_ERROR)
    {
        fs_ret = FS_FAT_ALLOC_ERROR;
        return fs_ret;
    }
  

    //fmgr_main_notify_done(MMI_FMGR_NOTIFY_BEFORE_CREATE_FOLDER, buffer, FALSE, TRUE,NULL, FALSE, FALSE);
    /* create directory if it is not there */
    fs_ret = FS_CreateDir((PU16) filepath);

    if (fs_ret < 0)
    {
        return fs_ret;
    }
    //TODO: FS_SetAttributes((U16 *)filepath, FS_ATTR_DIR | FS_ATTR_HIDDEN);    

    return fs_ret;
}

U16 g_QyFolders[][24] = { 
    {(L"C:\\QinYiApp")}, 
    {(L"C:\\QinYiApp\\Settting")},
    {(L"C:\\QinYiApp\\Program")},
    {(L"C:\\QinYiApp\\User")},
    {(L"C:\\QinYiApp\\temp")}
};


void GetQyPathFile(U16 * buff, QY_STORAGE_ID qid, U16* filename)
{
    kal_wsprintf( buff, "%w\\%w", g_QyFolders[qid],filename);
}

int OpenQyFile(QY_STORAGE_ID qid, U16* filename, int mode)
{
    int fs_h ;
    U16 unicode_buf[256];
    if( mode & FS_READ_WRITE)
        mode |= FS_COMMITTED;
    
    GetQyPathFile( unicode_buf, qid, filename);

    
    fs_h = FS_Open(unicode_buf,mode );
    {                                                        \
        U8 asc_path[64];                              \
        mmi_wcs_to_asc((S8 *)asc_path, unicode_buf);          \
        kal_prompt_trace(MOD_MMI, "OpenQyFile path: [%s], %d", asc_path, fs_h); \
    }
    return fs_h;
    
}

int DeleteQyFile(QY_STORAGE_ID qid, U16* filename)
{
    int ret ;
    U16 unicode_buf[256];
    
   GetQyPathFile( unicode_buf, qid, filename);

    
    ret = FS_Delete(unicode_buf);
    {                                                        \
        U8 asc_path[64];                              \
        mmi_wcs_to_asc((S8 *)asc_path, unicode_buf);          \
        kal_prompt_trace(MOD_MMI, "DeleteQyFile path: [%s], %d", asc_path, ret); \
    }
    return ret;
}
 
S32 OpenQyDir(QY_STORAGE_ID filepath)
{
     return OpenQyStrDir((PS8)g_QyFolders[filepath]);	 
}

const U16 * GetQyDirName(QY_STORAGE_ID dir)
{
    return (const U16 *)g_QyFolders[dir];
}

void InitStorage(void)
{
    int drive_sys, drive_usr, i;
    
    drive_sys = FS_GetDrive(FS_DRIVE_I_SYSTEM, 1, FS_NO_ALT_DRIVE);/* Invisible NOR only */
    drive_usr = FS_GetDrive(FS_DRIVE_V_NORMAL, 1, FS_DRIVE_I_SYSTEM); /* Order: 1. Visible NOR 2. Invisible NOR */

    for(i=0 ; i<QY_STORAGE_MAX; i++)
    {
         g_QyFolders[i][0] = (U16)drive_usr;
         OpenQyStrDir((PS8)g_QyFolders[i]);
    }
    
}


U8  g_QySysScanEngineEn = 0;
void EnScanEngine( int bEnableScanSenser)
{
    g_QySysScanEngineEn = (U8) bEnableScanSenser;
}


const QY_SETTING_PROF g_QyDefaultSetting = 
{
    {L"01291.001",L""},
    L"12345678",
    {218,246,21,43},
    9988,
    600,
    9989,
    0,
    0,
    0
};

int SaveQySettingProfile(QY_SETTING_PROF * psetting)
{
    U32 wlen = 0;
    int mode = FS_READ_WRITE| FS_CREATE;
    int fs_h = /* OpenQyFile(QY_SETTING, L"profile.bin",FS_READ_ONLY);
    
    if(fs_h > 0 )    
    { 
        mode = FS_READ_WRITE;
        FS_Close(fs_h);
    }

    fs_h =*/ OpenQyFile(QY_SETTING, L"profile.bin",mode);
    psetting->BinHost_port = psetting->Host_port+1;
    if(fs_h)
    {
        FS_Seek(fs_h, 0, FS_FILE_BEGIN);
        FS_Write(fs_h, psetting,sizeof(QY_SETTING_PROF), &wlen);
        FS_Close(fs_h);
    }
    return (wlen==sizeof(QY_SETTING_PROF))? QY_SUCCESS : QY_ERROR;

}


int LoadQySetting(QY_SETTING_PROF *  pSetting)
{
    if( pSetting )
    {
        UINT rlen = 0;
        int fs_h  = OpenQyFile(QY_SETTING, L"profile.bin",FS_READ_ONLY);
        if( fs_h > 0 )
        {
    		FS_Seek(fs_h, 0, FS_FILE_BEGIN);
            FS_Read(fs_h, pSetting,sizeof(QY_SETTING_PROF), &rlen);
            FS_Close(fs_h);   
        }
        kal_prompt_trace(MOD_MMI,"LoadQySetting (file : %d)(len:%d)",fs_h, rlen);
        if( rlen < sizeof(QY_SETTING_PROF) )
        {
            memcpy(pSetting, &g_QyDefaultSetting, sizeof(QY_SETTING_PROF));
            SaveQySettingProfile(pSetting);
        }
    }
    return 0;
}

U32 CalcLocal(void)
{	
    U32 sum =0, buff;
	int fsh = OpenQyFile(QY_PROG, L"AppsEntry.bin", FS_READ_ONLY);
	if( fsh > 0 )
	{
		{
			UINT rd; 
            do{
                buff = 0;
    			FS_Read(fsh, &buff, 4, &rd);
                sum += buff;                
            }while(rd==4);
            kal_prompt_trace(MOD_MMI,"flex bin: %d", rd);
		}
		FS_Close(fsh);
	}
	return sum;
}



