#include "StdAfx.h"
//#include <stdint.h>
#include "Utils.h"
#include "detours.h"
#include <EASTL\fixed_vector.h>
#include <EASTL\string.h>
#include "EASTL.h"

#ifndef BC2_HOOKS_H
#define BC2_HOOKS_H

namespace Nexus
{
	namespace BC2
	{
		class Hooks 
		{
		public:
			static void HookOnCommand();
			static void HookGetPackedString();
			static void HookTagFieldSetNumber();
			static void HookPunkBuster();
			static void HookGameUpdate();
			static void HookGetOptionValue();
			static void HookPunkBusterServer();
			static void HookCreateWindowEx();
		};
	}
}

#endif