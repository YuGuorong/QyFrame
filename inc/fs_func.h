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
 *	fs_func.h
 *
 * Project:
 * --------
 *   Maui
 *
 * Description:
 * ------------
 *    This file declares the exported APIs
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
 *
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
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/
#ifndef _FS_TYPE_H
#error "Please include fs_type.h first..."
#endif

#ifndef _FS_FUNC_H
#define _FS_FUNC_H

#if defined(__SMART_PHONE_MODEM__)

#include "fs_ccci.h"

#define MD_FS_API(n, ...) MD##_##n(__VA_ARGS__)

// General I/O
#define FS_Open(...)					MD_FS_API(FS_Open, __VA_ARGS__)
#define FS_OpenHint(...)				MD_FS_API(FS_OpenHint, __VA_ARGS__)
#define FS_Close(...)					MD_FS_API(FS_Close, __VA_ARGS__)
#define FS_CloseAll(...)				MD_FS_API(FS_CloseAll, __VA_ARGS__)
#define FS_Read(...)					MD_FS_API(FS_Read, __VA_ARGS__)
#define FS_Write(...)					MD_FS_API(FS_Write, __VA_ARGS__)
#define FS_SetSeekHint(...)			-255//MD_FS_API(FS_SetSeekHint, __VA_ARGS__)
#define FS_Seek(...)					MD_FS_API(FS_Seek, __VA_ARGS__)
#define FS_Commit(...)				-255//MD_FS_API(FS_Commit, __VA_ARGS__)
#define FS_ReleaseFH(...)				-255//MD_FS_API(FS_ReleaseFH, __VA_ARGS__)
#define FS_Abort(...)					-255//MD_FS_API(FS_Abort, __VA_ARGS__)
#define FS_ParseFH(...)				-255//MD_FS_API(FS_ParseFH, __VA_ARGS__)
#define FS_GenVirtualFileName(...)		-255//MD_FS_API(FS_GenVirtualFileName, __VA_ARGS__)

//Information
#define FS_GetFileInfo(...)				-255//MD_FS_API(FS_GetFileInfo, __VA_ARGS__)
#define FS_GetFileSize(...)				MD_FS_API(FS_GetFileSize, __VA_ARGS__)
#define FS_GetFilePosition(...)			-255//MD_FS_API(FS_GetFilePosition, __VA_ARGS__)
#define FS_SetFileTime(...)			-255//MD_FS_API(FS_SetFileTime, __VA_ARGS__)
#define FS_GetAttributes(...)			MD_FS_API(FS_GetAttributes, __VA_ARGS__) /* Meta tool need this */
#define FS_GetFirstCluster(...)			-255//MD_FS_API(FS_GetFirstCluster, __VA_ARGS__)

//File Only Operation
#define FS_SetAttributes(...)			-255//MD_FS_API(FS_SetAttributes, __VA_ARGS__)
#define FS_Delete(...)					MD_FS_API(FS_Delete, __VA_ARGS__)
#define FS_PseudoMerge(...)			-255//MD_FS_API(FS_PseudoMerge, __VA_ARGS__)
#define FS_CheckFile(...)				-255//MD_FS_API(FS_CheckFile, __VA_ARGS__)

//Folder Only Operation
#define FS_GetCurrentDir(...)			-255//MD_FS_API(FS_GetCurrentDir, __VA_ARGS__)
#define FS_SetCurrentDir(...)			-255//MD_FS_API(FS_SetCurrentDir, __VA_ARGS__)
#define FS_CreateDir(...)				MD_FS_API(FS_CreateDir, __VA_ARGS__)
#define FS_RemoveDir(...)				MD_FS_API(FS_RemoveDir, __VA_ARGS__)
#define FS_GetFolderSize(...)			MD_FS_API(FS_GetFolderSize, __VA_ARGS__)

//File and Folder Operations
#define FS_Extend(...)					-255//MD_FS_API(FS_Extend, __VA_ARGS__)
#define FS_Truncate(...)				-255//MD_FS_API(FS_Truncate, __VA_ARGS__)
#define FS_MakeFileName(...)			-255//MD_FS_API(FS_MakeFileName, __VA_ARGS__)
#define FS_Rename(...)				MD_FS_API(FS_Rename, __VA_ARGS__)

#define FS_Move(...)					MD_FS_API(FS_Move, __VA_ARGS__)

