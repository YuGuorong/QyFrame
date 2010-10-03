/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
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

/*****************************************************************************
 *
 * Filename:
 * ---------
 *	fs_type.h
 *
 * Project:
 * --------
 *   Maui
 *
 * Description:
 * ------------
 *    This file defines the type/structure for export
 *
 * Author:
 * -------
 * -------
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 * removed!
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#ifndef _FS_TYPE_H
#define _FS_TYPE_H

/***************** Compile Option definition ***************************/

/* MUST SYNC! rtfiles.h & fs_type.h */
#ifdef __LOW_COST_SUPPORT_ULC__
#define __FS_PROPRIETARY_SET__
#endif /* __LOW_COST_SUPPORT_ULC__ */

#ifdef WISDOM_MMI
   #ifndef __FS_NATIVE_ENCODING_TRANSPARENT__
   #define __FS_NATIVE_ENCODING_TRANSPARENT__
   #endif
#endif

/************************************************************************/

/*------------------------- SPECIAL DEFINE -----------------------*/
#ifndef MAX_TLS_INDEX
#define MAX_TLS_INDEX            2
#endif

#define FS_TRACE_INDEX           2
#if defined(__FS_PROPRIETARY_SET__)
#define FS_MAX_PATH              64
#else
#define FS_MAX_PATH              520            //Max path length in SPEC
#endif /* __FS_PROPRIETARY_SET__ */
#define FS_GenVFN_SIZE           92             //buffer size for Virtual File (include NULL tail)
#define FS_BUFFER_SIZE           512

//Attributes in SPEC
#define FS_ATTR_READ_ONLY        0x01
#define FS_ATTR_HIDDEN           0x02
#define FS_ATTR_SYSTEM           0x04
#define FS_ATTR_VOLUME           0x08
#define FS_ATTR_DIR              0x10
#define FS_ATTR_ARCHIVE          0x20
#define FS_LONGNAME_ATTR         0x0F

//Customized Device List
#define FS_DEVICE_REMOVABLE      0x0008
#define FS_DEVICE_NOR_FLASH      0x0040
#define FS_DEVICE_NAND_FLASH     0x0080
#define FS_DEVICE_EXTERNAL       0x0800
#define FS_DEVICE_SIMPLUS       0x1000
#define FS_DEVICE_MEMORY_STICK  0x4000
#define FS_DEVICE_CHECK_PART    0x8000

//Device reserved flag
#define FS_DEVICE_COUNT_FREE_CLUSTER    0x40

/*-------------------- Parameter for APIs ---------------------*/
//FS_Open Parameter
#define FS_READ_WRITE            0x00000000L
#define FS_READ_ONLY             0x00000100L
#define FS_OPEN_SHARED           0x00000200L
#define FS_OPEN_NO_DIR           0x00000400L
#define FS_OPEN_DIR              0x00000800L
#define FS_CREATE                0x00010000L
#define FS_CREATE_ALWAYS         0x00020000L
#define FS_COMMITTED		         0x01000000L
#define FS_CACHE_DATA	         0x02000000L
#define FS_LAZY_DATA		         0x04000000L
#define FS_NONBLOCK_MODE			0x10000000L
#define FS_PROTECTION_MODE		   0x20000000L
#define FS_NOBUSY_CHECK_MODE		0x40000000L

//FS_GetDiskInfo Parameter
#define FS_DI_BASIC_INFO         0x00000001L
#define FS_DI_FREE_SPACE         0x00000002L
#define FS_DI_FAT_STATISTICS     0x00000004L
#define FS_DI_VOLUME_LABEL       0x00000008L

//FS_GetDrive Parameter
#define FS_NO_ALT_DRIVE          0x00000001
#define FS_ONLY_ALT_SERIAL       0x00000002
#define FS_DRIVE_I_SYSTEM        0x00000004
#define FS_DRIVE_V_NORMAL        0x00000008
#define FS_DRIVE_V_REMOVABLE     0x00000010
#define FS_DRIVE_V_EXTERNAL      0x00000020
#define FS_DRIVE_V_SIMPLUS      0x00000040

