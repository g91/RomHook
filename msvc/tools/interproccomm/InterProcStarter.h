#pragma once

#include <Windows.h>
#include <vector>

#define IPC_INVALID_PROCESS_HANDLE 0xFFFFFFFF

class InterProcStarter
{

protected:

	DWORD			m_dwProcID;
	HANDLE			m_hProcess;
	HANDLE			m_hThread;


public:

	//static BOOL							GetDrive( LPCTSTR pszDosName, std::wstring& csDrive, bool bDriveLetterOnly );



public:
	InterProcStarter(void);
	~InterProcStarter(void);

	DWORD								GetProcessID(){ return m_dwProcID; }

	// 啟動執行檔 ( 如果啟動成功返回 PID, 失敗就返回 IPC_INVALID_PROCESS_HANDLE
	DWORD								Start(  const wchar_t* szExePath,  wchar_t* szCommand, WORD wShowWindow );

	// 關閉
	BOOL								Close();

	// 檢查程序是否在執行
	static BOOL							IsProcessRunning( DWORD dwPID );

	// 指定關閉程序
	static BOOL							CloseProcess( DWORD dwPid );

	//// 依據路徑, 尋找相關 PID
	//static std::vector<unsigned long>	FindProcByPath( const wchar_t* pszFilePath );
};