#define FS_Count(...)					MD_FS_API(FS_Count, __VA_ARGS__)
#define FS_XDelete(...)				MD_FS_API(FS_XDelete, __VA_ARGS__)
#define FS_XDeleteEx(...)				-255//MD_FS_API(FS_XDeleteEx, __VA_ARGS__)

#define FS_CompactDir(...)				-255//MD_FS_API(FS_XDeleteEx, __VA_ARGS__)

//Find File
#define FS_FindFirst(...)				MD_FS_API(FS_FindFirst, __VA_ARGS__)
#define FS_FindNext(...)				MD_FS_API(FS_FindNext, __VA_ARGS__)
#define FS_FindFirstN(...)				-255//MD_FS_API(FS_FindFirstN, __VA_ARGS__)
#define FS_FindNextN(...)				-255//MD_FS_API(FS_FindNextN, __VA_ARGS__)
#define FS_FindClose(...)				MD_FS_API(FS_FindClose, __VA_ARGS__)

#ifdef __FS_SORT_SUPPORT__
#define FS_SortCompareFileName(...)     -255
#define FS_SortCompareFileType(...)     -255
#define FS_XFindReset(...)				-255//MD_FS_API(FS_XFindReset, __VA_ARGS__)
#define FS_XFindStart(...)				-255//MD_FS_API(FS_XFindStart, __VA_ARGS__)
#define FS_XFindClose(...)				-255//MD_FS_API(FS_XFindClose, __VA_ARGS__)
#endif

//Drive Management
#define FS_GetDrive(...)				MD_FS_API(FS_GetDrive, __VA_ARGS__)
#define FS_GeneralFormat(...)			-255//MD_FS_API(FS_GeneralFormat, __VA_ARGS__)
#define FS_GetClusterSize(...)			MD_FS_API(FS_GetClusterSize, __VA_ARGS__)
#ifdef __FS_QM_SUPPORT__
#define FS_QmGetFree(...)				-255//MD_FS_API(FS_QmGetFree, __VA_ARGS__)
#endif
#define FS_CreateBootSector(...)		0//MD_FS_API(FS_CreateBootSector, __VA_ARGS__)
#define FS_GetPartitionInfo(...)		-255//MD_FS_API(FS_GetPartitionInfo, __VA_ARGS__)
#define FS_CommitAll(...)				-255//MD_FS_API(FS_CommitAll, __VA_ARGS__)
#define FS_MappingDrive(...)			-255//MD_FS_API(FS_MappingDrive, __VA_ARGS__)

//Power Lost Detection and Recovery
#define FS_SetDiskFlag(...)			MD_FS_API(FS_SetDiskFlag, __VA_ARGS__)
#define FS_CheckDiskFlag(...)			-255//MD_FS_API(FS_CheckDiskFlag, __VA_ARGS__)
#define FS_ClearDiskFlag(...)			MD_FS_API(FS_ClearDiskFlag, __VA_ARGS__)
#ifdef __FS_CHECKDRIVE_SUPPORT__
#define FS_CheckDrive(...)			-255//MD_FS_API(FS_CheckDrive, __VA_ARGS__)
#endif

//Disk Management
#define FS_CreateMasterBootRecord(...)	0//MD_FS_API(FS_CreateMasterBootRecord, __VA_ARGS__)
#define FS_SplitPartition(...)				0//MD_FS_API(FS_SplitPartition, __VA_ARGS__)
#define FS_GetDiskInfo(...)				MD_FS_API(FS_GetDiskInfo, __VA_ARGS__)
#define FS_GetDevType(...)				-255//MD_FS_API(FS_GetDevType, __VA_ARGS__)
#define FS_GetDevStatus(...)				-255//MD_FS_API(FS_GetDevStatus, __VA_ARGS__)
#define FS_GetDevPartitions(...)			-255//MD_FS_API(FS_GetDevPartitions, __VA_ARGS__)

//Card management
#define FS_TestMSDC(...)				-255//MD_FS_API(FS_TestMSDC, __VA_ARGS__)
#define FS_CloseMSDC(...)				-255//MD_FS_API(FS_CloseMSDC, __VA_ARGS__)

//OTG Card Reader Management 
#define FS_ConfigExtDevice(...)		-255//MD_FS_API(FS_ConfigExtDevice, __VA_ARGS__)

