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

	// �Ұʰ����� ( �p�G�Ұʦ��\��^ PID, ���ѴN��^ IPC_INVALID_PROCESS_HANDLE
	DWORD								Start(  const wchar_t* szExePath,  wchar_t* szCommand, WORD wShowWindow );

	// ����
	BOOL								Close();

	// �ˬd�{�ǬO�_�b����
	static BOOL							IsProcessRunning( DWORD dwPID );

	// ���w�����{��
	static BOOL							CloseProcess( DWORD dwPid );

	//// �̾ڸ��|, �M����� PID
	//static std::vector<unsigned long>	FindProcByPath( const wchar_t* pszFilePath );
};