//FS_GeneralFormat Parameter
#define FS_FORMAT_HIGH           0x00000001
#define FS_FORMAT_LOW            0x00000002

#define FS_FMT_SINGLE_FAT        0x00000100L
#define FS_FMT_FORCE_LOW_LEVEL   0x00000200L
#define FS_FMT_NO_LOW_LEVEL      0x00000400L
#define FS_FMT_GET_DATA_SECTOR   0x00000800L
#define FS_FMT_FAT_12            0x00001000L
#define FS_FMT_FAT_16            0x00002000L
#define FS_FMT_FAT_32            0x00004000L
#define FS_FMT_NO_FAT_32         0x00008000L

#define FS_FLASH_NO_HIGH_FMT     0x20000000L
#define FS_FLASH_NO_LOW_FMT      0x40000000L

//FS_Move, FS_Count, FS_GetFolderSize, FS_XDelete, FS_XFindReset (Sorting) Parameter and Flag Passing
#define FS_MOVE_COPY             0x00000001     // FS_Move only, Public
#define FS_MOVE_KILL             0x00000002     // FS_Move only, Public

#define FS_FILE_TYPE             0x00000004     // Recursive Type API Common, Public
#define FS_DIR_TYPE              0x00000008     // Recursive Type API Common, Public
#define FS_RECURSIVE_TYPE        0x00000010     // Recursive Type API Common, Public

#define FS_NO_SORT               0x00000020     // Sort Parameter, Public
#define FS_SORT_NAME             0x00000040     // Sort Parameter, Public
#define FS_SORT_SIZE             0x00000080     // Sort Parameter, Public
#define FS_SORT_ATTR             0x00000100     // Sort Parameter, Public
#define FS_SORT_TYPE             0x00000200     // Sort Parameter, Public
#define FS_SORT_TIME             0x00000400     // Sort Parameter, Public
#define FS_SORT_USER             0x00080000     // Sort Parameter, User

#define FS_COUNT_SIZE            0x00000800     // QM internal for RecFolderAction (DEPARTED)
#define FS_REMOVE_CHECK          0x00001000     // QM internal for RecFolderAction (DEPARTED)
#define FS_FILTER_SYSTEM_ATTR    0x00002000     // FS_Count only, Public
#define FS_REC_COPYRIGHT_DEL     0x00004000     // FS_SweepCopyrightFile only, <Private, APP SHOULD NOT USE>
#define FS_REC_COPYRIGHT_LIST    0x00008000     // FS_GetCopyrightList only, <Private, APP SHOULD NOT USE>
#define FS_MOVE_OVERWRITE        0x00010000     // FS_Move only, Public
#define FS_XDEL_ABORT_WATCH      0x00020000     // FS_XDelete only, <Private, APP SHOULD NOT USE>
#define FS_FILTER_HIDDEN_ATTR    0x00040000     // FS_Count only, Public

//FSSetTrace Parameter
#define FS_TRACE_API             0x00000001
#define FS_TRACE_ERROR           0x00000002
#define FS_TRACE_DISABLE         0x00000004
#define FS_TRACE_ALL_TASK        0x00000008

//Quota Management
#define FS_QMAX_NO_LIMIT         0xf1f2f3f4 //~3.8GB
#define FS_COUNT_IN_BYTE         0x00000001
#define FS_COUNT_IN_CLUSTER      0x00000002

//FS_Abort Parameter
#define FS_ABORT_CHECK_DRIVE     0x12345678
#define FS_ABORT_XDELETE         0x87654321
#define FS_ABORT_MOVE            0xFEDCBA09

//FS_ConfigExtDevice Parameter
#define FS_SETUP_EXT_DEVICE      0x02468ACE
#define FS_RELEASE_EXT_DEVICE    0x13579BDF

// FS_SwitchDriveMode Parameter
#define FS_DRIVE_SOFT_UNMOUNT    0x00000001
#define FS_DRIVE_SOFT_MOUNT      0x00000002

// FS_CompactDir Parameter
#define FS_CMPCT_READ_ONLY       0x00000001
#define FS_CMPCT_RECURSIVE       0x00000002