//File System Run-Time LifeCycle
#define FS_ShutDown(...)				MD_FS_API(FS_ShutDown, __VA_ARGS__)
#define FS_UnlockAll(...)				MD_FS_API(FS_UnlockAll, __VA_ARGS__)
#define FS_SanityCheck(...)			-255//MD_FS_API(FS_SanityCheck, __VA_ARGS__)
#define FS_LockFAT(...)				MD_FS_API(FS_LockFAT, __VA_ARGS__)

//File System Run-Time Debug
#define FS_CountUsedFH(...)			-255//MD_FS_API(FS_CountUsedFH, __VA_ARGS__)
#ifdef __FS_TRACE_SUPPORT__
#define FS_SetTrace(...)				-255//MD_FS_API(FS_SetTrace, __VA_ARGS__)
#define FS_DumpFHTable(...)			-255//MD_FS_API(FS_DumpFHTable, __VA_ARGS__)
#endif

//DirCache
#define FS_SetDirCache(...)			-255//MD_FS_API(FS_SetDirCache, __VA_ARGS__)
#define FS_GetDirCache(...)			-255//MD_FS_API(FS_GetDirCache, __VA_ARGS__)
#define FS_ExpireDirCache(...)			-255//MD_FS_API(FS_ExpireDirCache, __VA_ARGS__)

//Flash Device Direct IO
#define FS_OTPWrite(...)				-255//MD_FS_API(FS_OTPWrite, __VA_ARGS__)
#define FS_OTPRead(...)				-255//MD_FS_API(FS_OTPRead, __VA_ARGS__)
#define FS_OTPQueryLength(...)		-255//MD_FS_API(FS_OTPQueryLength, __VA_ARGS__)
#define FS_OTPLock(...)				-255//MD_FS_API(FS_OTPLock, __VA_ARGS__)
#define FS_IOCtrl(...)              -255//MD_FS_API(FS_IOCtrl, __VA_ARGS__)

//Flash Sweep
#define FS_SweepDevice(...)			-255//MD_FS_API(FS_SweepDevice, __VA_ARGS__)

#if defined(__MTP_ENABLE__)
#define FS_MakeFilePathByHint(...)  -255//MD_FS_API(FS_MakeFilePathByHint, __VA_ARGS__)
#define FS_OpenFileByHint(...)      -255//MD_FS_API(FS_OpenFileByHint, __VA_ARGS__)
#define FS_DeleteByHint(...)        -255//MD_FS_API(FS_DeleteByHint, __VA_ARGS__)
#define FS_GetAttributesByHint(...) -255//MD_FS_API(FS_GetAttributesByHint, __VA_ARGS__)
#define FS_SetAttributesByHint(...) -255//MD_FS_API(FS_SetAttributesByHint, __VA_ARGS__)
#define FS_HintGetParent(...)       -255//MD_FS_API(FS_HintGetParent, __VA_ARGS__)
#endif /* __MTP_ENABLE__ */


// Others: not supported

#else /* !__SMART_PHONE_MODEM__ */
// General I/O
extern int FS_Open(const WCHAR * FileName, UINT Flag);
extern int FS_OpenHint(const WCHAR * FileName, UINT Flag, FS_FileOpenHint * DSR_Hint);
extern int FS_Close(FS_HANDLE FileHandle);
extern int FS_CloseAll(void);
extern int FS_Read(FS_HANDLE FileHandle, void * DataPtr, UINT Length, UINT * Read);
extern int FS_Write(FS_HANDLE FileHandle, void * DataPtr, UINT Length, UINT * Written);
extern int FS_SetSeekHint(FS_HANDLE FileHandle, UINT HintNum, FS_FileLocationHint * Hint);
extern int FS_Seek(FS_HANDLE FileHandle, int Offset, int Whence);
extern int FS_Commit(FS_HANDLE FileHandle);
extern int FS_ReleaseFH(void * TaskId);
extern int FS_Abort(UINT ActionHandle);
extern int FS_ParseFH(FS_HANDLE FileHandle);
extern int FS_GenVirtualFileName(FS_HANDLE FileHandle, WCHAR * VFileNameBuf, UINT BufLength, UINT VFBeginOffset, UINT VFValidLength);

