//==================================================================================================
#include "Base.h"
#include "LoginCheck.h"
//==================================================================================================
// ====		Detours Start	==== //
//==================================================================================================
typedef hostent* (WINAPI *gethostbyname_t)(const char* name);
gethostbyname_t realgethostbyname = (gethostbyname_t)gethostbyname;
//==================================================================================================
char* serverName = NULL;
char* webName = NULL;
//==================================================================================================
hostent* WINAPI custom_gethostbyname(const char* name) {
	char* hostname = (char*)name;
	
	Logger(lDEBUG, "WS2_32", "GetHostByName (%s)", hostname);
	
	return realgethostbyname(hostname);
}

void WINAPI dllInit(HMODULE hModule)
{
	//HookFunc(g_pNet_Move_PG_Move_LtoC_AddToPartition,	Net_Move_PG_Move_LtoC_AddToPartition	);
	//HookFunc(g_pAddToPartition,							AddToPartition						    );
	//HookFunc(g_pCNetCli_Login_Login,					CNetCli_Login_Login						);

}
// ====		Detours End		==== //

namespace Nexus
{
	namespace BC2 
	{
		Base* Base::gInstance = NULL;

		Base* Base::GetInstance()
		{
			if(gInstance == NULL)
				gInstance = new Base;
			return gInstance;
		}

		// ==========================

		Base::Base()
		{
			HANDLE hModule = GetModuleHandle(NULL);

			dwCodeSize = Utils::GetSizeOfCode( hModule );
			dwCodeOffset = Utils::OffsetToCode( hModule );
			dwEntryPoint = (DWORD)hModule + dwCodeOffset;
		}

		int Base::CheckVersion()
		{
			// Check if there are any available updates
			VersionCheck::CheckForUpdates();

			return 1;
		}

		void Base::InitHooks(bool pIsServer)
		{
			PROT_BEGIN
			mIsServer = pIsServer;

			// Allocate a new console window for debugging purposes
			Utils::AllocateConsole("ChickenPickle - Debug Console");

			// Hook gethostbyname
			PBYTE offset = (PBYTE)GetProcAddress(GetModuleHandleA("ws2_32.dll"), "gethostbyname");
			realgethostbyname = (gethostbyname_t)DetourFunction(offset, (PBYTE)&custom_gethostbyname);

			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)dllInit, NULL, NULL, NULL);

			PROT_END
			PROT_CLEAR
		}

		bool Base::IsServer()
		{
			return mIsServer;
		}

		void Base::DeleteOldHook()
		{

		}
	}
}