///////////////////////////////////////////////////////////////////////////////
//
//  Module: CrashRpt.h
//
//    Desc: Defines the interface for the CrashRpt.DLL.
//
// Copyright (c) 2003 Michael Carruth
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _CRASHRPT_H_
#define _CRASHRPT_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>

// CrashRpt.h
#ifdef CRASHRPTAPI

// CRASHRPTAPI should be defined in all of the DLL's source files as
// #define CRASHRPTAPI extern "C" __declspec(dllexport)

#else

// This header file is included by an EXE - export
#define CRASHRPTAPI extern "C" __declspec(dllimport)

#endif

// Client crash callback
typedef BOOL (CALLBACK *LPGETLOGFILE) (LPVOID lpvState);

enum CrashDumpTypeENUM
{
	EM_CrashDumpType_Mini,
	EM_CrashDumpType_Mid,
	EM_CrashDumpType_Full,
};

//-----------------------------------------------------------------------------
// Install
//    Initializes the library and optionally set the client crash callback and
//    sets up the email details.
//
// Parameters
//    pfn         Client crash callback
//    lpTo        Email address to send crash report
//    lpSubject   Subject line to be used with email
//
// Return Values
//    If the function succeeds, the return value is a pointer to the underlying
//    crash object created.  This state information is required as the first
//    parameter to all other crash report functions.
//
// Remarks
//    Passing NULL for lpTo will disable the email feature and cause the crash 
//    report to be saved to disk.
//
CRASHRPTAPI 
LPVOID 
Install(
   IN LPGETLOGFILE pfn OPTIONAL,                // client crash callback
   IN LPCTSTR lpTo OPTIONAL,                    // Email:to
   IN LPCTSTR lpSubject OPTIONAL                // Email:subject
   );

//-----------------------------------------------------------------------------
// Uninstall
//    Uninstalls the unhandled exception filter set up in Install().
//
// Parameters
//    lpState     State information returned from Install()
//
// Return Values
//    void
//
// Remarks
//    This call is optional.  The crash report library will automatically 
//    deinitialize when the library is unloaded.  Call this function to
//    unhook the exception filter manually.
//
CRASHRPTAPI 
void 
Uninstall(
   IN LPVOID lpState                            // State from Install()
   );

//-----------------------------------------------------------------------------
// AddFile
//    Adds a file to the crash report.
//
// Parameters
//    lpState     State information returned from Install()
//    lpFile      Fully qualified file name
//    lpDesc      Description of file, used by details dialog
//
// Return Values
//    void
//
// Remarks
//    This function can be called anytime after Install() to add one or more
//    files to the generated crash report.
//
CRASHRPTAPI 
void 
AddFile(
   IN LPVOID lpState,                           // State from Install()
   IN LPCTSTR lpFile,                           // File name
   IN LPCTSTR lpDesc                            // File desc
   );


//-----------------------------------------------------------------------------
// GenerateErrorReport
//    Generates the crash report.
//
// Parameters
//    lpState     State information returned from Install()
//    pExInfo     Pointer to an EXCEPTION_POINTERS structure
//
// Return Values
//    void
//
// Remarks
//    Call this function to manually generate a crash report.
//
CRASHRPTAPI 
int 
GenerateErrorReport(
					IN LPVOID lpState,
					IN PEXCEPTION_POINTERS pExInfo OPTIONAL
					);
//-----------------------------------------------------------------------------
// SetDxDiagOutput
//   設定要不要產生 DxDiagOutput的報表
//
// Parameters
//    lpState     State information returned from Install()
//     bSwitch       FALSE 關閉,Ture 打開
//
// Return Values
//    void
//
// Remarks
//    This function can be called anytime after Install() to Set DxDiagOutput Enable
//

CRASHRPTAPI 
void 
SetDxDiagOutput(
		IN LPVOID lpState,                           // State from Install()		
		IN BOOL bSwitch                            //  FALSE 關閉,True 打開
		);

//-----------------------------------------------------------------------------
// SetDxDiagOutput
//   設定要不要產生 自動存檔
//
// Parameters
//    lpState     State information returned from Install()
//     lpFile     檔名路徑
//     bSwitch    FALSE 關閉,Ture 打開
//
// Return Values
//    void
//
// Remarks
//    This function can be called anytime after Install() to Set DxDiagOutput Enable
//

CRASHRPTAPI 
void 
SetAutoSavePath(
				IN LPVOID lpState,                           // State from Install()		
				 IN LPCTSTR lpFile,                           // File name
				IN BOOL bSwitch                            //  FALSE 關閉,True 打開
				);
//設定客端版號
CRASHRPTAPI 
void SetClientVersion(
					  IN LPVOID lpState, // State from Install()	
					   IN LPCTSTR lpVersion // Version LPCTSTR
					   );


//設定上傳跟密碼與 自動上傳
CRASHRPTAPI 
void SetAutoUpload(
					  IN LPVOID lpState, // State from Install()	
					  IN LPCTSTR URL, // URL LPCTSTR
					  IN LPCTSTR PassWord, // PassWord LPCTSTR
					  IN BOOL bSwitch                            //  FALSE 關閉,True 打開
					  );

CRASHRPTAPI 
void SetUploadExe(
				   IN LPVOID lpState, // State from Install()	
				   IN LPCTSTR upload // upload exe name LPCTSTR
				  
				   );




CRASHRPTAPI void SetUploadExe(
							IN LPVOID lpState,// State from Install()	
							IN LPCTSTR reportExe // report exe name LPCTSTR
							);
CRASHRPTAPI void SetAppName(LPVOID lpState, LPCTSTR appName);
CRASHRPTAPI void SetString(LPVOID lpState, LPCTSTR report,LPCTSTR Context,LPCTSTR OK,LPCTSTR Cancel);
//-----------------------------------------------------------------------------
// SetCrashDumpType
//   設定產生的Crash dump的種類
//
// Parameters
//    lpState     State information returned from Install()
//	  type		  Crash dump type, 0=mini 1=mid 2=full
//
// Return Values
//    void
//
// Remarks
//    This function can be called anytime after Install()
//
CRASHRPTAPI void SetCrashDumpType(LPVOID lpState, CrashDumpTypeENUM type);

#endif
