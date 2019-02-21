#include "DebugConsole.h"

dx12ge::DebugConsole::DebugConsole()
{	
}

dx12ge::DebugConsole::~DebugConsole()
{
	if (streamOut)
		fclose(streamOut);
	if (streamErr)
		fclose(streamErr);

	if (consoleHandleOut != INVALID_HANDLE_VALUE)
		CloseHandle(consoleHandleOut);
	if (consoleHandleError != INVALID_HANDLE_VALUE)
		CloseHandle(consoleHandleError);
}

dx12ge::DebugConsole & dx12ge::DebugConsole::get()
{
	static dx12ge::DebugConsole dConsole;
	return dConsole;
}
