
#pragma once

#include "InterProcCommBase.h"

class CInterProcCommHost : public CInterProcCommBase
{


protected:

	HANDLE				m_hMainThead;

	DWORD				m_uTryConnectLastTick;

	DWORD				m_uTryConnectTime;

	bool				m_bStopProc;

protected:

	void				RSThreadProc();

	static void			RunProc( LPARAM lparam );

	void				Detory();

public:

	CInterProcCommHost();
	~CInterProcCommHost();
	
	void				Process();

	// initital pipe 
	virtual bool		Init( const char* szPipeName );

	// �h�l�� ����n����
	void				StartProc();

};


