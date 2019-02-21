#pragma once

#include <Windows.h>
#include <string>
#include <functional>

#include "../../resource.h"
#include "../../Utils/dx12geHelper.h"
#include "DebugConsole.h"

// define UNICODE to use wstring in init function

namespace dx12ge
{
	struct WinMainParams
	{
		HINSTANCE& hInstance; 
		HINSTANCE& hPrevInstance;
		LPSTR& lpCmdLine; 
		int& nCmdShow;
	};

	enum E_ScreenSize // All screen sizes has ratio 16:9
	{
		DX12GE_SCREEN_SIZE_nHD,		// 640 x 360 pixels
		DX12GE_SCREEN_SIZE_qHD,		// 960 x 540 pixels
		DX12GE_SCREEN_SIZE_HD,		// 1280 x 720 pixels
		DX12GE_SCREEN_SIZE_HDPlus,	// 1600 x 900 pixels
		DX12GE_SCREEN_SIZE_FHD,		// 1920 x 1080 pixels
		DX12GE_SCREEN_SIZE_QHD,		// 2560 x 1440 pixels
		DX12GE_SCREEN_SIZE_QHDPlus,	// 3200 x 1800 pixels
		DX12GE_SCREEN_SIZE_4K_UHD,	// 3840 x 2160 pixels
		DX12GE_SCREEN_SIZE_4K,		// 5120 x 2880 pixels
		DX12GE_SCREEN_SIZE_8K_UHD	// 7680 x 4320 pixels
	};

	class Window
	{
	private:
		std::string _title;
		std::wstring _wtitle;
		unsigned int _width;
		unsigned int _height;

		HWND _hwnd;
		MSG _msg;

		// Inputs
		static std::function<void(HWND, UINT, WPARAM, LPARAM)> _KeyInputFunc;
		static std::function<void(HWND, UINT, WPARAM, LPARAM)> _mouseInputFunc;

		// For running game-loop
		double _timeStep;
		std::function<void(double)> _updateFunc;
		std::function<void()> _renderFunc;
		int _fps;
		double _msPerFrames;
		int _framesPerSeconds = 60;
		bool _showFPS = false;
		bool _showMsPerFrames = false;

	private:
		static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		Window();
		
		void setScreenSize(E_ScreenSize screenSize);

		template<typename T>
		void setStringTitle(const T& title){};
		template<>
		void setStringTitle<std::string>(const std::string& title)
		{
			_title = title;
		};
		template<>
		void setStringTitle<std::wstring>(const std::wstring& title)
		{
			_wtitle = title;
		};
		
		template<class T>
		void initWindow(const WinMainParams& winMainParams, const T& title, E_ScreenSize screenSize, int x, int y);

	public:
		Window(const Window& window) = delete;
		~Window();

		static Window& get();
		void init(const WinMainParams& winMainParams, const std::string& title, bool createDebugConsole = false);
		void init(const WinMainParams& winMainParams, const std::string& title, E_ScreenSize screenSize, bool createDebugConsole = false);
		void init(const WinMainParams& winMainParams, const std::string& title, E_ScreenSize screenSize, int x, int y, bool createDebugConsole = false);
		void init(const WinMainParams& winMainParams, const std::wstring& title, bool createDebugConsole = false);
		void init(const WinMainParams& winMainParams, const std::wstring& title, E_ScreenSize screenSize, bool createDebugConsole = false);
		void init(const WinMainParams& winMainParams, const std::wstring& title, E_ScreenSize screenSize, int x, int y, bool createDebugConsole = false);

		HWND& getWindow() { return _hwnd; };
		int mainReturn() { return _msg.wParam; };
		MSG& getMsg() { return _msg; };
		void changePostfixTitle(const std::string & title);
		void changePostfixTitle(const std::wstring & title);

