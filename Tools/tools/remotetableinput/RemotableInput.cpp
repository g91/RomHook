#include "RemotableInput.h"
#include "ControllerClient/ControllerClient.h"

#pragma managed(push, off)

// ************************************************************************************************************************************************************
CRemotableInput g_remotableInput;

CRemotableInput::CRemotableInput()
:	m_console_UseSTDIO(TRUE),
	m_console_InputHandle(INVALID_HANDLE_VALUE),
	m_console_OutputHandle(INVALID_HANDLE_VALUE)
{
}

CRemotableInput::~CRemotableInput()
{
}

bool CRemotableInput::Initialize()
{
	// Get standard console handles
	m_console_InputHandle = GetStdHandle(STD_INPUT_HANDLE);
	m_console_OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Attempt to use input handle as a pipe
	DWORD bytesAvailable;
	if(PeekNamedPipe(m_console_InputHandle, NULL, NULL, NULL, &bytesAvailable, NULL) == FALSE)
	{
		// Use failed, treat input as coming from the standard console
		m_console_UseSTDIO = true;
	}
	else
	{
		// Use succeeded, treat input as coming from a pipe
		m_console_UseSTDIO = false;
	}

	return true;
}

void CRemotableInput::OutputStartupMessage()
{
	PrintToController(false, "\nSERVER READY IDSTR = {6EC9D721-D946-4906-AB79-5AF7B35241CB}\n");
	fflush(NULL);
}

bool CRemotableInput::InputAvailable()
{
	if(m_console_UseSTDIO)
	{
		return _kbhit() != 0;
	}
	else
	{
		DWORD bytesAvailable;
		if(PeekNamedPipe(m_console_InputHandle, NULL, NULL, NULL, &bytesAvailable, NULL) == FALSE)
		{
			DWORD error = GetLastError();

			if(error == ERROR_INVALID_HANDLE)
			{
				return false;
			}
		}

		if(bytesAvailable > 0)
		{
			return true;
		}

		return false;
	}

	return false;
}

int CRemotableInput::GetChar()
{
	if(m_console_UseSTDIO)
	{
		return _getche();
	}
	else
	{
		char buffer[1];
		DWORD bytesRead = 0;
		if(ReadFile(m_console_InputHandle, buffer, 1, &bytesRead, NULL))
		{
			if(bytesRead > 0)
			{
				return buffer[0];
			}
		}
	}

	return 0;
}

// ************************************************************************************************************************************************************

#pragma managed(pop)
