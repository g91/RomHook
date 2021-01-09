#include "StdAfx.h"
#include <fcntl.h>

#ifndef ONLINECHECK_H
#define ONLINECHECK_H

namespace Nexus
{
	class OnlineCheck
	{
	public:
		static void CheckStatus();
	private:
		static DWORD WINAPI QuickConnectTTL(LPVOID sAddressPTR);
		static bool QuickConnect(char* pHostname, int pPort);
	};
}

#endif