#pragma once

//#include "../NetBridge/NetBridge.h"


#include <Windows.h>

#include "NPGameLib.h"

class CGameGuard
{
public:
	CGameGuard();

	static	void			Init();
	static	void			Release();
	
	static	void			Enable					( HWND hWnd );

	static	void			SetHwnd					( HWND hHandle );
	static	bool			CheckExit				();
	//static	BOOL CALLBACK	 NPGameMonCallback		( DWORD dwMsg, DWORD dwArg);

	static	bool			m_bEnable;
	static	bool			m_bExit;
	static	CNPGameLib*		m_pNpgl;
};

//extern CApexClient* g_pApexClient;
