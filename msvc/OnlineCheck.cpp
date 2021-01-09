// ==========================================================
// Emulator Nexus - Battlefield Bad Company 2 Hook
//
// Description:
//		Checks if the Master Server is currently reachable
//
// Author: NoFaTe
// ==========================================================

#include "OnlineCheck.h"

namespace Nexus
{
	bool OnlineCheck::QuickConnect(char* pHostname, int pPort)
	{
		WSADATA wData;
		WSAStartup(0x0101, &wData);

		struct sockaddr_in sAddress;

		LPHOSTENT sIP = gethostbyname(pHostname);

		sAddress.sin_family = AF_INET;
		sAddress.sin_port = htons(pPort);
		sAddress.sin_addr = *((LPIN_ADDR)*sIP->h_addr_list);

		HANDLE tConnThread;
		DWORD threadID;
		DWORD tExitCode = 0;

		tConnThread = CreateThread(NULL, 0, &QuickConnectTTL, &sAddress, 0, &threadID);

		SYSTEMTIME now;
		GetSystemTime(&now);

		int finishTime = (now.wDay * 24 * 60) + (now.wHour * 60) + (now.wSecond) + 2;
		int nowTime = 0;

		while(nowTime < finishTime)
		{
			GetSystemTime(&now);
			nowTime = (now.wDay * 24 * 60) + (now.wHour * 60) + (now.wSecond);
			GetExitCodeThread(tConnThread, &tExitCode);
			if(tExitCode != STILL_ACTIVE)
				break;
		}

		GetExitCodeThread(tConnThread, &tExitCode);

		if(tExitCode == STILL_ACTIVE)
		{
			TerminateThread(tConnThread, 0);
			tExitCode = 0;
		}

		CloseHandle(tConnThread);

		WSACleanup();

		if(tExitCode == 1)
			return true;
		else
			return false;
	}

	DWORD WINAPI OnlineCheck::QuickConnectTTL(LPVOID sAddressPTR)
	{
		//copy struct info from PTR
		struct sockaddr_in sAddress;
		memcpy(&sAddress, sAddressPTR, sizeof(struct sockaddr_in));

		//connect to remote host
		int concode;
		SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
		concode = connect(s, (struct sockaddr *)&sAddress, sizeof(sAddress));

		if(concode == SOCKET_ERROR)
		{
			ExitThread(0);
			return 0;
		}
		else
		{
			closesocket(s);
			ExitThread(1);
			return 1;
		}
	}

	void OnlineCheck::CheckStatus()
	{
		if (!QuickConnect("bfbc2.emulatornexus.com", 18390))
		{
			MessageBoxA(NULL, 
				"The NexusBC2 Master Server seems to be unreachable.\nThis means that the server is down, you don't have an active internet connection or your firewall is blocking the connection.\n\nPlease try again at a later time.", 
				"Master Server Unavailable", 
				MB_OK | MB_ICONINFORMATION);
		}
	}
}