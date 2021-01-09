#include "DiskSerial.h"
#include "StdAfx.h"
#include "Utils.h"

#ifndef ANTI_H
#define ANTI_H

namespace Nexus
{
	namespace BC2
	{
		class Anti
		{
		public:
			static void InitAC();
		};
	}
}

void     pCallDllFunction();
extern   int				CI_CGd3d9;
void     CheckForProxy();

#endif