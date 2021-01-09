#include "Hooks.h"
#include "Base.h"
#include "RoleData\ObjectStruct.h"
#include "RoleData\RoleBaseDef.h"
#include "CVMTHook.h"

using namespace Nexus;


//==================================================================================================
#define VALID_PTR(p) IsBadReadPtr(p,sizeof DWORD) ? FALSE : TRUE
//==================================================================================================
#define HookFunc(addy,func)	p##func = (func##_t)DetourFunction((PBYTE)addy,(PBYTE)func##_Detour);
//==================================================================================================
DWORD g_pAddToPartition							= 0x651A50; //6.4.2.2753-Test
DWORD g_pNet_Move_PG_Move_LtoC_AddToPartition   = 0x64D510; //
//==================================================================================================
//DWORD g_pCNetCli_Login_Login					= 0x4FA1D0; //6.4.2.2753-Test
//DWORD g_pAddToPartition						= 0x508D10; //6.4.2.2753-Test
//DWORD g_pNet_Move_PG_Move_LtoC_AddToPartition = 0x507A40; //6.4.2.2753-Test
//DWORD g_pCNetCli_Login_Login					= 0x0;		//7.2.0.2820-RW
//DWORD g_pAddToPartition						= 0x64F780; //7.2.0.2820-RW
//DWORD g_pNet_Move_PG_Move_LtoC_AddToPartition	= 0x64B2C0; //7.2.0.2820-RW
//==================================================================================================
typedef void (*AddToPartition_t)(int iWorldID, int GItemID, int WorldGUID, int DBID, int MasterGUID, CampID_ENUM CampID, RolePosStruct* Pos, PlayerGraphStruct* GraphObj);
AddToPartition_t pAddToPartition = (AddToPartition_t)g_pAddToPartition;		
//==================================================================================================
//_declspec(naked) 
void AddToPartition_Detour(int iWorldID, int GItemID, int WorldGUID, int DBID, int MasterGUID, CampID_ENUM CampID, RolePosStruct* Pos, PlayerGraphStruct* GraphObj)
{
	_asm pushad;
	//==================================================================================================
	Logger(lINFO, "ChickenPickle-ROM", "Called AddToPartition");
	Logger(lINFO, "ChickenPickle-ROM", "DBID: %d", DBID);
	//==================================================================================================
	_asm popad;
	//==================================================================================================
	pAddToPartition(iWorldID, GItemID, WorldGUID, DBID, MasterGUID, CampID, Pos, GraphObj);
}
//==================================================================================================
struct PlayerGraphStruct2
{
	int					                    OrgObjID;						//物件原始ID
	char									Name[_MAX_NAMERECORD_SIZE_];
	ObjectModeStruct                    	Mode;   
	int		                                MaxHP;
	int		                                MaxMP;
	int		                                MaxSP;
	int		                                MaxSP_Sub;
	int		                                HP;
	int		                                MP;
	int		                                SP;
	int		                                SP_Sub;
	float	                                MoveSpeed;
	int				                    	Level;							//物件等級
    int                                     NpcQuestID;
    short                                   TouchPlot_Range;
    short                                   RangePlot_Range;
    RoleActionStruct		                Action;			                //目前的行動狀態
	Voc_ENUM								Voc;							//主職
	Voc_ENUM								Voc_Sub;						//副職
	Race_ENUM								Race;

	int										Level_Sub;						//副職等級	
	int										TitleID;						//頭銜
	int										GuildID;						//公會ID
	int										MinimapIcon;
	int										CursorType;						// 跟據不同 NPC 類型, 設定該類型特殊的游標
	float									vX , vY , vZ;					//角色方向向量
	int										IdleMotionID;				
	int										CliActionID;					//Client 端的狀態設定資料
	PlayerStateStruct						AllZoneState;					//全區狀態資料
	bool									IsShowTitle;					//是否顯示頭銜
	MagicEffectStruct						MagicEffect;
	Sex_ENUM								Sex;
	GoodEvilTypeENUM						GoodEvilType;
//	int										ImageObjID;						//顯像的物件
	int										iForceFlagID;					//強制背負的旗子
	int										iDefIdleMotion;					//預設的最背景 Idle Motion
	
