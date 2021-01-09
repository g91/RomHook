#pragma once

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#include <stdio.h>
#include <conio.h>
#include <windows.h>

#pragma managed(push, off)

// ************************************************************************************************************************************************************

class CRemotableInput
{
protected:
	bool								m_console_UseSTDIO;
	HANDLE								m_console_InputHandle;
	HANDLE								m_console_OutputHandle;

public:
										CRemotableInput();
										~CRemotableInput();

	bool								Initialize();
	void								OutputStartupMessage();

	bool								InputAvailable();
	int									GetChar();
};

extern CRemotableInput g_remotableInput;
// ************************************************************************************************************************************************************

#pragma managed(pop)
