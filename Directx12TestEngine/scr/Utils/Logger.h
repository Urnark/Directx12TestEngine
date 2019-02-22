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
#define path std::string(__FILE__).erase(0, dx12ge::Logger::getDir().length())

#define Log(logType, ...) dx12ge::Logger::print(##logType, __VA_ARGS__)
#define LogInfo(...) dx12ge::Logger::print(dx12ge::Logger::E_LogType::INFO, dx12ge::Clock::date_and_systime_as_string().c_str(), " | INFO | ", path, ":", __FUNCTION__, ":", __LINE__, " | ", __VA_ARGS__, "\n")
#define LogWarning(...) dx12ge::Logger::print(dx12ge::Logger::E_LogType::WARNING, dx12ge::Clock::date_and_systime_as_string().c_str(), " | WARNING | ", path, ":", __FUNCTION__, ":", __LINE__, " | ", __VA_ARGS__, "\n")
#define LogError(...) dx12ge::Logger::print(dx12ge::Logger::E_LogType::ERR, dx12ge::Clock::date_and_systime_as_string().c_str(), " | ERROR | ", path, ":", __FUNCTION__, ":", __LINE__, " | ", __VA_ARGS__, "\n")
#define LogDebug(...) dx12ge::Logger::print(dx12ge::Logger::E_LogType::DEBUG, dx12ge::Clock::date_and_systime_as_string().c_str(), " | DEBUG | ", path, ":", __FUNCTION__, ":", __LINE__, " | ", __VA_ARGS__, "\n")

	class ToString
	{
	public:
		ToString() {};
		virtual ~ToString() {};

		virtual std::string toString() const = 0;
	};

	extern bool dx12ge_canUseCOUT;

	class Logger
	{
	public:
		enum E_LogType {
			DEBUG,
			INFO,
			WARNING,
			ERR
		};

	private:
		static void outputDebugStringA(dx12ge::Logger::E_LogType logType, const char* str);
		static void outputDebugStringW(dx12ge::Logger::E_LogType logType, const wchar_t* str);

		static void printT(dx12ge::Logger::E_LogType logType, const std::string &&str) { outputDebugStringA(logType, str.c_str()); };
		static void printT(dx12ge::Logger::E_LogType logType, const std::string &str) { outputDebugStringA(logType, str.c_str()); };
		static void printT(dx12ge::Logger::E_LogType logType, std::string &&str) { outputDebugStringA(logType, str.c_str()); };
		static void printT(dx12ge::Logger::E_LogType logType, std::string &str) { outputDebugStringA(logType, str.c_str()); };
		static void printT(dx12ge::Logger::E_LogType logType, const std::wstring &&str) { outputDebugStringW(logType, str.c_str()); };
		static void printT(dx12ge::Logger::E_LogType logType, const std::wstring &str) { outputDebugStringW(logType, str.c_str()); };
		static void printT(dx12ge::Logger::E_LogType logType, std::wstring &&str) { outputDebugStringW(logType, str.c_str()); };
		static void printT(dx12ge::Logger::E_LogType logType, std::wstring &str) { outputDebugStringW(logType, str.c_str()); };

		static void printT(dx12ge::Logger::E_LogType logType, const dx12ge::ToString &&str) { outputDebugStringA(logType, str.toString().c_str()); };
		static void printT(dx12ge::Logger::E_LogType logType, const dx12ge::ToString &str) { outputDebugStringA(logType, str.toString().c_str()); };

		static void printT(dx12ge::Logger::E_LogType logType, const char* &&str) { outputDebugStringA(logType, str); };
		static void printT(dx12ge::Logger::E_LogType logType, const char* &str) { outputDebugStringA(logType, str); };
		static void printT(dx12ge::Logger::E_LogType logType, char* &&str) { outputDebugStringA(logType, str); };
		static void printT(dx12ge::Logger::E_LogType logType, char* &str) { outputDebugStringA(logType, str); };
		static void printT(dx12ge::Logger::E_LogType logType, const wchar_t* &str) { outputDebugStringW(logType, str); };
		static void printT(dx12ge::Logger::E_LogType logType, const wchar_t* &&str) { outputDebugStringW(logType, str); };
		static void printT(dx12ge::Logger::E_LogType logType, wchar_t* &&str) { outputDebugStringW(logType, str); };
		static void printT(dx12ge::Logger::E_LogType logType, wchar_t* &str) { outputDebugStringW(logType, str); };

		template <typename Rep, typename Period>
		static void printT(dx12ge::Logger::E_LogType logType, std::chrono::duration<Rep, Period> time) 
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
		static void printT(dx12ge::Logger::E_LogType logType, T&& t)
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
		inline static void print(dx12ge::Logger::E_LogType logType, Args &&... params)
		{
			int dummy[] = { 0, ((void)dx12ge::Logger::printT(logType, std::forward<Args>(params)), 0) ... };
		};
	};
};