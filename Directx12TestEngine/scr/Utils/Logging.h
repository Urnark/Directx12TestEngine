#pragma once

#include <Windows.h>
#include <string>
#include <type_traits>
#include <chrono>
#include <iostream>

#include <stdio.h>/* defines FILENAME_MAX */
#include <direct.h>/* includes _getcwd */

namespace dx12ge
{
	//---------------------------------------------------------- Show message box ----------------------------------------------------
	static void mgsError(const std::string& mgs)
	{
		MessageBoxA(NULL, mgs.c_str(), "Error!", MB_ICONERROR | MB_OK);
	}

	static void mgsWarning(const std::string& mgs)
	{
		MessageBoxA(NULL, mgs.c_str(), "Warning!", MB_ICONWARNING | MB_OK);
	}

	static void mgsInformation(const std::string& mgs)
	{
		MessageBoxA(NULL, mgs.c_str(), "Information!", MB_ICONINFORMATION | MB_OK);
	}

	//---------------------------------------------------------- Print message in debug output window ----------------------------------------------------
#define path std::string(__FILE__).erase(0, dx12ge::Logging::getDir().length())

#define Log(logType, ...) dx12ge::Logging::print(##logType, __VA_ARGS__)
#define LogInfo(...) dx12ge::Logging::print(dx12ge::Logging::E_LogType::INFO, "\n  ", __VA_ARGS__, "\n")
#define LogWarning(...) dx12ge::Logging::print(dx12ge::Logging::E_LogType::WARNING, "\n  ", __VA_ARGS__, "\n")
#define LogError(...) dx12ge::Logging::print(dx12ge::Logging::E_LogType::ERR, "\n  File: [", path, "]\n  Function: [", __FUNCTION__, "]\n  Line: [", __LINE__, "]\n  Description: ", __VA_ARGS__, "\n\n")

	class ToString
	{
	public:
		ToString() {};
		virtual ~ToString() {};

		virtual std::string toString() const = 0;
	};

	extern bool dx12ge_canUseCOUT;

	class Logging
	{
	public:
		enum E_LogType {
			INFO,
			WARNING,
			ERR
		};

	private:
		static void outputDebugStringA(dx12ge::Logging::E_LogType logType, const char* str);
		static void outputDebugStringW(dx12ge::Logging::E_LogType logType, const wchar_t* str);

		static void printT(dx12ge::Logging::E_LogType logType, const std::string &&str) { outputDebugStringA(logType, str.c_str()); };
		static void printT(dx12ge::Logging::E_LogType logType, const std::string &str) { outputDebugStringA(logType, str.c_str()); };
		static void printT(dx12ge::Logging::E_LogType logType, std::string &&str) { outputDebugStringA(logType, str.c_str()); };
		static void printT(dx12ge::Logging::E_LogType logType, std::string &str) { outputDebugStringA(logType, str.c_str()); };
		static void printT(dx12ge::Logging::E_LogType logType, const std::wstring &&str) { outputDebugStringW(logType, str.c_str()); };
		static void printT(dx12ge::Logging::E_LogType logType, const std::wstring &str) { outputDebugStringW(logType, str.c_str()); };
		static void printT(dx12ge::Logging::E_LogType logType, std::wstring &&str) { outputDebugStringW(logType, str.c_str()); };
		static void printT(dx12ge::Logging::E_LogType logType, std::wstring &str) { outputDebugStringW(logType, str.c_str()); };

		static void printT(dx12ge::Logging::E_LogType logType, const dx12ge::ToString &&str) { outputDebugStringA(logType, str.toString().c_str()); };
		static void printT(dx12ge::Logging::E_LogType logType, const dx12ge::ToString &str) { outputDebugStringA(logType, str.toString().c_str()); };

		static void printT(dx12ge::Logging::E_LogType logType, const char* &&str) { outputDebugStringA(logType, str); };
		static void printT(dx12ge::Logging::E_LogType logType, const char* &str) { outputDebugStringA(logType, str); };
		static void printT(dx12ge::Logging::E_LogType logType, char* &&str) { outputDebugStringA(logType, str); };
		static void printT(dx12ge::Logging::E_LogType logType, char* &str) { outputDebugStringA(logType, str); };
		static void printT(dx12ge::Logging::E_LogType logType, const wchar_t* &str) { outputDebugStringW(logType, str); };
		static void printT(dx12ge::Logging::E_LogType logType, const wchar_t* &&str) { outputDebugStringW(logType, str); };
		static void printT(dx12ge::Logging::E_LogType logType, wchar_t* &&str) { outputDebugStringW(logType, str); };
		static void printT(dx12ge::Logging::E_LogType logType, wchar_t* &str) { outputDebugStringW(logType, str); };

		template <typename Rep, typename Period>
		static void printT(dx12ge::Logging::E_LogType logType, std::chrono::duration<Rep, Period> time) 
		{
#ifdef UNICODE
			std::wstring s = std::to_wstring(time.count());
			if (typeid(time) == typeid(dx12ge::seconds)) s += L"s";
			if (typeid(time) == typeid(dx12ge::minutes)) s += L"min";
			if (typeid(time) == typeid(dx12ge::hours)) s += L"h";
			if (typeid(time) == typeid(dx12ge::days)) s += L"days";
			if (typeid(time) == typeid(dx12ge::milliseconds)) s += L"ms";
			if (typeid(time) == typeid(dx12ge::microseconds)) s += L"us";
			if (typeid(time) == typeid(dx12ge::nanoseconds)) s += L"ns";
			outputDebugStringW(logType, s.c_str());
#else
			std::string s = std::to_string(time.count());
			if (typeid(time) == typeid(dx12ge::seconds)) s += "s";
			if (typeid(time) == typeid(dx12ge::minutes)) s += "min";
			if (typeid(time) == typeid(dx12ge::hours)) s += "h";
			if (typeid(time) == typeid(dx12ge::days)) s += "days";
			if (typeid(time) == typeid(dx12ge::milliseconds)) s += "ms";
			if (typeid(time) == typeid(dx12ge::microseconds)) s += "us";
			if (typeid(time) == typeid(dx12ge::nanoseconds)) s += "ns";
			outputDebugStringA(logType, s.c_str());
#endif
		};

		template<typename T>
		static void printT(dx12ge::Logging::E_LogType logType, T&& t)
		{
#ifdef UNICODE
			std::wstring s = std::to_wstring(t);
			outputDebugStringW(logType, s.c_str());
#else
			std::string s = std::to_string(t);
			outputDebugStringA(logType, s.c_str());
#endif
		};

	public:
		static std::string getDir();

		template<typename ...Args>
		inline static void print(dx12ge::Logging::E_LogType logType, Args &&... params)
		{
			std::string type;
			switch (logType)
			{
			case dx12ge::Logging::INFO:
				type = "\nINFO: ";
				break;
			case dx12ge::Logging::WARNING:
				type = "\nWARNING: ";
				break;
			case dx12ge::Logging::ERR:
				type = "\nERROR: ";
				break;
			default:
				break;
			}
			dx12ge::Logging::printT(logType, type);
			int dummy[] = { 0, ((void)dx12ge::Logging::printT(logType, std::forward<Args>(params)), 0) ... };
		};
	};
};