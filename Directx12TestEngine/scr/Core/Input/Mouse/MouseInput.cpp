#include "MouseInput.h"

dx12ge::MouseInput::MouseInput()
{
	createMouseMap();
}

void dx12ge::MouseInput::createMouseMap()
{
	for (dx12ge::E_MouseCode mouseCode = DX12GE_MOUSE_CODE_START; mouseCode < DX12GE_MOUSE_CODE_END; ((int&)mouseCode)++)
	{
		_mouse[mouseCode] = DX12GE_MOUSE_STATE_IS_UP;
	}
}

void dx12ge::MouseInput::setMouseDownSates(dx12ge::E_MouseCode mouseCode)
{
	if (_mouse[mouseCode] == DX12GE_MOUSE_STATE_DOWN)
		_mouse[mouseCode] = DX12GE_MOUSE_STATE_IS_DOWN;
	if (_mouse[mouseCode] != DX12GE_MOUSE_STATE_IS_DOWN)
		_mouse[mouseCode] = DX12GE_MOUSE_STATE_DOWN;
}

dx12ge::MouseInput::~MouseInput()
{
}

dx12ge::MouseInput & dx12ge::MouseInput::get()
{
	static dx12ge::MouseInput mouseInput;
	return mouseInput;
}

void dx12ge::MouseInput::processInputs(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	dx12ge::E_MouseCode mouseCode = (dx12ge::E_MouseCode)(wParam);
	dx12ge::E_MouseCode mouseCodeUp = dx12ge::E_MouseCode::DX12GE_MOUSE_CODE_START;
	_mouse[dx12ge::E_MouseCode::DX12GE_MOUSE_CODE_MOVE] = dx12ge::E_MouseState::DX12GE_MOUSE_STATE_IDLE;
	_mouse[dx12ge::E_MouseCode::DX12GE_MOUSE_CODE_WHEEL] = dx12ge::E_MouseState::DX12GE_MOUSE_STATE_IDLE;
	bool publishEvent = false;
	switch (msg)
	{
		// Down
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		setMouseDownSates(mouseCode);
		publishEvent = true;
		break;
	case WM_XBUTTONDOWN:
		mouseCode = (dx12ge::E_MouseCode)GET_XBUTTON_WPARAM(wParam);
		if (mouseCode == XBUTTON1)
			mouseCode = dx12ge::E_MouseCode::DX12GE_MOUSE_CODE_XBUTTON1;
		if (mouseCode == XBUTTON2)
			mouseCode = dx12ge::E_MouseCode::DX12GE_MOUSE_CODE_XBUTTON2;
		setMouseDownSates(mouseCode);
		publishEvent = true;
		break;

		// Up
	case WM_LBUTTONUP:
		mouseCodeUp = dx12ge::E_MouseCode::DX12GE_MOUSE_CODE_LBUTTON;
		_mouse[mouseCodeUp] = DX12GE_MOUSE_STATE_UP;
		publishEvent = true;
		break;
	case WM_RBUTTONUP:
		mouseCodeUp = dx12ge::E_MouseCode::DX12GE_MOUSE_CODE_RBUTTON;
		_mouse[mouseCodeUp] = DX12GE_MOUSE_STATE_UP;
		publishEvent = true;
		break;
	case WM_MBUTTONUP:
		mouseCodeUp = dx12ge::E_MouseCode::DX12GE_MOUSE_CODE_MBUTTON;
		_mouse[mouseCodeUp] = DX12GE_MOUSE_STATE_UP;
		publishEvent = true;
		break;
	case WM_XBUTTONUP:
		mouseCode = (dx12ge::E_MouseCode)GET_XBUTTON_WPARAM(wParam);
		if (mouseCode == XBUTTON1)
			mouseCode = dx12ge::E_MouseCode::DX12GE_MOUSE_CODE_XBUTTON1;
		if (mouseCode == XBUTTON2)
			mouseCode = dx12ge::E_MouseCode::DX12GE_MOUSE_CODE_XBUTTON2;
		mouseCodeUp = mouseCode;
		_mouse[mouseCodeUp] = DX12GE_MOUSE_STATE_UP;
		publishEvent = true;
		break;

		// Double Click
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
		_mouse[mouseCode] = DX12GE_MOUSE_STATE_DOUBLE_CLICK;
		publishEvent = true;
		break;
	case WM_XBUTTONDBLCLK:
		mouseCode = (dx12ge::E_MouseCode)GET_XBUTTON_WPARAM(wParam);
		if (mouseCode == XBUTTON1)
			mouseCode = dx12ge::E_MouseCode::DX12GE_MOUSE_CODE_XBUTTON1;
		if (mouseCode == XBUTTON2)
			mouseCode = dx12ge::E_MouseCode::DX12GE_MOUSE_CODE_XBUTTON2;
		_mouse[mouseCode] = DX12GE_MOUSE_STATE_DOUBLE_CLICK;
		publishEvent = true;
		break;

		// Mouse H wheel
	case WM_MOUSEWHEEL:
		mouseWheel += (GET_WHEEL_DELTA_WPARAM(wParam) / MOUSE_WHEEL_STEP);
		_mouse[dx12ge::E_MouseCode::DX12GE_MOUSE_CODE_WHEEL] = dx12ge::E_MouseState::DX12GE_MOUSE_STATE_MOVE;
		publishEvent = true;
		break;

		// Mouse move
	case WM_MOUSEMOVE:
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hwnd, &pt);
		mouseX = pt.x;
		mouseY = pt.y;
		_mouse[dx12ge::E_MouseCode::DX12GE_MOUSE_CODE_MOVE] = dx12ge::E_MouseState::DX12GE_MOUSE_STATE_MOVE;
		publishEvent = true;
		break;
	default:
		break;
	}

	if (publishEvent)
		dx12ge::EventSystem::publish(dx12ge::MouseInput::get());

	if (mouseCodeUp != dx12ge::E_MouseCode::DX12GE_MOUSE_CODE_START)
		_mouse[mouseCodeUp] = dx12ge::E_MouseState::DX12GE_MOUSE_STATE_IS_UP;
}

