
#include "InterProcStarter.h"
#include <io.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <Shlwapi.h>
#include <psapi.h>

typedef DWORD (WINAPI* PGNSI)(__in HANDLE hProcess, __out_ecount(nSize) LPWSTR lpImageFileName, __in DWORD nSize );

InterProcStarter::InterProcStarter()
{
	m_dwProcID = IPC_INVALID_PROCESS_HANDLE;
	m_hProcess = m_hThread = INVALID_HANDLE_VALUE;
}

InterProcStarter::~InterProcStarter()
{

}

// 啟動
DWORD InterProcStarter::Start( const wchar_t* szExePath, wchar_t* szCommand, WORD wShowWindow )
{
	if( _waccess( szExePath, 0 ) > -1 )
	{
		// 截取出目錄
		wchar_t szDir[ 1024 ];
		wcscpy_s( szDir, 1024, szExePath );

		wchar_t* szCh1	= wcsrchr( szDir, L'\\' );
		wchar_t* szCh2	= wcsrchr( szDir, L'/' );
		wchar_t* szCh	= szCh1 > szCh2? szCh1: szCh2;
		
		const wchar_t* pszDir = NULL;

		if( szCh )
		{
			*szCh = L'\0';
			pszDir = szDir;
		}

		STARTUPINFOW si = {0};
		PROCESS_INFORMATION pi;
		si.cb = sizeof( STARTUPINFO );
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = wShowWindow;

		if( CreateProcessW( szExePath, szCommand, NULL, NULL, NULL, FALSE, NULL, pszDir, &si, &pi ) )
		{
			m_dwProcID = pi.dwProcessId;
			m_hProcess = pi.hProcess;
			m_hThread  = pi.hThread;
			return pi.dwProcessId;
		}		
	}
	return 0;
}

BOOL CALLBACK TerminateWinProc( HWND hWnd, LPARAM lparam )
{
	DWORD dwProcID = lparam;

	if( hWnd )
	{
		DWORD dwPid ;
		GetWindowThreadProcessId( hWnd, &dwPid );

		if( hWnd && dwProcID == dwPid )
		{
			PostMessage( hWnd, WM_CLOSE, 0, 0 );
		}
	}
	return TRUE;
}


BOOL InterProcStarter::CloseProcess( DWORD dwPid )
{
	BOOL bRet = FALSE; 

	if( dwPid != IPC_INVALID_PROCESS_HANDLE )
	{	
		// 先用 PROCESS_TERMINATE 權限開啟 Process
		HANDLE hProc = OpenProcess( SYNCHRONIZE | PROCESS_TERMINATE, FALSE, dwPid );

		// 使用 Post WM_CLOSE 方式通知他去結束
		EnumWindows( (WNDENUMPROC)TerminateWinProc, (LPARAM)dwPid );

		if( hProc != NULL )
		{
			// 等待 1 秒,  如果還沒結束就強制結束
			if( WaitForSingleObject( hProc, 1000 ) != WAIT_OBJECT_0 )
			{
				// 強制中止
				bRet = ( TerminateProcess( hProc, 0 ) == 0 );
			}
			else
				bRet = TRUE;

			CloseHandle( hProc );
		}
	}
	return bRet;
}

// 關閉
BOOL InterProcStarter::Close()
{
	BOOL bRet = CloseProcess( m_dwProcID );

/*
	if( m_dwProcID != IPC_INVALID_PROCESS_HANDLE )
	{	
		// 先用 PROCESS_TERMINATE 權限開啟 Process
		HANDLE hProc = OpenProcess( SYNCHRONIZE | PROCESS_TERMINATE, FALSE, m_dwProcID );

		// 使用 Post WM_CLOSE 方式通知他去結束
		EnumWindows( (WNDENUMPROC)TerminateWinProc, (LPARAM)m_dwProcID );

		if( hProc != NULL )
		{
			// 等待 1 秒,  如果還沒結束就強制結束
			if( WaitForSingleObject( hProc, 1000 ) != WAIT_OBJECT_0 )
			{
				// 強制中止
				bRet = ( TerminateProcess( hProc, 0 ) == 0 );
			}
			else
				bRet = TRUE;

			CloseHandle( hProc );
		}
	}
*/
	CloseHandle( m_hProcess );	
	CloseHandle( m_hThread );	

	m_hProcess	= INVALID_HANDLE_VALUE;
	m_hThread	= INVALID_HANDLE_VALUE;

	return bRet;
}


BOOL InterProcStarter::IsProcessRunning( DWORD dwPID )
{
	BOOL exists = FALSE;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry))
		while (Process32Next(snapshot, &entry))
			if( entry.th32ProcessID == dwPID ) 
				exists = TRUE;

	CloseHandle(snapshot);
	return exists;
}
/*
// Function resolves the fosedevice name to drive name
BOOL InterProcStarter::GetDrive( LPCTSTR pszDosName, std::wstring& csDrive, bool bDriveLetterOnly )
{
	TCHAR tcDeviceName[50];
	TCHAR tcDrive[3] = _T("A:");

	// Iterating through the drive letters
	for ( TCHAR actDrive = _T('A'); actDrive <= _T('Z'); actDrive++ )
	{
		tcDrive[0] = actDrive;
		// Query the device for the drive letter
		if ( QueryDosDevice( tcDrive, tcDeviceName, 50 ) != 0 )
		{
			// Is this the drive letter we are looking for?
			if ( _tcsnicmp( tcDeviceName, pszDosName, _tcslen( tcDeviceName ) ) == 0 )
			{
				if( bDriveLetterOnly )
				{
					csDrive = tcDrive;
				}
				else
				{
					csDrive = pszDosName;

					size_t pos = csDrive.find( tcDeviceName );

					if( pos != std::wstring::npos )
					{
						csDrive.replace( pos, wcslen( tcDeviceName ), tcDrive );
					}
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}*/
/*
std::vector<unsigned long> InterProcStarter::FindProcByPath( const wchar_t* pszFilePath )
{
	std::vector< unsigned long > vecPids;

	BOOL exists = FALSE;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if( snapshot != INVALID_HANDLE_VALUE )
	{
		if (Process32First(snapshot, &entry))
		{
			do
			{
				HANDLE h = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, entry.th32ProcessID );

				if( h != NULL )
				{
					wchar_t szFileName[1024] = {0};
					PGNSI pGI = (PGNSI)GetProcAddress( GetModuleHandle( _T("psapi.dll")), "GetProcessImageFileNameW" );

					if( pGI != NULL )
						pGI( h , szFileName, 1024 );
					else
					{
						HMODULE hMod;
						DWORD cbNeeded;
						if ( EnumProcessModules( h, &hMod, sizeof(hMod), &cbNeeded) )
							GetModuleFileNameExW( h, hMod, szFileName, 1024 );
					}
					CloseHandle( h );

					// DOS 磁碟代號轉成 Windows 在用的磁碟代號
					std::wstring strFDFilePath( szFileName );
					/GetDrive( strFDFilePath.c_str(), strFDFilePath , false );

					if( _tcsicmp( pszFilePath, strFDFilePath.c_str() ) == 0 )
						vecPids.push_back( entry.th32ProcessID );
				}
			}while (Process32Next(snapshot, &entry));
		}
		CloseHandle(snapshot);
	}
	return vecPids;
}*/