#include "StdAfx.h"
#include "detours.h"
#include "Utils.h"

typedef hostent* (WINAPI *gethostbyname_t)(const char* name);
gethostbyname_t realgethostbyname = (gethostbyname_t)gethostbyname;

char* serverName = NULL;
char* webName = NULL;

hostent* WINAPI custom_gethostbyname(const char* name) {
	char* hostname = (char*)name;
	/*
	Logger(lDEBUG, "WS2_32", "GetHostByName (%s)", hostname);

	// Check if the host is related to EA
	unsigned int PlasmaC = oneAtATimeHash("bfbc2-pc.fesl.ea.com");
	unsigned int TheaterC = oneAtATimeHash("bfbc2-pc.theater.ea.com");

	unsigned int PlasmaS = oneAtATimeHash("bfbc2-pc-server.fesl.ea.com");
	unsigned int TheaterS = oneAtATimeHash("bfbc2-pc-server.theater.ea.com");

	unsigned int Easo = oneAtATimeHash("easo.ea.com");
	unsigned int current = oneAtATimeHash((char*)name);
	
	// If so return our hostname
	if (current == PlasmaC || current == TheaterC || current == Easo || current == PlasmaS || current == TheaterS) {
		if (!serverName) {
			serverName = "bfbc2.emulatornexus.com";
			//serverName = "localhost";
		}
		hostname = serverName;
	}
	*/
	return realgethostbyname(hostname);
}

void (__cdecl* logPrintF)(int a1, int a2, int a3, const char *Src);

void __cdecl cLogPrintF(int a1, int a2, int a3, const char *Src)
{
	Logger(lDEBUG, "cLog", "[%s] %s", Src, (char*)a1);

	return logPrintF(a1, a2, a3, Src);
}

void (__stdcall* JoinGame)(int xuid, int requestAttribs, int playerType);

void __stdcall cJoinGame(int xuid, int requestAttribs, int playerType)
{
	 void* th; 
	__asm mov [th], ecx    

	Logger(lDEBUG, "JoinGame", "[%d] %d (%d)", xuid, requestAttribs, playerType);

	__asm mov ecx, [th]
	return JoinGame(xuid, requestAttribs, playerType);
}

void (__stdcall* AllowPlayerEntry)(int ref, bool allow, int reason);

void __stdcall cAllowPlayerEntry(int ref, bool allow, int reason)
{
	 void* th; 
	__asm mov [th], ecx    

	Logger(lDEBUG, "AllowPlayerEntry", "[%d] %d (%d)", ref, reason, allow);

	__asm mov ecx, [th]
	return AllowPlayerEntry(ref, allow, reason);
}

void (__stdcall* AllowPlayerEntryInternal)(int *player, bool allow, int reason);

void __stdcall cAllowPlayerEntryInternal(int *player, bool allow, int reason)
{
	 void* th; 
	__asm mov [th], ecx    

	int pID = *(int*)((char*)player + 0x0C);

	Logger(lDEBUG, "AllowPlayerEntryInternal", "[%d] %d (%d)", pID, reason, allow);

	__asm mov ecx, [th]
	return AllowPlayerEntryInternal(player, allow, reason);
}
int (__cdecl* setPacketValue)(int a1, int a2, int a3, signed int a4);

int __cdecl cSetPacketValue(int a1, int a2, int a3, signed int a4)
{
	// returnEncryptedInfo
	if (a3 == 25332276)
		a4 = 0;

	return setPacketValue(a1, a2, a3, a4);
}

int (__cdecl* isDebugEnabled)(int a1);

int __cdecl cIsDebugEnabled(int a1)
{
	Logger(lDEBUG, "BC2Game", "IsDebugEnabled (%d)", a1);
	return 1;
}

int (__cdecl* unknownFuncHook)(int a1, const char *a2);

int __cdecl cUnknownFuncHook(int a1, const char *a2)
{
	if (!strcmp(a2, "localhost"))
	{
		Logger(lDEBUG, "UNK", "%d, %s", a1, a2);
		return 0;
	}

	return unknownFuncHook(a1, a2);
}

void PatchSSL(bool ISDEDI)
{
	Logger(lDEBUG, "Main", "Patching SSL Certificate Verification");

	if (ISDEDI)
	{
		*(BYTE*)0xE5C269 = 0x15;
		*(BYTE*)0xE5C26A = 0x00;
	}
	else
	{
		//*(BYTE*)0x1186339 = 0x15;
		//*(BYTE*)0x118633A = 0x00;

		*(BYTE*)0xD826B9 = 0x15;
		*(BYTE*)0xD826BA = 0x00;
	}	
}

void PatchServerLogin()
{
	// Was bfbc2.server.pc@ea.com
	const char* lUser = "bc2.server@alteriw.net";	
	//strcpy((char*)0x17732E8, lUser);

	// Was Che6rEPA
	const char* lPass = "5sG29dHn";	
	//strcpy((char*)0x17732DC, lPass);
}