// Size unit
#define FS_KB *1024
#define FS_MB *1024*1024

/*-------------------- Type Define --------------------*/

#if defined(GEN_FOR_PC)             /* Code Gen  */
   #define ONE_BYTE_ALIGN_ADS
#elif defined(__MTK_TARGET__)       /* Target    */
   #define ONE_BYTE_ALIGN_ADS __packed        // for unaligned access
#else                               /* Simulator */
   #define ONE_BYTE_ALIGN_ADS
#endif

#ifdef __MTK_TARGET__
typedef unsigned int	DWORD;
#endif  /* prevent "duplicate define" compiler warning on Simulator */

typedef unsigned short WORD;

#ifndef KAL_ON_THREADX
typedef unsigned int   UINT;
#endif

typedef unsigned char  BYTE;
typedef void * HANDLE;
typedef int FS_HANDLE;

typedef void (* FS_FormatCallback)(const char * DeviceName, int Action, UINT Total, UINT Completed);
typedef int FS_ProgressCallback(int Action, UINT Total, UINT Completed, UINT Info);
typedef int MTCallback(WCHAR * target1, WCHAR * target2, UINT Action, FS_ProgressCallback Progress); // internal RecFolderAction

typedef ONE_BYTE_ALIGN_ADS struct
{
   unsigned int Second2:5;
   unsigned int Minute:6;
   unsigned int Hour:5;
   unsigned int Day:5;
   unsigned int Month:4;
   unsigned int Year1980:7;
} FS_DOSDateTime;

typedef struct
{
   UINT Cluster;
   UINT Index;
   UINT Stamp;
   UINT Drive;
   UINT SerialNumber;
} FS_FileOpenHint;

typedef struct
{
   char                    FileName[8];
   ONE_BYTE_ALIGN_ADS char Extension[3];
   ONE_BYTE_ALIGN_ADS BYTE Attributes;
   ONE_BYTE_ALIGN_ADS BYTE NTReserved;
   ONE_BYTE_ALIGN_ADS BYTE CreateTimeTenthSecond;
   FS_DOSDateTime          CreateDateTime;
   ONE_BYTE_ALIGN_ADS WORD LastAccessDate;
   ONE_BYTE_ALIGN_ADS WORD FirstClusterHi;
   FS_DOSDateTime          DateTime;
   ONE_BYTE_ALIGN_ADS WORD FirstCluster;
   ONE_BYTE_ALIGN_ADS UINT FileSize;
   // FS_FileOpenHint members (!Note that RTFDOSDirEntry structure is not changed!)
   UINT                    Cluster;
   UINT                    Index;
   UINT                    Stamp;
   UINT                    Drive;
   UINT                    SerialNumber;
} FS_DOSDirEntry;

/*------------------------------------------------------------------------------
 * Retrieve FS_FileOpenHint structure from FS_DOSDirEntry structure
 *
 * Purpose: FS_FindFirst / FS_FindNext series APIs support open hint feature.
 * For minimum modification, we append FS_FileOpenHint members to FS_DOSDirEntry
 * structure.
 *-------------------------------------------------------------------- W09.19 --*/
#define FS_GetOpenHintByDOSDirEntry(DOSDirEntry) ((FS_FileOpenHint*)((BYTE*)&(((FS_DOSDirEntry*)(DOSDirEntry))->FileSize) + sizeof(UINT)))

// get file table index from a file handle
#define FS_GetFileTableIdx(FileHandle) ((FileHandle) & ((1 << (4 * sizeof(int))) - 1))

typedef struct
{
   UINT Cluster;
   UINT Index;
}FS_FileLocationHint;

typedef struct
{
   const FS_DOSDirEntry * DirEntry;
   UINT                  FilePos;
   UINT                  AllocatedSize;
   UINT                  ClusterChains;
   UINT                  VolumeSerialNumber;
   const char           * FullName;
}FS_FileInfo;

