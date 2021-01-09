#include <stdlib.h>  //Include for C Runtime Invalid Parameter Check (see MSDN: "_set_invalid_parameter_handler")

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include <windows.h>
#include "CrashProcess.h"
#include "StackWalker/StackWalker.h"
#include "DebugLog/errormessage.h"
#include "CrashRpt/crashrpt.h"
#include "BaseFunction/BaseFunction.h"
#include "SmallObj/SmallObj.h"
#include "CreateDump/CreateDump.cpp"
#include <direct.h>



#define CHECK_TIME_GAP   10000
#define TIME_OUT_GAP     30000
#define MAX_CHECK_COUNT  15

HANDLE					CrashProcess::m_MainThreadHandle	= NULL;
DWORD					CrashProcess::m_dwCheckTick			= 0;
LPVOID					CrashProcess::m_LPV					= NULL;
bool					CrashProcess::m_bRunning			= false;
CrashProcessFunction	CrashProcess::m_OnCheck				= NULL;
CrashProcessFunction	CrashProcess::m_OnExit				= NULL;

void _RaiseException(LPVOID	LPV)
{
	if (!LPV)
		return;

	__try
	{
		RaiseException(EXCEPTION_BREAKPOINT, 0, 0, NULL);
	}
	__except(GenerateErrorReport(LPV, GetExceptionInformation())){}
}

void InvalidParameterHandler(const wchar_t* expression,
							 const wchar_t* function, 
							 const wchar_t* file, 
							 unsigned int line, 
							 uintptr_t pReserved)
{
	_RaiseException(CrashProcess::GetLPV());
}



bool CrashProcess::Init(HANDLE hMainThread, LPVOID lpV)
{
	if (hMainThread)
	{
		//Get Main Thread Handle for Generate call Stack
		DuplicateHandle(
			GetCurrentProcess(), 
			GetCurrentThread(), 
			GetCurrentProcess(),
			&m_MainThreadHandle, 
			0,
			FALSE,
			DUPLICATE_SAME_ACCESS);
	}

	m_LPV = lpV; 

	// Set invalid parameter handler to custom Handler
	_set_invalid_parameter_handler(InvalidParameterHandler);

	return true;
}

bool CrashProcess::Start()
{
	if (!m_bRunning)
	{
		Check();
		CreateThread( NULL , 0 , ServiceLoop , NULL , 0 , NULL );
		m_bRunning = true;
		return true;
	}

	return false;
}

void CrashProcess::Check()
{
	m_dwCheckTick = MytimeGetTime();
}

bool CrashProcess::Stop()
{
	if (m_MainThreadHandle)
	{
		CloseHandle(m_MainThreadHandle);
		m_MainThreadHandle = NULL;
	}

	m_bRunning    = false;
	m_LPV         = NULL;
	m_OnCheck	  = NULL;
	m_OnExit	  = NULL;
	m_dwCheckTick = 0;
	return true;
}


DWORD WINAPI CrashProcess::ServiceLoop( void* )
{
	int	CheckCount = 0;
	while (m_bRunning)
	{
		Sleep( CHECK_TIME_GAP );

		//VC模式不處理
		if (IsDebuggerPresent())
		{
			continue;
		}

		if( MytimeGetTime() - m_dwCheckTick <= TIME_OUT_GAP  )
		{
			//指定時間內有更新過
			CheckCount = 0;
			continue;
		}

		//指定時間內有未更新過, 增加檢查計數器
		CheckCount++;
		if( CheckCount < MAX_CHECK_COUNT )
		{
			if (m_OnCheck)
				m_OnCheck();
			continue;
		}
		//檢查次數到僅列印一次
		else if (CheckCount == MAX_CHECK_COUNT)
		{
			if (m_OnExit)
				m_OnExit();

			{//測試Code 產生dump
				_mkdir("Dump");
				wchar_t fileName[256];
				swprintf( fileName , L"Dump/Zone_%d.dmp" , TimeStr::Now_Value()  );
				CreateDump( fileName , EM_DumpType_MAX  );
			}
	
			// 印出 CallStack
			if (m_MainThreadHandle)
			{
				StackWalkerChild sw;
				sw.m_callStackStrings.clear();

				sw.ShowCallstack(m_MainThreadHandle);

				Print(LV5, "CrashProcess", "Print Call Stack");
				for (int i = 0 ; i < (int)sw.m_callStackStrings.size(); i++)
				{
					Print(LV5, "", sw.m_callStackStrings[i].c_str());
					g_pPrint->OutputBuffToFile();
				}
			}
		}

		return 0;
	}
	return 0;
}