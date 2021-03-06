
#include "GameGuard.h"
#include "..\..\ErrorList\errorlist.h"
#include "..\mainproc\ObjectDataClass.h"

#include "..\..\netwaker_member\net_login\NetCli_Login_Child.h"

#include "Rune Engine/Rune/UI/RuUI_Font.h"
//#pragma comment (lib, "SHInterfaceClient")
//#pragma comment (lib, "AHClientInterface")

// WITH APEX SETTING
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

CNPGameLib*				CGameGuard::m_pNpgl		= NULL;
bool					CGameGuard::m_bEnable	= false;
bool					CGameGuard::m_bExit		= false;

#include <windows.h>

CGameGuard::CGameGuard()
{
	//m_pNpgl = NULL;

}
//----------------------------------------------------------------------------
void CGameGuard::Init()
{
	if( m_pNpgl == NULL)
	{
		m_pNpgl	= new CNPGameLib("RunesKR");
	}



	//m_pNpgl->RunFAQ( dwResult );

}
//----------------------------------------------------------------------------
void CGameGuard::Enable( HWND hWnd )
{

	//CNetCli_Login::SM_GameGuardReport( 4, strlen("[REPORT] Report too big"), "[REPORT] Report too big" );

	if( m_pNpgl == NULL )
		return;

	m_bEnable = true;

	DWORD dwResult = m_pNpgl->Init();

	

	g_pLogList->AddMessage( "GameGuard Init() = %d", dwResult );
	

	if( dwResult != NPGAMEMON_SUCCESS )
	{
		TCHAR	msg[256];
		LPCSTR	lpszMsg;

		// 参照‘6. 主要错误代码’根据情况输出相关的信息。
		switch (dwResult)
		{
		case NPGAMEMON_ERROR_EXIST:				
			//lpszMsg = TEXT("GameGuard運行中，稍後或重啟後重新運行。");								break;
			lpszMsg = g_ObjectData->GetString( "NPGAMEMON_ERROR_EXIST" );							
			break;

		case NPGAMEMON_ERROR_GAME_EXIST:		
			//lpszMsg = TEXT("遊戲重複運行，或者GameGuard已運行。結束遊戲後請重新運行。");			break;
			lpszMsg = g_ObjectData->GetString( "NPGAMEMON_ERROR_GAME_EXIST" );						
			break;

		case NPGAMEMON_ERROR_INIT:				
			//lpszMsg = TEXT("GameGuard初始化錯誤。重啟後重新運行或者關閉其它可衝突軟體後運行。");	break;
			lpszMsg = g_ObjectData->GetString( "NPGAMEMON_ERROR_INIT" );							
			break;

		case NPGAMEMON_ERROR_AUTH_GAMEGUARD:
		case NPGAMEMON_ERROR_NFOUND_GG:
		case NPGAMEMON_ERROR_AUTH_INI:
		case NPGAMEMON_ERROR_NFOUND_INI:		
			//lpszMsg = TEXT("GameGuard設置文件已損壞或不存在。請重新安裝GameGuard軟體。");			break;
			lpszMsg = g_ObjectData->GetString( "NPGAMEMON_ERROR_AUTH_GAMEGUARD" );							
			break;

		case NPGAMEMON_ERROR_CRYPTOAPI:			
			//lpszMsg = TEXT("Window的部分檔已損壞。請重新安裝IE遊覽器。");							break;		
			lpszMsg = g_ObjectData->GetString( "NPGAMEMON_ERROR_CRYPTOAPI" );							
			break;		

		case NPGAMEMON_ERROR_EXECUTE:			
			//lpszMsg = TEXT("GameGuard運行失敗。請重新安裝GameGuard軟體。");							break;
			lpszMsg = g_ObjectData->GetString( "NPGAMEMON_ERROR_EXECUTE" );						
			break;

		case NPGAMEMON_ERROR_ILLEGAL_PRG:
			//lpszMsg = TEXT("非法軟體被發現。請關閉與遊戲無關軟體後重新運行。");
			//lpszMsg = TEXT("非法軟體被發現。請關閉與遊戲無關軟體後重新運行。");
			lpszMsg = g_ObjectData->GetString( "NPGAMEMON_ERROR_ILLEGAL_PRG" );	
			break;

		case NPGMUP_ERROR_ABORT:
			//lpszMsg = TEXT("GameGuard升級取消了。無法進行連接時請重新調整網路及個人防火牆的設置。");
			lpszMsg = g_ObjectData->GetString( "NPGMUP_ERROR_ABORT" );	
			break;
		case NPGMUP_ERROR_CONNECT:
			//lpszMsg = TEXT("連接GameGuard更新伺服器失敗了。稍後請再連接或檢查網路的狀態。");
			lpszMsg = g_ObjectData->GetString( "NPGMUP_ERROR_CONNECT" );	
			break;
		case NPGAMEMON_ERROR_GAMEGUARD:
			//lpszMsg = TEXT("GameGuard初始化錯誤或者GameGuard的舊版本檔。請重新安裝GameGuard軟體後再執行遊戲 。");
			lpszMsg = g_ObjectData->GetString( "NPGAMEMON_ERROR_GAMEGUARD" );	
			break;
		case NPGMUP_ERROR_PARAM:
			//lpszMsg = TEXT("ini檔沒有或者已損壞。重新安裝GameGuard軟體可以解決此問題 。");
			lpszMsg = g_ObjectData->GetString( "NPGMUP_ERROR_PARAM" );	
			break;
		case NPGMUP_ERROR_INIT:
			//lpszMsg = TEXT("npgmup.des初始化錯誤。請您將GameGuard資料夾刪除掉後，再執行遊戲。");
			lpszMsg = g_ObjectData->GetString( "NPGMUP_ERROR_INIT" );	
			break;
		case NPGMUP_ERROR_DOWNCFG:
			//lpszMsg = TEXT("GameGuard升級伺服器連接失敗。請稍後再試，或者重新調整個人防火牆。");
			lpszMsg = g_ObjectData->GetString( "NPGMUP_ERROR_DOWNCFG" );	
			break;
		case NPGMUP_ERROR_AUTH:
			//lpszMsg = TEXT("GameGuard更新無法正常執行。請暫時停止防毒軟體後再執行，或者使用PC管理軟體進行調整的設定。");
			lpszMsg = g_ObjectData->GetString( "NPGMUP_ERROR_AUTH" );	
			break;
		case NPGAMEMON_ERROR_NPSCAN:
			//lpszMsg = TEXT("病毒及木馬檢查模組記錄失敗。記憶體不足或病毒感染。");
			lpszMsg = g_ObjectData->GetString( "NPGAMEMON_ERROR_NPSCAN" );	
			break;
		default:
			// 輸出相關的結束資訊
			//lpszMsg = TEXT("GameGuard運行中出錯。在遊戲資料夾下位的GameGuard資料夾中*.erl檔添加在郵件附件中發送到gghelp@3zsafe.com。");
			lpszMsg = g_ObjectData->GetString( "NPGAMEMON_ERROR_UNKNOW" );	
			break;
		}
		wsprintf(msg,TEXT("GameGuard Error: %lu"), dwResult);
		MessageBox(NULL, lpszMsg, msg, MB_OK);

		CGameGuard::m_bExit = true;

	}

	SetHwnd( hWnd );	
}
//----------------------------------------------------------------------------
void CGameGuard::Release()
{
	if( m_pNpgl != NULL )
	{
		delete m_pNpgl;
		m_pNpgl		= NULL;
		m_bEnable	= false;
		m_bExit		= false;
	}
}
//----------------------------------------------------------------------------
void CGameGuard::SetHwnd( HWND hHandle )
{
	m_pNpgl->SetHwnd( hHandle );
}
//----------------------------------------------------------------------------
BOOL CALLBACK NPGameMonCallback( DWORD dwMsg, DWORD dwArg )
{

	g_pLogList->AddMessage( "GameGuard Callback() dwMsg[ %d ], dwArg[ %d ]", dwMsg, dwArg  );
	
	char	g_szHackMsg[1024];

	bool	bReturn		= true;
	bool	bAppExit	= false;
	bool	bMsg		= false;
	
	switch (dwMsg)
	{
	case NPGAMEMON_COMM_ERROR:
	case NPGAMEMON_COMM_CLOSE:
		{
			bAppExit	= true; // 结束代码
			bReturn		= false;
			bMsg		= false;
		} break;

	case NPGAMEMON_INIT_ERROR:
		{
			//wsprintf(g_szHackMsg, TEXT("初始化錯誤。"));
			wsprintf(g_szHackMsg, g_ObjectData->GetString("NPGAMEMON_INIT_ERROR") );
			bAppExit	= true;
			bReturn		= false;
			bMsg		= true;
		} break;

	case NPGAMEMON_SPEEDHACK:
		{
			//wsprintf(g_szHackMsg, TEXT("发现加速外挂。"));
			wsprintf(g_szHackMsg, g_ObjectData->GetString("NPGAMEMON_SPEEDHACK") );
			bAppExit	= true; // 结束代码
			bReturn		= false;
			bMsg		= true;
		} break;

	case NPGAMEMON_GAMEHACK_KILLED:
		{
			//wsprintf(g_szHackMsg, TEXT("发现游戏外挂。\r\n%s"),CGameGuard::m_pNpgl->GetInfo());
			wsprintf(g_szHackMsg, g_ObjectData->GetString("NPGAMEMON_GAMEHACK_DETECT") );
			bAppExit	= true; // 结束代码
			bReturn		= false;
			bMsg		= true;

			char szBuff[4096];
			sprintf( szBuff, "[KILLED] %s", CGameGuard::m_pNpgl->GetInfo() );
			CNetCli_Login::SM_GameGuardReport( 1, strlen(szBuff), szBuff );

		} break;

	case NPGAMEMON_GAMEHACK_DETECT:
		{
			//wsprintf(g_szHackMsg, TEXT("发现游戏外挂。\r\n%s"),CGameGuard::m_pNpgl->GetInfo());
			wsprintf(g_szHackMsg, g_ObjectData->GetString("NPGAMEMON_GAMEHACK_DETECT") );
			bAppExit	= true; // 结束代码
			bMsg		= true;
			bReturn		= false;

			char szBuff[4096];
			sprintf( szBuff, "[DETECT] %s", CGameGuard::m_pNpgl->GetInfo() );
			CNetCli_Login::SM_GameGuardReport( 2, strlen(szBuff), szBuff );
		} break;

	case NPGAMEMON_GAMEHACK_DOUBT:
		{
			//wsprintf(g_szHackMsg, TEXT("游戏或者GameGuard已损坏"));
			wsprintf(g_szHackMsg, g_ObjectData->GetString("NPGAMEMON_GAMEHACK_DOUBT") );
			bAppExit	= true; // 结束代码
			bReturn		= false;
			bMsg		= true;
		} break;
				
	case NPGAMEMON_GAMEHACK_REPORT:
		{
			DWORD dwHackInfoSize = 0;
			LPBYTE pHackInfo = NULL;
			pHackInfo = CGameGuard::m_pNpgl->GetHackInfo(&dwHackInfoSize);
			// pHackInfo = npgl.GetHackInfo(&dwHackInfoSize); // 如果是C++ 
			if (pHackInfo && dwHackInfoSize > 0)
			{
				// 以下函数不是GameGaurd提供的. 
				//SendToHackLog(pHackInfo, dwHackInfoSize); // 把信息传到服务器上.
				if( dwHackInfoSize < 4000 )
				{
					char szBuff[4000];
					memset( szBuff, 0, sizeof( szBuff ) );
					memcpy( szBuff, pHackInfo, dwHackInfoSize );
					CNetCli_Login::SM_GameGuardReport( 3, dwHackInfoSize, szBuff );
				}
				else
				{
					CNetCli_Login::SM_GameGuardReport( 4, strlen("[REPORT] Report too big"), "[REPORT] Report too big" );
				}
			}

			bAppExit	= true;
			bReturn		= false;
			bMsg		= true;

		} break;
	}

	if( bMsg == true )
	{
		WCHAR* str = MultiByteToWChar( g_szHackMsg );
		MessageBoxW( NULL, str, L"GameGuard", MB_OK );
		delete [] str;
	}

	CGameGuard::m_bExit = bAppExit;

	return bReturn;
}

bool CGameGuard::CheckExit()
{
	if( m_bEnable == true && m_bExit == true )
		return true;	
	return false;
}