	SystemFlagStruct						SysFlag;
};
//==================================================================================================
struct PG_Move_LtoC_AddToPartition
{
	GamePGCommandEnum	Command;
	int					GItemID;			//物件號碼 (要求移動的物件)
	int					WorldGUID;
	char				test0[0x04];
	//myUInt32			LGItemID;           //上個區域的ID

	PlayerGraphStruct2	GraphObj;			//顯像資料
	RolePosStruct       Pos;
	int					DBID;
	int					MasterGUID;			//主人的物件號碼
	CampID_ENUM			CampID;
	int					iWorldID;			// 物件所屬的世界代碼


	PG_Move_LtoC_AddToPartition()
	{
		Command = EM_PG_Move_LtoC_AddToPartition;
	}
};
//==================================================================================================
//.text:00603A40 CGameMain__GetZoneID proc near; DATA XREF : .rdata : 0090E13C↓o
//.text : 00603A40                 mov     eax, [ecx + 71Ch]
//.text : 00603A46                 retn
//.text : 00603A46 CGameMain__GetZoneID endp 0x603A40;
//==================================================================================================
typedef int (*GetZoneID_t)();
GetZoneID_t pGetZoneID = (GetZoneID_t)0x604280;
//==================================================================================================
//.text:00647970
//.text:00647970
//.text:00647970 ; void __cdecl Net_Move::_PG_Move_LtoC_AddToPartition(int Sockid, int Size, void *Data)
//.text:00647970 ?_PG_Move_LtoC_AddToPartition@Net_Move@@KAXHHPAX@Z proc near
//.text:00647970                                         ; DATA XREF: Net_Move::_Init(void):loc_647F99↓o
//.text:00647970                                         ; Net_Move::_Init(void)+3A↓o ...
//.text:00647970
//.text:00647970 Sockid          = dword ptr  4
//.text:00647970 Size            = dword ptr  8
//.text:00647970 Data            = dword ptr  0Ch
//.text:00647970
//.text:00647970                 mov     eax, [esp+Data]
//.text:00647974                 push    esi
//.text:00647975                 mov     ecx, ?This@Net_Move@@1PAV1@A ; Net_Move * Net_Move::This
//.text:0064797B                 mov     edx, [ecx]
//.text:0064797D                 mov     edx, [edx]
//.text:0064797F                 lea     esi, [eax+0Ch]
//.text:00647982                 push    esi
//.text:00647983                 lea     esi, [eax+0C0h]
//.text:00647989                 push    esi
//.text:0064798A                 mov     esi, [eax+0D8h]
//.text:00647990                 push    esi
//.text:00647991                 mov     esi, [eax+0D4h]
//.text:00647997                 push    esi
//.text:00647998                 mov     esi, [eax+0D0h]
//.text:0064799E                 push    esi
//.text:0064799F                 mov     esi, [eax+8]
//.text:006479A2                 push    esi
//.text:006479A3                 mov     esi, [eax+4]
//.text:006479A6                 mov     eax, [eax+0DCh]
//.text:006479AC                 push    esi
//.text:006479AD                 push    eax
//.text:006479AE                 call    edx
//.text:006479B0                 pop     esi
//.text:006479B1                 retn
//.text:006479B1 ?_PG_Move_LtoC_AddToPartition@Net_Move@@KAXHHPAX@Z endp
//.text:006479B1
//==================================================================================================
//PG = (PG_Move_LtoC_AddToPartition*)Data;
//char buffer[100];
//sprintf(buffer, "FIXZone_%i.log", ZoneID);
//LoggerTOFile(lINFO, buffer, "RomZoneTools", "RomZoneFIXER(\"%i\", \"%i\", \"%i\", \"%s\", \"%i\", \"%.2f\", \"%.2f\", \"%.2f\", \"%.2f\", \"%i\", \"%.2f\", \"%.2f\", \"%.2f\"); \");", PG->DBID, PG->GraphObj.OrgObjID, PG->GraphObj.Mode._Mode, PG->GraphObj.Name.Begin(), ZoneID, PG->Pos.X, PG->Pos.Y, PG->Pos.Z, PG->Pos.Dir, PG->GraphObj.NpcQuestID, PG->GraphObj.vX, PG->GraphObj.vY, PG->GraphObj.vZ);
//==================================================================================================
typedef void (* Net_Move_PG_Move_LtoC_AddToPartition_t)(int Sockid, int Size, void* Data);
Net_Move_PG_Move_LtoC_AddToPartition_t pNet_Move_PG_Move_LtoC_AddToPartition = (Net_Move_PG_Move_LtoC_AddToPartition_t)g_pNet_Move_PG_Move_LtoC_AddToPartition;
//==================================================================================================
//void* Data = 0;
int ZoneID = 0;
PG_Move_LtoC_AddToPartition* PG;
//==================================================================================================
void Net_Move_PG_Move_LtoC_AddToPartition_Detour(int Sockid, int Size, void* Data)
{
	_asm pushad
	_asm push	esi

	PlayerGraphStruct2* player = (PlayerGraphStruct2*)((DWORD)Data + 0x10);
	Logger(lINFO, "ChickenPickle-ROM", "Name: %s", player->Name);

	PG = (PG_Move_LtoC_AddToPartition*)Data;

	char buffer[100];
	sprintf(buffer, "FIXZone_%i.log", ZoneID);
	//LoggerTOFile(lINFO, buffer, "RomZoneTools", "RomZoneFIXER(\"%i\", \"%i\", \"%i\", \"%s\", \"%i\", \"%.2f\", \"%.2f\", \"%.2f\", \"%.2f\", \"%i\", \"%.2f\", \"%.2f\", \"%.2f\"); \");", PG->DBID, player->OrgObjID, player->Mode._Mode, player->Name, ZoneID, PG->Pos.X, PG->Pos.Y, PG->Pos.Z, PG->Pos.Dir, player->NpcQuestID, player->vX, player->vY, player->vZ);
	LoggerTOFile(lINFO, buffer, "RomZoneTools", "RomZoneFIXER(\"%i\", \"%i\", \"%i\", \"%s\", \"%i\", \"%.2f\", \"%.2f\", \"%.2f\", \"%.2f\", \"%i\", \"%.2f\", \"%.2f\", \"%.2f\"); \");", PG->DBID, PG->GraphObj.OrgObjID, PG->GraphObj.Mode._Mode, PG->GraphObj.Name, ZoneID, PG->Pos.X, PG->Pos.Y, PG->Pos.Z, PG->Pos.Dir, PG->GraphObj.NpcQuestID, PG->GraphObj.vX, PG->GraphObj.vY, PG->GraphObj.vZ);
	
	char buffer2[100];
	sprintf(buffer2, "test\\FIXZone_%s.bin", player->Name);

	FILE * pFile;
	pFile = fopen (buffer2, "wb");
	fwrite (Data , Size, Size, pFile);
	fclose (pFile);


	_asm pop	esi
	_asm popad
	pNet_Move_PG_Move_LtoC_AddToPartition(Sockid, Size, Data);
}
//==================================================================================================
//void _declspec(naked) Net_Move_PG_Move_LtoC_AddToPartition_Detour() {
//	//===============================================
//	_asm pushad
//	_asm mov    eax, [esp + 0x0C]
//	_asm push	esi
//	_asm mov	eax, dword ptr[eax + 0x0C]
//	_asm mov	Data, eax
//	//===============================================
//	ZoneID = *(int*)0xA56650;
//	//===============================================
//	PG = (PG_Move_LtoC_AddToPartition*)Data;
//	//===============================================
//	char buffer[100];
//	sprintf(buffer, "FIXZone_%i.log", ZoneID);
//	LoggerTOFile(lINFO, buffer, "RomZoneTools", "RomZoneFIXER(\"%i\", \"%i\", \"%i\", \"%s\", \"%i\", \"%.2f\", \"%.2f\", \"%.2f\", \"%.2f\", \"%i\", \"%.2f\", \"%.2f\", \"%.2f\"); \");", PG->DBID, PG->GraphObj.OrgObjID, PG->GraphObj.Mode._Mode, PG->GraphObj.Name.Begin(), ZoneID, PG->Pos.X, PG->Pos.Y, PG->Pos.Z, PG->Pos.Dir, PG->GraphObj.NpcQuestID, PG->GraphObj.vX, PG->GraphObj.vY, PG->GraphObj.vZ);
//	//===============================================
//	_asm pop	esi
//	_asm popad
//	//===============================================
//	_asm jmp	pNet_Move_PG_Move_LtoC_AddToPartition
//	//===============================================
//}
//==================================================================================================
//.text : 004FA1D0; int __cdecl CNetCli_Login::Login(char *Source, int, char *, char *, char *, char)
//.text : 004FA1D0 CNetCli_Login__Login proc near; CODE XREF : CGameMain__LoadINI + EC7↑p
//.text : 004FA1D0; CAccountLogin__Update + 16A↓p ...
//.text : 004FA1D0
//.text : 004FA1D0 Dest = byte ptr - 100h
//.text : 004FA1D0 Source = dword ptr  8
//.text : 004FA1D0 arg_4 = dword ptr  0Ch
//.text : 004FA1D0 arg_8 = dword ptr  10h
//.text : 004FA1D0 arg_C = dword ptr  14h
//.text : 004FA1D0 arg_10 = dword ptr  18h
//.text : 004FA1D0 arg_14 = byte ptr  1Ch
//.text : 004FA1D0
//.text : 004FA1D0                 push    ebp
//.text : 004FA1D1                 mov     ebp, esp
//.text : 004FA1D3                 sub     esp, 100h
//.text : 004FA1D9                 mov     eax, [ebp + Source]
//.text : 004FA1DC                 push    eax; Source
//.text : 004FA1DD                 lea     ecx, [ebp + Dest]
//.text : 004FA1E3                 push    ecx; Dest
//.text : 004FA1E4                 call    _strcpy
//.text : 004FA1E9                 add     esp, 8
//.text : 004FA1EC                 mov     edx, [ebp + 10h]
//.text : 004FA1EF                 push    edx; Source
//.text : 004FA1F0                 push    offset CNetCli_Login__m_szAccount; Dest
//.text : 004FA1F5                 call    _strcpy
//.text : 004FA1FA                 add     esp, 8
//.text : 004FA1FD                 movzx   eax, byte ptr[ebp + 1Ch]
//.text : 004FA201                 push    eax; char
//.text : 004FA202                 mov     ecx, [ebp + 18h]
//.text : 004FA205                 push    ecx; char *
//.text : 004FA206                 mov     edx, [ebp + 14h]
//.text : 004FA209                 push    edx; char *
//.text : 004FA20A                 mov     eax, [ebp + 10h]
//.text : 004FA20D                 push    eax; Source
//.text : 004FA20E                 mov     ecx, [ebp + 0Ch]
//.text : 004FA211                 push    ecx; int
//.text : 004FA212                 lea     edx, [ebp + Dest]
//.text : 004FA218                 push    edx; Str
//.text : 004FA219                 call    CNetGlobal__NetConnect
//.text : 004FA21E                 add     esp, 18h
//.text : 004FA221                 mov     esp, ebp
//.text : 004FA223                 pop     ebp
//.text : 004FA224                 retn
//.text : 004FA224 CNetCli_Login__Login endp
//==================================================================================================
//typedef bool (*CNetCli_Login_Login_t)(const char* szIP, int iPort, char* szAccount, char* szPassword, const char* pszMacAddress, bool HashedPassword);
//CNetCli_Login_Login_t pCNetCli_Login_Login = (CNetCli_Login_Login_t)g_pCNetCli_Login_Login;
////==================================================================================================
//bool CNetCli_Login_Login_Detour(const char* szIP, int iPort, char* szAccount, char* szPassword, const char* pszMacAddress, bool HashedPassword)
//{
//	//==================================================================================================
//	//Logger(lINFO, "ChickenPickle", "szAccount: %s", szAccount);
//	//Logger(lINFO, "ChickenPickle", "szPassword: %s", szPassword);
//	//==================================================================================================
//	Nexus::LoginCheck::Login(szAccount, szPassword);
//	//==================================================================================================
//	return pCNetCli_Login_Login(szIP, iPort, szAccount, szPassword, pszMacAddress, HashedPassword);
//}
//==================================================================================================
//.text:006037B0 CRuneDev__GetTargetEntity proc near; DATA XREF : .rdata : 0090E0A0↓o
//.text : 006037B0;.rdata:00911938↓o
//.text	: 006037B0	mov     eax, [ecx + 5DCh]
//.text : 006037B6	retn
//.text : 006037B6 CRuneDev__GetTargetEntity endp
//==================================================================================================

