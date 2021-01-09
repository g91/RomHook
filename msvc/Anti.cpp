#include "Anti.h"
#include "detours.h"

#pragma unmanaged

int	mD3D9Proxy = 0;

#define DEREF( name )*(UINT_PTR *)(name)
#define DEREF_64( name )*(DWORD64 *)(name)
#define DEREF_32( name )*(DWORD *)(name)
#define DEREF_16( name )*(WORD *)(name)
#define DEREF_8( name )*(BYTE *)(name)

// special function which jumps inside a DLL function
// skipping the first 5 bytes, which can have a possible hook
// Before using it, check if the standard code  is there....
void __declspec(naked) pCallDllFunction()
{
	__asm
	{						// mov edi,edi     placeholder for MS patch
		push ebp			// original code which we skip, total 5 bytes
		mov  ebp, esp
		// ---- above is standard code, now we skip 5 bytes and jump to it
		add  eax, 5			// skip possible hook
		push eax
		ret					// jump to the function
	}
}


extern BYTE *HLmem;
extern DWORD firstSteamID;

void CheckForProxy()
{
	//PROT_BEGIN
		// Check for d3d9.dll in the game directory
		// TODO: Protect these strings
		//Logger(lDEBUG, "BC2::Anti", "Checking for d3d9 proxy.");
		FILE *fp = fopen((Utils::GetCurrentDir() + "\\d3d9.dll").c_str(), "r");
		if (fp) 
		{
			fclose(fp);
			mD3D9Proxy = 1;
			//Logger(lDEBUG, "BC2::Anti", "Found a d3d9 proxy DLL. Terminating.");
			TerminateProcess(GetCurrentProcess(), 0);
		}
	//PROT_END
	PROT_IMMCLEAR(CheckForProxy)
}

//////////////////////////////////////////////////////////////////////////

// This doesn't work
bool (__stdcall* UpdateGame)(void *params, bool *isIngame, bool lowLatencyUpdate);

bool __stdcall cUpdateGame(void *params, bool *isIngame, bool lowLatencyUpdate)
{
	void* th; 
	__asm mov [th], ecx    

	//if (isIngame)
	//	Logger(lDEBUG, "Client::updateGame", "Is Ingame");

	__asm mov ecx, [th]
	return UpdateGame(params, isIngame, lowLatencyUpdate);
}

//////////////////////////////////////////////////////////////////////////

namespace Nexus
{
	namespace BC2
	{
		void Anti::InitAC()
		{
			// 0x0056E3C0 dice::Client::updateGame (possibly for every frame)
			//UpdateGame = (bool (__stdcall*)(void *params, bool *isIngame, bool lowLatencyUpdate))DetourFunction((PBYTE)0x0056E3C0, (PBYTE)cUpdateGame);
			// For now we only check for a d3d9 proxy
			CheckForProxy();
		}
	}
}
