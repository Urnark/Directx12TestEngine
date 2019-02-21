#pragma once

#include <Windows.h>
#include <string>
#include <type_traits>
#include <chrono>
#include <iostream>

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
#ifdef DX12GE_DEBUG
#define DX12GE_DEBUG_PFL
#endif

#ifdef DX12GE_DEBUG_PFL
#include <stdio.h>/* defines FILENAME_MAX */
#include <direct.h>/* includes _getcwd */

	static std::string GetDir()
	{
		char cCurrentPath[FILENAME_MAX];

		if (!_getcwd(cCurrentPath, sizeof(cCurrentPath)))
		{
			return "?";
		}

		cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
		std::string str = cCurrentPath;
		return str;
	}

#define path std::string(__FILE__).erase(0, dx12ge::GetDir().length())

#define Print_PFN(...) dx12ge::print("File: [", path, "], Function: [", __FUNCTION__, "], Line: [", __LINE__, "], ", __VA_ARGS__)
#define PrintNL_PFN(...) dx12ge::printNL("File: [", path, "], Function: [", __FUNCTION__, "], Line: [", __LINE__, "], ", __VA_ARGS__)

#define Print(...) dx12ge::print(__VA_ARGS__)
#define PrintNL(...) dx12ge::printNL(__VA_ARGS__)
#else
#define Print_PFN(...)
#define PrintNL_PFN(...)

#define Print(...)
#define PrintNL(...)
#endif

	class ToString
	{
	public:
		ToString() {};
		virtual ~ToString() {};

		virtual std::string toString() const = 0;
	};

	extern bool dx12ge_canUseCOUT;

	namespace impl
	{
		static void outputDebugStringA(const char* str)
		{
			if (dx12ge_canUseCOUT)
				std::cout << str;
			else
				OutputDebugStringA(str);
		}
		static void outputDebugStringW(const wchar_t* str)
		{
			if (dx12ge_canUseCOUT)
				std::wcout << str;
			else
				OutputDebugStringW(str);
		}

		static void printT(const std::string &&str){ outputDebugStringA(str.c_str()); }
		static void printT(const std::string &str) { outputDebugStringA(str.c_str()); }
		static void printT(std::string &&str) { outputDebugStringA(str.c_str()); }
		static void printT(std::string &str) { outputDebugStringA(str.c_str()); }
		static void printT(const std::wstring &&str) { outputDebugStringW(str.c_str()); }
		static void printT(const std::wstring &str) { outputDebugStringW(str.c_str()); }
		static void printT(std::wstring &&str) { outputDebugStringW(str.c_str()); }
		static void printT(std::wstring &str) { outputDebugStringW(str.c_str()); }

		static void printT(const dx12ge::ToString &&str)
		{
			outputDebugStringA(str.toString().c_str());
		}
		static void printT(const dx12ge::ToString &str)
		{
			outputDebugStringA(str.toString().c_str());
		}

		template <typename Rep, typename Period>
		static void printT(std::chrono::duration<Rep, Period> time)
		{
			std::string s = std::to_string(time.count());
			if (typeid(time) == typeid(dx12ge::seconds)) s += "s";
			if (typeid(time) == typeid(dx12ge::minutes)) s += "min";
			if (typeid(time) == typeid(dx12ge::hours)) s += "h";
			if (typeid(time) == typeid(dx12ge::days)) s += "days";
			if (typeid(time) == typeid(dx12ge::milliseconds)) s += "ms";
			if (typeid(time) == typeid(dx12ge::microseconds)) s += "us";
			if (typeid(time) == typeid(dx12ge::nanoseconds)) s += "ns";
			outputDebugStringA(s.c_str());
		}

		static void printT(const char* &&str) { outputDebugStringA(str); }
		static void printT(const char* &str) { outputDebugStringA(str); }
		static void printT(char* &&str) { outputDebugStringA(str); }
		static void printT(char* &str) { outputDebugStringA(str); }
		static void printT(const wchar_t* &str) { outputDebugStringW(str); }
		static void printT(const wchar_t* &&str) { outputDebugStringW(str); }
		static void printT(wchar_t* &&str) { outputDebugStringW(str); }
		static void printT(wchar_t* &str) { outputDebugStringW(str); }

		template<typename T>
		static void printT(T&& t)
		{
			std::string s = std::to_string(t);
			outputDebugStringA(s.c_str());
		}
	};

	template<typename ...Args>
	inline static void print(Args &&... params)
	{
		int dummy[] = { 0, ((void)impl::printT(std::forward<Args>(params)), 0) ... };
	}
	template<typename ...Args>
	inline static void printNL(Args &&... params)
	{
		int dummy[] = { 0, ((void)impl::printT(std::forward<Args>(params)), 0) ... };
		impl::outputDebugStringA("\n");
	}
};