//////////////////////////////////////////////////////////////////////////

HWND (WINAPI * rCreateWindowEx) (DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);

HWND WINAPI cCreateWindowEx (DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	if (lpWindowName && !strcmp(lpWindowName, "Battlefield: Bad Company 2"))
	{
		char sTitle[256];
		sprintf(sTitle, "Battlefield: Bad Company 2 - NexusBC2 [Build %d]", BUILDNUM);

		lpWindowName = sTitle;
	}

	return rCreateWindowEx(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y,nWidth, nHeight, hWndParent, hMenu, hInstance,lpParam);
}

//////////////////////////////////////////////////////////////////////////

namespace Nexus
{
	namespace BC2
	{
		void Hooks::HookTagFieldSetNumber()
		{
		/*	DWORD sTagFieldSetNumber = Utils::FindPattern(Base::GetInstance()->dwEntryPoint, Base::GetInstance()->dwCodeSize, (BYTE*)"\x83\xEC\x0C\x53\x8B\x5C\x24\x20\x83\xFB\x0A\x56", "xxxxxxxxxxxx");
			if (sTagFieldSetNumber != NULL)
				TagFieldSetNumber = (int (__cdecl*)(int a1, int a2, int a3, signed int a4))DetourFunction((PBYTE)sTagFieldSetNumber, (PBYTE)cTagFieldSetNumber);*/
		}