dx12ge::E_MouseState dx12ge::MouseInput::getMouseState(dx12ge::E_MouseCode mouseCode)
{
	return _mouse[mouseCode];
}

int dx12ge::MouseInput::getMouseX()
{
	return mouseX;
}

int dx12ge::MouseInput::getMouseY()
{
	return mouseY;
}

int dx12ge::MouseInput::getMouseWheel()
{
	return mouseWheel;
}

bool dx12ge::MouseInput::isButtonClicked(dx12ge::E_MouseCode mouseCode)
{
	return _mouse[mouseCode] == dx12ge::E_MouseState::DX12GE_MOUSE_STATE_DOWN || _mouse[mouseCode] == dx12ge::E_MouseState::DX12GE_MOUSE_STATE_DOUBLE_CLICK;
}

bool dx12ge::MouseInput::isButtonPressed(dx12ge::E_MouseCode mouseCode)
{
	return _mouse[mouseCode] == dx12ge::E_MouseState::DX12GE_MOUSE_STATE_IS_DOWN || _mouse[mouseCode] == dx12ge::E_MouseState::DX12GE_MOUSE_STATE_DOWN || 
		_mouse[mouseCode] == dx12ge::E_MouseState::DX12GE_MOUSE_STATE_DOUBLE_CLICK;
}

bool dx12ge::MouseInput::isButtonReleased(dx12ge::E_MouseCode mouseCode)
{
	return _mouse[mouseCode] == dx12ge::E_MouseState::DX12GE_MOUSE_STATE_UP;
}

bool dx12ge::MouseInput::isButtonDoubleClicked(dx12ge::E_MouseCode mouseCode)
{
	return _mouse[mouseCode] == E_MouseState::DX12GE_MOUSE_STATE_DOUBLE_CLICK;
}

bool dx12ge::MouseInput::mouseWheelMoved()
{
	return _mouse[E_MouseCode::DX12GE_MOUSE_CODE_WHEEL] == E_MouseState::DX12GE_MOUSE_STATE_MOVE;
}

bool dx12ge::MouseInput::mouseMoved()
{
	return _mouse[E_MouseCode::DX12GE_MOUSE_CODE_MOVE] == E_MouseState::DX12GE_MOUSE_STATE_MOVE;
}
