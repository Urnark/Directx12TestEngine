#include "Window.h"
#include "../../Utils/Clock.h"

std::function<void(HWND, UINT, WPARAM, LPARAM)> dx12ge::Window::_KeyInputFunc;
std::function<void(HWND, UINT, WPARAM, LPARAM)> dx12ge::Window::_mouseInputFunc;

LRESULT dx12ge::Window::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (_KeyInputFunc)
		_KeyInputFunc(hwnd, msg, wParam, lParam);
	if (_mouseInputFunc)
		_mouseInputFunc(hwnd, msg, wParam, lParam);

	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	
	return 0;
}

dx12ge::Window::Window()
{
}

void dx12ge::Window::setScreenSize(E_ScreenSize screenSize)
{
	switch (screenSize)
	{
	case dx12ge::DX12GE_SCREEN_SIZE_nHD:
		_width = 640;
		_height = 360;
		break;
	case dx12ge::DX12GE_SCREEN_SIZE_qHD:
		_width = 960;
		_height = 540;
		break;
	case dx12ge::DX12GE_SCREEN_SIZE_HD:
		_width = 1280;
		_height = 720;
		break;
	case dx12ge::DX12GE_SCREEN_SIZE_HDPlus:
		_width = 1600;
		_height = 900;
		break;
	case dx12ge::DX12GE_SCREEN_SIZE_FHD:
		_width = 1920;
		_height = 1080;
		break;
	case dx12ge::DX12GE_SCREEN_SIZE_QHD:
		_width = 2560;
		_height = 1440;
		break;
	case dx12ge::DX12GE_SCREEN_SIZE_QHDPlus:
		_width = 3200;
		_height = 1800;
		break;
	case dx12ge::DX12GE_SCREEN_SIZE_4K_UHD:
		_width = 3840;
		_height = 2160;
		break;
	case dx12ge::DX12GE_SCREEN_SIZE_4K:
		_width = 5120;
		_height = 2880;
		break;
	case dx12ge::DX12GE_SCREEN_SIZE_8K_UHD:
		_width = 7680;
		_height = 4320;
		break;
	default:
		break;
	}
}

dx12ge::Window::~Window()
{
}

dx12ge::Window & dx12ge::Window::get()
{
	static Window window;
	return window;
}

void dx12ge::Window::init(const WinMainParams & winMainParams, const std::string & title, bool createDebugConsole)
{
	init(winMainParams, title, DX12GE_SCREEN_SIZE_HD, createDebugConsole);
}

void dx12ge::Window::init(const WinMainParams & winMainParams, const std::string & title, E_ScreenSize screenSize, bool createDebugConsole)
{
	init(winMainParams, title, screenSize, -1, -1, createDebugConsole);
}

void dx12ge::Window::init(const WinMainParams & winMainParams, const std::string & title, E_ScreenSize screenSize, int x, int y, bool createDebugConsole)
{
	if (createDebugConsole)
		dx12ge::DebugConsole::get().init(title);
	initWindow(winMainParams, title, screenSize, x, y);
}

void dx12ge::Window::init(const WinMainParams & winMainParams, const std::wstring & title, bool createDebugConsole)
{
	init(winMainParams, title, DX12GE_SCREEN_SIZE_HD, createDebugConsole);
}

void dx12ge::Window::init(const WinMainParams & winMainParams, const std::wstring & title, E_ScreenSize screenSize, bool createDebugConsole)
{
	init(winMainParams, title, screenSize, -1, -1, createDebugConsole);
}

void dx12ge::Window::init(const WinMainParams & winMainParams, const std::wstring & title, E_ScreenSize screenSize, int x, int y, bool createDebugConsole)
{
	if (createDebugConsole)
		dx12ge::DebugConsole::get().init(title);
	initWindow(winMainParams, title, screenSize, x, y);
}

void dx12ge::Window::changePostfixTitle(const std::string & title)
{
	std::string str = _title + " - " + title;
	SetWindowTextA(dx12ge::Window::get().getWindow(), (LPCSTR)str.c_str());

}

void dx12ge::Window::changePostfixTitle(const std::wstring & title)
{
	std::wstring str = _wtitle + L" - " + title;
	SetWindowTextW(dx12ge::Window::get().getWindow(), (LPCWSTR)str.c_str());
}

void dx12ge::Window::showFPS(bool show)
{
	_showFPS = show;
}

void dx12ge::Window::showMsPerFrames(bool show)
{
	_showMsPerFrames = show;
}

void dx12ge::Window::setDeltaTimeStep(double timeStep)
{
	_timeStep = timeStep;
}

int dx12ge::Window::getFPS()
{
	return 0;
}

double dx12ge::Window::getMsPerFrame()
{
	return 0.0;
}

void dx12ge::Window::run()
{
	dx12ge::Clock clock;
	dx12ge::seconds dt = dx12ge::seconds{ _timeStep };

	auto currentTick = clock.now<dx12ge::milliseconds>().count();
	auto endTick = currentTick + 1000 / _framesPerSeconds;

	dx12ge::seconds lastTime = clock.now<dx12ge::seconds>();
	dx12ge::seconds currentTime = clock.now<dx12ge::seconds>();
	dx12ge::seconds accumulator = dx12ge::seconds{ 0 };
	dx12ge::seconds newTime;
	dx12ge::seconds frameTime;
	int nbFrames = 0;
	bool finished = false;
	while (!finished) {
		currentTick = clock.now<dx12ge::milliseconds>().count();
		endTick = currentTick + 1000 / _framesPerSeconds;
		while (currentTick < endTick) {
			if (PeekMessage(&dx12ge::Window::get().getMsg(), /*dx12ge::Window::get().getWindow()*/NULL, 0, 0, PM_REMOVE)) {
				if (WM_QUIT == dx12ge::Window::get().getMsg().message) {
					finished = true;
					break;
				}
				else {
					TranslateMessage(&dx12ge::Window::get().getMsg());
					DispatchMessage(&dx12ge::Window::get().getMsg());
				}
				currentTick = clock.now<dx12ge::milliseconds>().count();
			}
			else {
				break;
			}
		}

		newTime = clock.now<dx12ge::seconds>();
		frameTime = newTime - currentTime;
		currentTime = newTime;

		nbFrames++;

		if ((currentTime - lastTime) >= dx12ge::seconds{ 1 })
		{
			_fps = nbFrames / (int)((currentTime - lastTime).count());
			_msPerFrames = 1000.0 / double(nbFrames);
			if (_showFPS || _showMsPerFrames)
			{
#ifdef UNICODE
				std::wstring str = L"";
				if (_showFPS)
					str = std::to_wstring(_fps) + L" fps";
				if (_showFPS && _showMsPerFrames)
					str += L", ";
				if (_showMsPerFrames)
					str += std::to_wstring(_msPerFrames) + L" ms/frame";
#else
				std::string str = "";
				if (_showFPS)
					str = std::to_string(_fps) + " fps";
				if (_showFPS && _showMsPerFrames)
					str += ", ";
				if (_showMsPerFrames)
					str += std::to_string(_msPerFrames) + " ms/frame";
#endif
				changePostfixTitle(str);
			}
			nbFrames = 0;
			lastTime = currentTime;
		}

		accumulator += frameTime;
		
		while (accumulator >= dt)
		{
			_updateFunc(dt.count());
			accumulator -= dt;
		}

		_renderFunc();
	}
}