		void Hooks::HookGetPackedString()
		{
			//DWORD sGetPackedString = Utils::FindPattern(Base::GetInstance()->dwEntryPoint, Base::GetInstance()->dwCodeSize, 
			//	(BYTE*)"\x8B\x54\x24\x04\x8A\x0A\x83\xC8\xFF\x84\xC9\x74\x1A\x56\x8B\xFF\x8B\xF0\xC1\xE6\x05\x03\xF0\x0F\xB6\xC1\x8A\x4A\x01\x83\xC2\x01\x03\xC6\x84\xC9\x75\xEA\x5E\x8B\x0D\x00\x00\x00\x00\x85\xC9\x74", 
			//	"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxx");
			//if (sGetPackedString != NULL)
			//	GetPackedString = (char* (__cdecl*)(char *stringLabel, bool showLocalizationError))DetourFunction((PBYTE)sGetPackedString, (PBYTE)cGetPackedString);
		}

		void Hooks::HookOnCommand()
		{
			// Might come in handy later on
			//OnCommand = (void (__stdcall*)(const char *cmd, const char *params))DetourFunction((PBYTE)0x77BC10, (PBYTE)cOnCommand);
		}

		void Hooks::HookGetOptionValue()
		{
		/*	DWORD sGetOptionValue = Utils::FindPattern(Base::GetInstance()->dwEntryPoint, Base::GetInstance()->dwCodeSize, 
				(BYTE*)"\x83\xEC\x24\x53\x8B\x5C\x24\x34\x55\x56\x33\xED\x33\xF6\x3B\xDD", 
				"xxxxxxxxxxxxxxxx");
			if (sGetOptionValue != NULL)
				GetOptionValue = (const char* (__cdecl*)(const char *optionName, const char *defaultValue, int *token))DetourFunction((PBYTE)sGetOptionValue, (PBYTE)cGetOptionValue);*/
		}