typedef struct
{
   char            Label[24];
   char            DriveLetter;
   BYTE            WriteProtect;
   char            Reserved[2];
   UINT            SerialNumber;
   UINT            FirstPhysicalSector;
   UINT            FATType;
   UINT            FATCount;
   UINT            MaxDirEntries;
   UINT            BytesPerSector;
   UINT            SectorsPerCluster;
   UINT            TotalClusters;
   UINT            BadClusters;
   UINT            FreeClusters;
   UINT            Files;
   UINT            FileChains;
   UINT            FreeChains;
   UINT            LargestFreeChain;
}FS_DiskInfo;

// for device CFI information query

typedef enum
{
   FS_DEV_NO_BOOT = 0,
   FS_DEV_DUAL_BOOT,
   FS_DEV_TOP_BOOT,
   FS_DEV_BOTTOM_BOOT
} FS_DEVICE_BOOT_LOCATION_ENUM; /* ! Must SYNC ! */

// FS_NANDDeviceInfo (RTFNANDDeviceInfo) related definition
#define FS_DEVICE_FLAG_VISIBLE   (0x00000001)

typedef struct
{
   BYTE  DeviceID[8];
   UINT  BlockSize;
   UINT  PageSize;
   UINT  DeviceSize;
   UINT  Flag;
} FS_NANDDeviceInfo; /* ! Must SYNC ! */

typedef struct
{
   BYTE  DeviceID[8];
   UINT  DeviceSize;
   BYTE  BootLocation;
} FS_NORDeviceInfo; /* ! Must SYNC ! */

typedef struct
{
   union
   {
      FS_NANDDeviceInfo NAND;
      FS_NORDeviceInfo  NOR;
   } DeviceInfo;
} FS_DeviceInfo; /* ! Must SYNC ! */

//For Driver START
typedef ONE_BYTE_ALIGN_ADS struct
{
   BYTE  BootIndicator,
         StartHead,
         StartSector,
         StartTrack,
         OSType,
         EndHead,
         EndSector,
         EndTrack;
   UINT  RelativeSector,
         Sectors;
} FS_PartitionRecord;

typedef ONE_BYTE_ALIGN_ADS struct
{
   BYTE BootCode[512-4*sizeof(FS_PartitionRecord)-sizeof(WORD)];
   FS_PartitionRecord PTable[4];
   WORD Signature;
} FS_MasterBootRecord;

typedef ONE_BYTE_ALIGN_ADS struct
{
   BYTE     PhysicalDiskNumber;
   BYTE     CurrentHead;
   BYTE     Signature;
   UINT     SerialNumber;
   BYTE     Label[11];
   char     SystemID[8];
}FS_ExtendedBIOSParameter;

typedef ONE_BYTE_ALIGN_ADS struct
{
   char     OEMName[8];
   WORD     BytesPerSector;
   BYTE     SectorsPerCluster;
   WORD     ReservedSectors;
   BYTE     NumberOfFATs;
   WORD     DirEntries;
   WORD     SectorsOnDisk;
   BYTE     MediaDescriptor;
   WORD     SectorsPerFAT;
   WORD     SectorsPerTrack;
   WORD     NumberOfHeads;
   UINT     NumberOfHiddenSectors;
   UINT     TotalSectors;
   ONE_BYTE_ALIGN_ADS union
   {
      ONE_BYTE_ALIGN_ADS struct
      {
         FS_ExtendedBIOSParameter BPB;
      } _16;
      ONE_BYTE_ALIGN_ADS struct
      {
         UINT     SectorsPerFAT;
         WORD     Flags;
         WORD     Version;
         UINT     RootDirCluster;
         WORD     FSInfoSector;
         WORD     BackupBootSector;
         BYTE     Reserved[12];
         FS_ExtendedBIOSParameter BPB;
      } _32;
   } E;
}FS_BIOSParameter;

typedef ONE_BYTE_ALIGN_ADS struct
{
   BYTE NearJump[3];
   FS_BIOSParameter BP;
   BYTE BootCode[512-3-sizeof(FS_BIOSParameter)-sizeof(WORD)];
   WORD Signature;
}FS_BootRecord;

