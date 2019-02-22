#include "Logging.h"

namespace dx12ge {
	bool dx12ge_canUseCOUT = false;

	void Logging::outputDebugStringA(dx12ge::Logging::E_LogType logType, const char * str)
	{
		if (dx12ge_canUseCOUT)
			std::cout << str;
		else
			OutputDebugStringA(str);
	}
	void Logging::outputDebugStringW(dx12ge::Logging::E_LogType logType, const wchar_t * str)
	{
		if (dx12ge_canUseCOUT)
			std::wcout << str;
		else
			OutputDebugStringW(str);
	}

	std::string Logging::getDir()
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
};