void InitBC2Client()
{
	// Allocate Console Window
	AllocConsole() ;
	AttachConsole( GetCurrentProcessId() );
	freopen( "CON", "w", stdout ) ;
	SetConsoleTitle( L"BC2 Client Debug Console" );

	// Resize console (max length)
	COORD cordinates = {80, 32766};
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(handle, cordinates);

	Logger(lINFO, "Main", "Starting BC2 Client");

	// Hook GetHostByName function
	PBYTE offset = (PBYTE)GetProcAddress(GetModuleHandleA("ws2_32.dll"),"gethostbyname");
	realgethostbyname = (gethostbyname_t)DetourFunction(offset, (PBYTE)&custom_gethostbyname);
	
	//logPrintF = (void (__cdecl*)(int a1, int a2, int a3, const char *Src))DetourFunction((PBYTE)0xF0E610, (PBYTE)cLogPrintF);
	//isDebugEnabled = (int (__cdecl*)(int a1))DetourFunction((PBYTE)0xF0E8D0, (PBYTE)cIsDebugEnabled);

	// Possibly Game Joining Function
	// void __thiscall Fesl::GameManagerImpl::JoinGame(Fesl::GameManagerImpl *this, const unsigned __int64 *xuid, Fesl::AttributeMap *requestAttribs, Fesl::GamePlayerType playerType)
	//JoinGame = (void (__stdcall*)(int xuid, int requestAttribs, int playerType))DetourFunction((PBYTE)0x00DBDE00, (PBYTE)cJoinGame);

	// Patch SSL Certificate Validation
	PatchSSL(false);
	// 0xF0E8D0 isDebugEnabled? (int __cdecl sub_F0E8D0(int a1))

	Logger(lINFO, "Main", "Patching server version validation");
	const char* lRomePC = "\"ROMEPC133769\""; // Was ROMEPC784592
	strcpy((char*)0x1418604, lRomePC);

	// void Log(int a1, const char *Format, ...)
	// 0xF0EA20
	// Console logging function anyone?
}

void InitBC2Server()
{
	// Allocate Console Window
	AllocConsole() ;
	AttachConsole( GetCurrentProcessId() );
	freopen( "CON", "w", stdout ) ;
	SetConsoleTitle( L"BC2 Server Debug Console" );

	// Resize console (max length)
	COORD cordinates = {80, 32766};
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(handle, cordinates);

	Logger(lINFO, "Main", "Starting BC2 Server");

	// Hook GetHostByName function
	PBYTE offset = (PBYTE)GetProcAddress(GetModuleHandleA("ws2_32.dll"),"gethostbyname");
	realgethostbyname = (gethostbyname_t)DetourFunction(offset, (PBYTE)&custom_gethostbyname);

	// Hook packet value setting function
	setPacketValue = (int (__cdecl*)(int a1, int a2, int a3, signed int a4))DetourFunction((PBYTE)0x00E63B30, (PBYTE)cSetPacketValue);
	
	// Hook localhost checking function
	//unknownFuncHook = (int (__cdecl*)(int a1, const char *a2))DetourFunction((PBYTE)0x00445A10, (PBYTE)cUnknownFuncHook);

	// 0xE958A0 - void Fesl::GameManagerHostedGameImpl::AllowPlayerEntry(int ref, bool allow, int reason)
	//AllowPlayerEntry = (void (__stdcall*)(int ref, bool allow, int reason))DetourFunction((PBYTE)0x00E958A0, (PBYTE)cAllowPlayerEntry);

	// 0xE94CA0 - void Fesl::GameManagerHostedGameImpl::AllowPlayerEntryInternal(Fesl::GameManagerPlayerImpl *player, bool allow, int reason)
	//AllowPlayerEntryInternal = (void (__stdcall*)(int *player, bool allow, int reason))DetourFunction((PBYTE)0x00E94CA0, (PBYTE)cAllowPlayerEntryInternal);

	// 0x445A10
	// Patch SSL Certificate Validation
	PatchSSL(true);

	/*const char* lArgs = "InvalidArguments";	
	strcpy((char*)0x1773FEC, lArgs);
	*(BYTE*)0x9A4923 = 0x11;
	*(BYTE*)0x9A4934 = 0x11;
	*(BYTE*)0x9A492C = 0x10;
	*(BYTE*)0x9A494D = 0x10;*/

	// NOP this shit!
	*(BYTE*)0x9681E9 = 0x90;
	*(BYTE*)0x9681EA = 0x90;

	*(BYTE*)0x9AE9CE = 0x90;
	*(BYTE*)0x9AE9CF = 0x90;

	*(BYTE*)0x8EC0AC = 0x90;
	*(BYTE*)0x8EC0AD = 0x90;

	// Always Jump
	*(BYTE*)0x9A4AF5 = 0x85;
	*(BYTE*)0x9A48D5 = 0x85;

	// Lift player limit to 128
	*(BYTE*)0xE9E8F7 = 0x80;
	//*(BYTE*)0xE9E90F = 0x80;
	//*(BYTE*)0xE9E8C0 = 0x80;
	*(BYTE*)0x9A4D63 = 0x80;

	// 128 Max Players for Rush and Conquest
	*(BYTE*)0x5B6CCD = 0x80;

	// Patch login info
	//PatchServerLogin();

	// 0x017083FC "dist\linux\"
}