typedef struct fsdriver
{
   int  (* MountDevice)    (void * DriveData, int DeviceNumber, int DeviceType, UINT Flags);
   int  (* ShutDown)       (void * DriveData);
   int  (* ReadSectors)    (void * DriveData, UINT Sector, UINT Sectors, void * Buffer);
   int  (* WriteSectors)   (void * DriveData, UINT Sector, UINT Sectors, void * Buffer);
   int  (* MediaChanged)   (void * DriveData);
   int  (* DiscardSectors) (void * DriveData, UINT Sector, UINT Sectors);
   int  (* GetDiskGeometry)(void * DriveData, FS_PartitionRecord * DiskGeometry, BYTE * MediaDescriptor);
   int  (* LowLevelFormat) (void * DriveData, const char * DeviceName, FS_FormatCallback Progress, UINT Flags);
   int  (* NonBlockWriteSectors)   (void * DriveData, UINT Sector, UINT Sectors, void * Buffer);
   int  (* RecoverableWriteSectors)(void * DriveData, UINT Sector, UINT Sectors, void * Buffer);
   int  (* ResumeSectorStates)     (void  * DriveData);
   int  (* HighLevelFormat)(void * DriveData, UINT BaseSector);
   int  (* RecoverDisk)    (void * DriveData);
   int  (* MessageAck)     (void * DriveData, int AckType);
   int  (* CopySectors)    (void * DriveData, UINT SrcSector, UINT DstSector, UINT Sectors);
   int  (* OTPAccess)      (void * DriveData, int type, UINT Offset, void * BufferPtr, UINT Length);
   int  (* OTPQueryLength) (void * DriveData, UINT *Length);
   int  (* IOCtrl)         (void * DriveData, UINT CtrlAction, void * CtrlData); // For device IO control
}FS_Driver;

#ifndef MMI_ON_WIN32

typedef struct _fsMutex
{
   kal_semid   mt_sem;
   kal_taskid	mt_sem_owner;
   kal_uint32	mt_lock_count;
   int         DeviceNum_1;
   int         DeviceNum_2;
}FS_Mutex;

#else

typedef UINT FS_Mutex;

#endif  /* MMI_ON_WIN32 */

struct _fsDrive;
struct _fsBuffer;

typedef struct _fsDeviceData
{
   FS_Mutex         * Lock;
   struct _fsDrive  * FirstDrive;
   BYTE               MediaPresent;
   BYTE               MediaRemovedReported;
   BYTE               Reserved;
   BYTE               MountState;
   int                SectorSize;
   FS_PartitionRecord Geometry;
   UINT               SectorShift;
   UINT               AccessCount;
   struct _fsBuffer * B;
   struct _fsBuffer * AltBuffer;
   int                ErrorCondition;
   int                PhysicalDiskIndex;
   char               FriendlyName[7];
   BYTE               MediaDescriptor;
}FS_DeviceData;

typedef struct _fsDevice
{
   int                DeviceType;
   int                DeviceNumber;
   UINT               DeviceFlags;
   FS_Driver        * Driver;
   void             * DriverData;
   FS_DeviceData      DevData;
}FS_Device;

typedef struct _fsDirEntry{
   UINT                 DirCluster;
   FS_FileLocationHint  LongPos;
   FS_FileLocationHint  ShortPos;
   FS_DOSDirEntry       Dir;
}FS_DirEntry;

typedef struct _fsDrive
{
   struct _fsDevice *   Dev;
   struct _fsDrive  *   NextDrive;
   int                  MountState;
   FS_PartitionRecord   Geometry;
   UINT                 Clusters;
   UINT                 SectorsPerCluster;
   UINT                 ClusterSize;
   UINT                 ClusterShift;
   UINT                 SPerCShift;
   UINT                 FATType;
   UINT                 FATCount;
   UINT                 SectorsPerFAT;
   UINT                 ClusterWatermark;
   UINT                 FreeClusterCount;
   UINT                 InfoSector;
   UINT                 SerialNumber;
   UINT                 FirstSector;
   UINT                 FirstFATSector;
   UINT                 FirstDirSector;
   UINT                 FirstDataSector;
   UINT                 RootDirEntries;
   FS_DirEntry          CurrDirEntry;
   char                 CurrDir[FS_MAX_PATH];
#ifdef __FS_QM_SUPPORT__
   BYTE                 QuotaMgt;
   BYTE                 Reserved[3];
#endif
}FS_Drive;

