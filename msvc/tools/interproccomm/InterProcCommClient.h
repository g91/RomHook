
#pragma once

#include "InterProcCommBase.h"

class CInterProcCommClient : public CInterProcCommBase
{


protected:

	HANDLE				m_hMainThead;

	unsigned long		m_uTryConnectTime;
	unsigned long		m_uTryConnectLastTick;

	bool				m_bStopProc;
	std::string			m_strPipeName;

protected:

	void				Destroy();
	static void			RunProc( LPARAM lparam );
	bool				InitPipe();

public:

	CInterProcCommClient();
	~CInterProcCommClient();

	// initital pipe 
	virtual bool		Init( const char* szPipeName );
	bool				RSThreadProc();

	// the time of try connect server
	void				SetTryConnectTime( unsigned long dwTime_ms );
	void				Process();

	// Check Pipe is exist
	static bool			IsPipeExist( const char* pszPipeName, int iTimeOut );

};