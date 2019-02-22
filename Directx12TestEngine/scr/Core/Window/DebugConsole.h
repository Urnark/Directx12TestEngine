#pragma once

#include <Windows.h>
#include <stdio.h>
#include <string>

#include "../../Utils/Logger.h"

namespace dx12ge
{
	class DebugConsole
	{
	private:
		FILE * streamOut = nullptr;
		FILE *streamErr = nullptr;
		HANDLE consoleHandleOut = nullptr;
		HANDLE consoleHandleError = nullptr;

	private:
		DebugConsole();

	public:
		DebugConsole(const DebugConsole&) = delete;
		~DebugConsole();

		static DebugConsole& get();

		template<class T>
		bool init(const T & title);
	};

	template<class T>
	inline bool DebugConsole::init(const T & title)
	{
		dx12ge_canUseCOUT = true;

		// Create a new console
		AllocConsole();

		// Redirect unbuffered STDOUT to the console
		consoleHandleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (consoleHandleOut != INVALID_HANDLE_VALUE)
		{
			freopen_s(&streamOut, "CONOUT$", "w", stdout);
			setvbuf(stdout, NULL, _IONBF, 0);
		}
		else
		{
			return false;
		}
		// Redirect unbuffered STDERR to the console
		consoleHandleError = GetStdHandle(STD_ERROR_HANDLE);
		if (consoleHandleError != INVALID_HANDLE_VALUE)
		{
			freopen_s(&streamErr, "CONOUT$", "w", stderr);
			setvbuf(stderr, NULL, _IONBF, 0);
		}
		else
		{
			return false;
		}

		// Remove disable CLOSE button on the console
		HWND hwnd = GetConsoleWindow();
		HMENU hmenu = GetSystemMenu(hwnd, FALSE);
		EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);

		// Set title
#ifdef UNICODE
		wchar_t consoleTitle[256];
		wsprintfW(consoleTitle, (LPCWSTR)title.c_str());
		SetConsoleTitleW((LPCTWSTR)consoleTitle);
#else
		char consoleTitle[256];
		wsprintfA(consoleTitle, (LPCSTR)title.c_str());
		SetConsoleTitleA((LPCTSTR)consoleTitle);
#endif

		// Disable input for the console
		DWORD dwMode = 0x0;
		GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &dwMode);
		// Remove ENABLE_PROCESSED_INPUT flag
		dwMode &= ~ENABLE_PROCESSED_INPUT;
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), dwMode);

		return true;
	}
}