typedef struct _fsBuffer
{
   struct _fsBuffer * Next;
   struct _fsBuffer * Prev;
   FS_Device        * Dev;
   BYTE             * Data;
   UINT              Sector;
   struct _fsDrive  * FATSectorInfo;
   UINT              Flags;
   UINT              FirstDirtyTime,
                      LastDirtyTime;
   int                Num;
   BYTE               recoverable_flag;
#define    FS_RECOVERABLE_WRITE     1
#define    FS_NORMAL_WRITE          0
}FS_Buffer;
//For Driver END

typedef struct
{
   WCHAR Pattern[8];
}FS_Pattern_Struct;

typedef struct __fsQuotaStruct
{
   BYTE        Path[FS_MAX_PATH/2];
   UINT        Priority;
   UINT        Qmin;
   UINT        Qmax;
   UINT        Uint;
}FS_QuotaStruct;

typedef struct __fsInternQStruct
{
   UINT        Qmin;
   UINT        Qmax;
   UINT        Qnow;
}FS_InternQStruct;

typedef struct __fsFile
{
   FS_Drive             *  Drive;
   FS_Device            *  Dev;
   int                     SpecialKind;
   UINT                    Unique;
   UINT                    Flags;
   FS_DirEntry             DirEntry;
   UINT                    FilePointer;
   UINT                    LastCluster;
   UINT                    Cluster;
   UINT                    Offset;
   char                    FullName[FS_MAX_PATH];
   void                 *  Task;
   UINT                    HintNum;
   FS_FileLocationHint  *  Seek_Hint;
   BYTE                    Lock;
   BYTE                    Valid;
   BYTE                    Reserved[sizeof(int) - 2 * sizeof(BYTE)];
}FS_File;

typedef struct __fsTables
{
   FS_Drive  * DriveTable;
   FS_File   * FileTable;
   FS_Buffer * BufferTable;
   BYTE      * BufferData;
}FS_Tables;

typedef struct __fsExceptionData
{
   UINT      * Next;
   int         Data[11];
   int         XValue;
   int         State;
   int         IsHandled;
}FS_ExceptionData;

/*------------------------- ENUM TYPE -----------------------*/
//For Driver only
typedef enum
{
   FS_DEVICE_UNKNOWN,
   FS_DEVICE_FLOPPY,
   FS_DEVICE_FDISK
}FS_DRIVER_DEVICE_ENUM;

//For Driver->MessageAck only
typedef enum
{
   FS_DEV_IN_ACK_ENUM = 1,
   FS_DEV_SLOT_ACK_ENUM,
   FS_DEV_OUT_ACK_ENUM
}FS_ACK_TYPE_ENUM;


typedef enum
{
   FS_NO_WAIT,
   FS_INFINITE
}FS_TIMEOUT_ENUM;

//FS_Seek Parameter
typedef enum
{
   FS_FILE_BEGIN,
   FS_FILE_CURRENT,
   FS_FILE_END
}FS_SEEK_POS_ENUM;

//FS_GeneralFormat Callback Return Value
typedef enum
{
   FS_FMT_PGS_DONE = -1,
   FS_FMT_PGS_FAIL,
   FS_FMT_PGS_LOW_FMT,
   FS_FMT_PGS_HIGH_FMT
}FS_FORMAT_PGS_ENUM;

//FS_Move Callback Return Value
typedef enum
{
   FS_MOVE_PGS_FAIL = -1,
   FS_MOVE_PGS_PREPARE,
   FS_MOVE_PGS_START,
   FS_MOVE_PGS_ING,
   FS_MOVE_PGS_DONE
}FS_MOVE_PGS_ENUM;

//FS_XDelete Callback Return Value
typedef enum
{
   FS_XDELETE_PGS_FAIL = -1,
   FS_XDELETE_PGS_PREPARE,
   FS_XDELETE_PGS_START,
   FS_XDELETE_PGS_ING,
   FS_XDELETE_PGS_DONE
}FS_XDELETE_PGS_ENUM;

