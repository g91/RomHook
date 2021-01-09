#include <windows.h>
#include <DbgHelp.h>
#include "CreateDump.h"
#include "../DebugLog/ErrorMessage.h"


bool CreateDump( const wchar_t* lpszFileName , DumpTypeENUM type )
{
	BOOL Result = FALSE;

	HANDLE hFile = CreateFileW( lpszFileName, GENERIC_READ | GENERIC_WRITE, 
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

	if( ( hFile != NULL ) && ( hFile != INVALID_HANDLE_VALUE ) ) 
	{
		MINIDUMP_TYPE mdt = MiniDumpNormal;

		switch (type)
		{
		case EM_DumpType_MID:
			mdt = (MINIDUMP_TYPE)(MiniDumpWithPrivateReadWriteMemory | 
				MiniDumpWithDataSegs | 
				MiniDumpWithHandleData |
				MiniDumpWithUnloadedModules ); 
			break;
		case EM_DumpType_MAX:
			mdt = (MINIDUMP_TYPE)(MiniDumpWithFullMemory | 
				MiniDumpWithHandleData | 
				MiniDumpWithUnloadedModules ); 
			break;
		}

		HANDLE hProcess = GetCurrentProcess();
		unsigned long dwPID =  GetCurrentProcessId();

		Result = MiniDumpWriteDump( hProcess, dwPID, hFile, mdt, NULL, NULL, NULL ); 

		CloseHandle( hFile );
		CloseHandle( hProcess );

		if( !Result )
			Print(LV5, "CreateDump", "MiniDumpWriteDump failed. Error: %u", GetLastError() ); 

	}
	else
	{
		Print(LV5, "CreateDump", "Create file %s failed. ", lpszFileName ); 
	}

	return (Result == TRUE);
}