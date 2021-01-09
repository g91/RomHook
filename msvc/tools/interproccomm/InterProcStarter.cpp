
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

// �Ұ�
DWORD InterProcStarter::Start( const wchar_t* szExePath, wchar_t* szCommand, WORD wShowWindow )
{
	if( _waccess( szExePath, 0 ) > -1 )
	{
		// �I���X�ؿ�
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
		// ���� PROCESS_TERMINATE �v���}�� Process
		HANDLE hProc = OpenProcess( SYNCHRONIZE | PROCESS_TERMINATE, FALSE, dwPid );

		// �ϥ� Post WM_CLOSE �覡�q���L�h����
		EnumWindows( (WNDENUMPROC)TerminateWinProc, (LPARAM)dwPid );

		if( hProc != NULL )
		{
			// ���� 1 ��,  �p�G�٨S�����N�j���
			if( WaitForSingleObject( hProc, 1000 ) != WAIT_OBJECT_0 )
			{
				// �j���
				bRet = ( TerminateProcess( hProc, 0 ) == 0 );
			}
			else
				bRet = TRUE;

			CloseHandle( hProc );
		}
	}
	return bRet;
}

// ����
BOOL InterProcStarter::Close()
{
	BOOL bRet = CloseProcess( m_dwProcID );

/*
	if( m_dwProcID != IPC_INVALID_PROCESS_HANDLE )
	{	
		// ���� PROCESS_TERMINATE �v���}�� Process
		HANDLE hProc = OpenProcess( SYNCHRONIZE | PROCESS_TERMINATE, FALSE, m_dwProcID );

		// �ϥ� Post WM_CLOSE �覡�q���L�h����
		EnumWindows( (WNDENUMPROC)TerminateWinProc, (LPARAM)m_dwProcID );

		if( hProc != NULL )
		{
			// ���� 1 ��,  �p�G�٨S�����N�j���
			if( WaitForSingleObject( hProc, 1000 ) != WAIT_OBJECT_0 )
			{
				// �j���
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

					// DOS �ϺХN���ন Windows �b�Ϊ��ϺХN��
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