//Find Series Return Value
typedef enum
{
   FS_NOT_MATCH,
   FS_LFN_MATCH,
   FS_SFN_MATCH
}FS_FIND_ENUM;

//FS_GetDevType Return Value
//FS_GetDevStatus Paramter, Cannot overlap with 'A'~'Z' 0x41~0x5f
typedef enum
{
  FS_DEVICE_TYPE_NOR = 1,
  FS_DEVICE_TYPE_NAND,
  FS_DEVICE_TYPE_CARD,
  FS_DEVICE_TYPE_EXTERNAL,
  FS_DEVICE_TYPE_SIMPLUS,
  FS_DEVICE_TYPE_MAX_VALUE
}FS_DEVICE_TYPE_ENUM;

//FS_XFindStart, FS_FindFirstN, FS_FindNextN Parameter
typedef enum
{
   FS_FIND_DEFAULT,
   FS_FIND_LFN_TRUNC
}FS_GET_NAME_ENUM;

//Quota management
typedef enum
{
   FS_QP_HIG_ENUM,
   FS_QP_MID_ENUM,
   FS_QP_LOW_ENUM,
   FS_QP_DEL_ENUM
}FS_QP_ENUM;

//FS_GetDevStatus Parameter
typedef enum
{
   FS_MOUNT_STATE_ENUM,
   FS_FEATURE_STATE_ENUM,
   FS_EXPORT_STATE_ENUM,
   FS_CARD_BATCHCOUNT_STATE_ENUM
}FS_GET_DEV_STATUS_ENUM;

//FS_LockFAT Parameter
typedef enum
{
   FS_LOCK_USB_ENUM,
   FS_UNLOCK_USB_ENUM,
   FS_LOCK_BLOCK_ENUM,
   FS_LOCK_NONBLOCK_ENUM,
   FS_EXPORT_ENUM,
   FS_PURGE_HANDLE_ENUM,
   FS_REMOUNT_ENUM,
#if defined(__MTP_ENABLE__)
   FS_TASK_EXPORT_ENUM,
   FS_TASK_PURGE_HANDLE_ENUM,
   FS_TASK_REMOUNT_ENUM,
#endif /* __MTP_ENABLE__ */
   FS_CARD_BUSY_NONBLOCK_ENUM,
   FS_EXPORT_FINISHED_ENUM
}FS_LOCK_TYPE_ENUM;

typedef enum
{
   FS_NOT_EXPORTED = 0,
   FS_EXPORTING,
   FS_EXPORTED
}FS_LOCK_EXPORT_STATUS_ENUM;

//FS_CountUsedFH Parameter
typedef enum
{
   FS_FH_COUNT_CURRENT_TASK = 0,
   FS_FH_COUNT_AVAILABLE,
   FS_FH_COUNT_USED,
   FS_FH_COUNT_CONFIGURED
}FS_COUNT_USED_FH_ENUM;

//FDM OTPAccess Parameter
typedef enum
{
   FS_OTP_READ = 1,
   FS_OTP_WRITE,
   FS_OTP_LOCK
}FS_OTPACCESS_TYPE_ENUM;

//FS_Sort Callback Return Value
typedef enum
{
   FS_SORT_PGS_FAIL = -1,
   FS_SORT_PGS_PREPARE,
   FS_SORT_PGS_START,
   FS_SORT_PGS_ING,
   FS_SORT_PGS_DONE,
   FS_SORT_PGS_ABORT
}FS_SORT_PGS_ENUM;

typedef int (*SortingProgressCallback)(FS_SORT_PGS_ENUM Status, int Total, UINT Completed, void *CallbackParam);
typedef int (*SortingCompareFunc)(WCHAR *FileName1, UINT *Hint1, WCHAR *FileName2, UINT *Hint2);