//Information
extern int FS_GetFileInfo(FS_HANDLE FileHandle, FS_FileInfo * FileInfo);
extern int FS_GetFileSize(FS_HANDLE FileHandle, UINT * Size);
extern int FS_GetFilePosition(FS_HANDLE FileHandle, UINT * Position);
extern int FS_SetFileTime(FS_HANDLE FileHandle, const FS_DOSDateTime * Time);
extern int FS_GetAttributes(const WCHAR * FileName);
extern int FS_GetFirstCluster(FS_HANDLE FileHandle, UINT * Cluster);

//File Only Operation
extern int FS_SetAttributes(const WCHAR * FileName, BYTE Attributes);
extern int FS_Delete(const WCHAR * FileName);
extern int FS_PseudoMerge(const WCHAR * FileName1, const WCHAR * FileName2);
extern int FS_CheckFile(const WCHAR * FileName);

//Folder Only Operation
extern int FS_GetCurrentDir(WCHAR * DirName, UINT MaxLength);
extern int FS_SetCurrentDir(const WCHAR * DirName);
extern int FS_CreateDir(const WCHAR * DirName);
extern int FS_RemoveDir(const WCHAR * DirName);
extern int FS_GetFolderSize(const WCHAR *DirName, UINT Flag, BYTE *RecursiveStack, const UINT StackSize);

//File and Folder Operations
extern int FS_Extend(FS_HANDLE FileHandle, UINT Length);
extern int FS_Truncate(FS_HANDLE FileHandle);
extern int FS_MakeFileName(FS_HANDLE FileHandle, UINT Flag, WCHAR * FileName, UINT MaxLength);
extern int FS_Rename(const WCHAR * FileName, const WCHAR * NewName);

extern int FS_Move(const WCHAR * SrcFullPath, const WCHAR * DstFullPath, UINT Flag, FS_ProgressCallback Progress, BYTE *RecursiveStack, const UINT StackSize);

extern int FS_Count(const WCHAR * FullPath, UINT Flag, BYTE *RecursiveStack, const UINT StackSize);
extern int FS_XDelete(const WCHAR * FullPath, UINT Flag, BYTE *RecursiveStack, const UINT StackSize);
extern int FS_XDeleteEx(const WCHAR * FullPath, UINT Flag, FS_ProgressCallback Progress, BYTE *RecursiveStack, const UINT StackSize);

extern int FS_CompactDir(const WCHAR* DirName, UINT Flags);

//Find File
extern int FS_FindFirst(const WCHAR * NamePattern, BYTE Attr, BYTE AttrMask, FS_DOSDirEntry * FileInfo, WCHAR * FileName, UINT MaxLength);
extern int FS_FindNext(FS_HANDLE FileHandle, FS_DOSDirEntry * FileInfo, WCHAR * FileName, UINT MaxLength);
extern int FS_FindFirstN(const WCHAR * NamePattern, FS_Pattern_Struct * PatternArray, UINT PatternNum, BYTE ArrayMask, BYTE Attr, BYTE AttrMask, FS_DOSDirEntry * FileInfo, WCHAR * FileName, UINT MaxLength, UINT EntryIndex, UINT Flag);
extern int FS_FindNextN(FS_HANDLE Handle, FS_Pattern_Struct * PatternArray, UINT PatternNum, BYTE ArrayMask, FS_DOSDirEntry * FileInfo, WCHAR * FileName, UINT MaxLength, UINT Flag);
extern int FS_FindClose(FS_HANDLE FileHandle);

#ifdef __FS_SORT_SUPPORT__
extern int FS_SortCompareFileName(WCHAR *FileName1, WCHAR *FileName2);
extern int FS_SortCompareFileType(WCHAR *FileName1, WCHAR *FileName2);
extern int FS_XFindReset(FS_SortingParam *Param);
extern int FS_XFindStart(const WCHAR * Pattern, FS_DOSDirEntry * FileInfo, WCHAR * FileName, UINT MaxLength, UINT Index, UINT * Position, UINT Flag);
extern int FS_XFindClose(UINT * Position);
#endif