		// Inputs
		template<class T>
		void setKeyInputFunc(T * instance, void(T::*inputFunc)(HWND, UINT, WPARAM, LPARAM))
		{
			_KeyInputFunc = dx12ge::bindFunciton(inputFunc, instance);
		};
		template<class T>
		void setMouseInputFunc(T * instance, void(T::*inputFunc)(HWND, UINT, WPARAM, LPARAM))
		{
			_mouseInputFunc = dx12ge::bindFunciton(inputFunc, instance);
		};

		// For running game loop
		void showFPS(bool show);
		void showMsPerFrames(bool show);
		void setDeltaTimeStep(double timeStep);
		int getFPS();
		double getMsPerFrame();
		void run();

		template<class T>
		void setUpdateFunc(T * instance, void(T::*update)(double))
		{
			_updateFunc = dx12ge::bindFunciton(update, instance);
		};
		template<class T>
		void setRenderFunc(T * instance, void(T::*render)())
		{
			_renderFunc = dx12ge::bindFunciton(render, instance);
		};
	};

	template<class T>
	inline void Window::initWindow(const WinMainParams & winMainParams, const T & title, E_ScreenSize screenSize, int x, int y)
	{
		setStringTitle(title);
		setScreenSize(screenSize);

#ifdef UNICODE
		WNDCLASSEXW wc;
#else
		WNDCLASSEXA wc;
#endif

		//Step 1: Registering the Window Class
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_DBLCLKS;
		wc.lpfnWndProc = wndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = winMainParams.hInstance;
		wc.hIcon = LoadIcon(winMainParams.hInstance, MAKEINTRESOURCE(IDI_ICON2));//LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
		wc.lpszMenuName = NULL;
#ifdef UNICODE
		wc.lpszClassName = L"dx12ge::Window";
#else
		wc.lpszClassName = "dx12ge::Window";
#endif
		wc.hIconSm = LoadIcon(winMainParams.hInstance, MAKEINTRESOURCE(IDI_ICON1));

#ifdef UNICODE
		if (!RegisterClassExW(&wc))
		{
			MessageBoxW(NULL, L"Window Registration Failed!", L"Error!",
				MB_ICONEXCLAMATION | MB_OK);
			exit(0);
		}
#else
		if (!RegisterClassExA(&wc))
		{
			MessageBoxA(NULL, "Window Registration Failed!", "Error!",
				MB_ICONEXCLAMATION | MB_OK);
			exit(0);
		}
#endif

		RECT rect;
		rect.left = x;
		rect.top = y;
		if (x == -1 || y == -1)
		{
			GetClientRect(GetDesktopWindow(), &rect);
			rect.left = (rect.right / 2) - (_width / 2);
			rect.top = (rect.bottom / 2) - (_height / 2);
		}

		// Step 2: Creating the Window
#ifdef UNICODE
		_hwnd = CreateWindowExW(
			WS_EX_CLIENTEDGE,
			L"dx12ge::Window",
			(LPCWSTR)title.c_str(),
			WS_OVERLAPPEDWINDOW,
			rect.left, rect.top, _width, _height,
			NULL, NULL, winMainParams.hInstance, NULL);

		if (_hwnd == NULL)
		{
			MessageBoxW(NULL, L"Window Creation Failed!", L"Error!",
				MB_ICONEXCLAMATION | MB_OK);
			exit(0);
		}
#else
		_hwnd = CreateWindowExA(
			WS_EX_CLIENTEDGE,
			"dx12ge::Window",
			(LPCSTR)title.c_str(),
			WS_OVERLAPPEDWINDOW,
			rect.left, rect.top, _width, _height,
			NULL, NULL, winMainParams.hInstance, NULL);

		if (_hwnd == NULL)
		{
			MessageBoxA(NULL, "Window Creation Failed!", "Error!",
				MB_ICONEXCLAMATION | MB_OK);
			exit(0);
		}
#endif

		ShowWindow(_hwnd, winMainParams.nCmdShow);
		UpdateWindow(_hwnd);
	}
}