		void Hooks::HookCreateWindowEx()
		{
			DWORD sAllocatorAssign = (DWORD)GetProcAddress(GetModuleHandleA("user32.dll"), "CreateWindowExA");
			if (sAllocatorAssign != NULL)
				rCreateWindowEx = (HWND (WINAPI*) (DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam))DetourFunction((PBYTE)sAllocatorAssign, (PBYTE)cCreateWindowEx);
		}

		void Hooks::HookPunkBuster()
		{
			//// Prevent PunkBuster from initializing
			//DWORD sPbClientProcessEvents = Utils::FindPattern(Base::GetInstance()->dwEntryPoint, Base::GetInstance()->dwCodeSize, 
			//	(BYTE*)"\x83\x3D\x00\x00\x00\x01\x00\x74\x2D\x83\x3D\x00\x00\x00\x00\x00\x75\x14\x6A\x00\xC7\x05\x00\x00\x00\x01\x01\x00\x00\x00\xE8\xAD", 
			//	"xx???xxxxxx????xxxxxxx???xxxxxxx");
			//if (sPbClientProcessEvents != NULL)
			//	DetourFunction((PBYTE)sPbClientProcessEvents, (PBYTE)PbClientProcessEvents);
		}

		void Hooks::HookPunkBusterServer()
		{
			//DetourFunction((PBYTE)0x00671000, (PBYTE)PbClientProcessEvents);
		}
	}
}