//Drive Management
extern int FS_GetDrive(UINT Type, UINT Serial, UINT AltMask);
extern int FS_GeneralFormat(const WCHAR * DriveName, UINT Level, FS_FormatCallback Progress);
extern int FS_GetClusterSize(UINT DriveIdx);
#ifdef __FS_QM_SUPPORT__
extern int FS_QmGetFree(const BYTE * Path);
#endif
extern int FS_CreateBootSector(void * BootSector, const FS_PartitionRecord * Partition, BYTE MediaDescriptor, UINT MinSectorsPerCluster, UINT Flags);
extern int FS_GetPartitionInfo(const WCHAR * DriveName, FS_PartitionRecord * PartitionInfo);
extern int FS_CommitAll(const WCHAR * DriveName);
extern int FS_MappingDrive(UINT UpperOldDrv, UINT UpperNewDrv);
extern int FS_SetVolumeLabel(const WCHAR * DriveName, const WCHAR * Label);
extern int FS_SwitchDriveMode(UINT DriveIdx, UINT Mode);

//Power Lost Detection and Recovery
extern int FS_SetDiskFlag(void);
extern int FS_CheckDiskFlag(void);
extern int FS_ClearDiskFlag(void);
#ifdef __FS_CHECKDRIVE_SUPPORT__
extern int FS_CheckDrive(const UINT DriveIdx, BYTE * CheckBuffer, const UINT CheckBufferSize);
#endif

//Disk Management
extern int FS_CreateMasterBootRecord(void * SectorBuffer, const FS_PartitionRecord * DiskGeometry);
extern int FS_SplitPartition(void * MasterBootRecord, UINT Sectors);
extern int FS_GetDiskInfo(const WCHAR * DriveName, FS_DiskInfo * DiskInfo, int Flags);
extern int FS_GetDevType(const WCHAR * Path);
extern int FS_GetDevStatus(UINT DriveIdx, UINT Flag);
extern int FS_GetDevPartitions(UINT QueryTarget);

//Card management
int FS_TestMSDC(void * slot_id, BYTE * drive_list, UINT * drive_num);
extern int FS_CloseMSDC(UINT MSDCIndex, UINT Mode);

//OTG Card Reader Management 
extern int FS_ConfigExtDevice(int Action, FS_Driver *DrvFuncs, int Slots, void **SlotIdArray, int *SlotsConfiged);

//File System Run-Time LifeCycle
extern void FS_ShutDown(void);
extern int FS_UnlockAll(void);
extern int FS_SanityCheck(void);
extern int FS_LockFAT(UINT Type);

//File System Run-Time Debug
extern int FS_CountUsedFH(int flag);
#ifdef __FS_TRACE_SUPPORT__
extern int FS_SetTrace(UINT Flag, UINT Timeout);
extern int FS_DumpFHTable(void);
#endif

//Copyright
#ifdef __P_PROPRIETARY_COPYRIGHT__
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
#endif

//DirCache
extern int FS_SetDirCache(FS_HANDLE FileHandle, UINT NewValue);
extern int FS_GetDirCache(FS_HANDLE FileHandle, UINT *CurrValue);
extern int FS_ExpireDirCache(FS_HANDLE FileHandle);

//Flash Device Direct IO
extern int FS_OTPWrite(int devtype, UINT Offset, void * BufferPtr, kal_uint32 Length);
extern int FS_OTPRead(int devtype, UINT Offset, void * BufferPtr, kal_uint32 Length);
extern int FS_OTPQueryLength(int devtype, UINT *Length);
extern int FS_OTPLock(int devtype);
extern int FS_IOCtrl(const WCHAR* DriveName, UINT CtrlAction, void* CtrlData);

//Flash Sweep or Recover
extern int FS_SweepDevice(const int devtype);
extern int FS_RecoverDevice(const int devtype);

#if defined(__MTP_ENABLE__)
extern int FS_MakeFilePathByHint(WCHAR DriveLetter, UINT DirCluster, UINT DirIndex, WCHAR * FileName, UINT MaxLength);
extern int FS_OpenFileByHint(WCHAR DriveLetter, UINT DirCluster, UINT DirIndex, UINT Flags);
extern int FS_DeleteByHint(WCHAR DriveLetter, UINT DirCluster, UINT DirIndex);
extern int FS_GetAttributesByHint(WCHAR DriveLetter, UINT DirCluster, UINT DirIndex);
extern int FS_SetAttributesByHint(WCHAR DriveLetter, UINT DirCluster, UINT DirIndex, BYTE Attributes);
extern int FS_HintGetParent(WCHAR DriveLetter, UINT DirCluster, UINT DirIndex, UINT *ParentCluster, UINT *ParentIndex);
#endif /* __MTP_ENABLE__ */

#endif /* __SMART_PHONE_MODEM__ */

#endif //_FS_FUNC_H