typedef struct
{
    WCHAR *Pattern;
    FS_Pattern_Struct *PatternArray;
    UINT PatternNum;
    BYTE ArrayMask;
    BYTE AttrMask;
    UINT Flag;
    UINT Timeout;
    UINT * Position;
    SortingProgressCallback ProgressCallback;
    void *ProgressCallbackParam;
    SortingCompareFunc CompareFunc;
    BYTE *SortingBuffer;
    int SortingBufferSize;
    BYTE *WorkingBuffer;
    int WorkingBufferSize;
} FS_SortingParam;

// The working buffer contains              1. HintList(4) 2. HintList2(4) 3. FileName(520) 4. TmpName1(520) 5. TmpName2(520)
//                                          6. FileInfo(RTFDOSDirEntry)
// The sorting buffer contains              1. Sizeof(FSSortingInternalS) 2. PosList(8)

#define FS_SORT_WORKING_BUFFER_SIZE         ((FS_SORTING_MAX_FILES*(4+4))+3*(FS_MAX_PATH+4)+sizeof(FS_DOSDirEntry))
#define FS_SORT_SORTING_BUFFER_SIZE         ((FS_SORTING_MAX_FILES*8)+(20*4) /* sizeof(FSSortingInternalS) */)

#define FS_SORT_WORKING_BUFFER_SIZE_FOR_FILES(x)         (((x+3)*(4+4))+3*(FS_MAX_PATH+4)+sizeof(FS_DOSDirEntry))
#define FS_SORT_SORTING_BUFFER_SIZE_FOR_FILES(x)         (((x+3)*8)+(20*4) /*sizeof(FSSortingInternalS)*/)

#define FS_SORT_CB_SUCCESS                  0
#define FS_SORT_CB_ABORT                    (-1)

#define FS_MOVE_BUFFER_SIZE_FOR_FOLDER_LEVEL(x)         (72+3*(FS_MAX_PATH+4+sizeof(int))+2048+x*52)
#define FS_XDELETE_BUFFER_SIZE_FOR_FOLDER_LEVEL(x)      (72+3*(FS_MAX_PATH+4+sizeof(int))+x*52)

// IO control
typedef enum {
   FS_IOCTRL_DEVICE_UNKNOWN,
   FS_IOCTRL_DEVICE_CAS_CARD // CMMB CAS full card
} FS_IOCTRL_DEVICE_TYPE_ENUM;

typedef enum {
   FS_IOCTRL_QUERY_DEVICE_TYPE,
   FS_IOCTRL_QUERY_NAND_INFO,
   FS_IOCTRL_QUERY_NOR_INFO,
   FS_IOCTRL_SET_COMMAND_SECTOR  // for CMMB CAS full card
} FS_IOCTRL_ACTION_ENUM; /* ! Must SYNC ! */

/*------------------------------
 * FS Internal Hint Management
 *------------------------------*/

typedef enum {
   FS_HINT_FREE = 0,
   FS_HINT_ALLOCATED,
   FS_HINT_CREATING,
   FS_HINT_STABLE,
   FS_HINT_STABLE_LOCKED,
   FS_HINT_DELETED_LOCKED
} FS_OpenHintStatusEnum; /* ! Must SYNC ! */

typedef struct {
   UINT     Cluster;                  // zero if none
   UINT     Index;                    // undefined if none
   UINT     DirCluster;
} FS_OpenHintLocation; /* ! Must SYNC ! */

// FS internal open hint
typedef struct {
   FS_OpenHintStatusEnum Status;
   BYTE                  FirstLevel;
   BYTE                  HintNum;
   BYTE                  FirstHint;
   BYTE                  HitStamp;
   BYTE                  Flag;
   WORD                  PathLength;
   FS_Drive              *Drive;
   UINT                  SerialNumber;
   FS_OpenHintLocation   *Location;
   WCHAR                 Path[FS_MAX_PATH / 2];
} FS_OpenHintPath; /* ! Must SYNC ! */

// FS external open hint
typedef struct {
   // RTFDirLocation
   UINT Cluster;
   UINT Index;
   // Extension
   BYTE Level;
   BYTE PathIndex;
   BYTE MatchType;
   BYTE Flag;
   UINT DirCluster;
} FS_OpenHintInt; /* ! Must SYNC ! */

#endif //_FS_TYPE_H

