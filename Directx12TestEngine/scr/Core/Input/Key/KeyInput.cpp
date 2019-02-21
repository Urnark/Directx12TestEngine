#include "KeyInput.h"

dx12ge::KeyInput::KeyInput()
{
}

void dx12ge::KeyInput::createKeyMap()
{
	for (dx12ge::E_KeyCode keyCode = DX12GE_KEY_CODE_START; keyCode < DX12GE_KEY_CODE_END; ((int&)keyCode)++)
	{
		_keys[keyCode] = DX12GE_KEY_STATE_IS_UP;
	}
}

dx12ge::KeyInput::~KeyInput()
{
	createKeyMap();
}

dx12ge::KeyInput& dx12ge::KeyInput::get()
{
	static dx12ge::KeyInput keyInput;
	return keyInput;
}

void dx12ge::KeyInput::processInputs(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	dx12ge::E_KeyCode keyCode = (dx12ge::E_KeyCode)(wParam);
	dx12ge::E_KeyCode keyCodeUp = dx12ge::E_KeyCode::DX12GE_KEY_CODE_START;
	bool publishEvent = false;
	_pressed = false;
	_enteredText = false;
	switch (msg)
	{
	case WM_KEYDOWN:
		if (_keys[keyCode] == DX12GE_KEY_STATE_DOWN)
			_keys[keyCode] = DX12GE_KEY_STATE_IS_DOWN;
		if (_keys[keyCode] != DX12GE_KEY_STATE_IS_DOWN)
			_keys[keyCode] = DX12GE_KEY_STATE_DOWN;
		publishEvent = true;
		_pressed = true;
		break;

	case WM_KEYUP:
		keyCodeUp = keyCode;
		_keys[keyCodeUp] = DX12GE_KEY_STATE_UP;
		publishEvent = true;
		break;

	case WM_CHAR:
		// Check bit for the repeat
		//if (lParam & 0x40000000)
#ifdef DX12GE_UNICODE
		if ((wchar_t)wParam != L'\b')
		{
			if (_recordTextInput)
				_text += (wchar_t)wParam;
			else
				_text = (wchar_t)wParam;
		}
#else
		if ((char)wParam != '\b')
		{
			if (_recordTextInput)
				_text += (char)wParam;
			else
				_text = (char)wParam;
		}
#endif
		_enteredText = true;
		publishEvent = true;
		break;

	default:
		break;
	}

	if (publishEvent)
		dx12ge::EventSystem::publish(dx12ge::KeyInput::get());
	if (keyCodeUp != dx12ge::E_KeyCode::DX12GE_KEY_CODE_START)
		_keys[keyCodeUp] = DX12GE_KEY_STATE_IS_UP;
}

dx12ge::E_KeyState dx12ge::KeyInput::getKeyState(dx12ge::E_KeyCode keyCode)
{
	return _keys[keyCode];
}

bool dx12ge::KeyInput::isKeyClicked(dx12ge::E_KeyCode keyCode)
{
	return _keys[keyCode] == dx12ge::E_KeyState::DX12GE_KEY_STATE_DOWN;
}

bool dx12ge::KeyInput::isKeyPressed(dx12ge::E_KeyCode keyCode)
{
	return _keys[keyCode] == dx12ge::E_KeyState::DX12GE_KEY_STATE_IS_DOWN || _keys[keyCode] == dx12ge::E_KeyState::DX12GE_KEY_STATE_DOWN;
}

bool dx12ge::KeyInput::isKeyReleased(dx12ge::E_KeyCode keyCode)
{
	return _keys[keyCode] == dx12ge::E_KeyState::DX12GE_KEY_STATE_UP;
}

bool dx12ge::KeyInput::isAnyKeyPressed()
{
	return _pressed;
}

bool dx12ge::KeyInput::hasEnteredText()
{
	return _enteredText;
}

void dx12ge::KeyInput::startRecordTextInput()
{
	_recordTextInput = true;
	_text.clear();
}

#ifdef DX12GE_UNICODE
std::wstring
#else
std::string
#endif
& dx12ge::KeyInput::getText()
{
	return _text;
}

#ifdef DX12GE_UNICODE
std::wstring
#else
std::string
#endif
dx12ge::KeyInput::stopRecordTextInput()
{
	_recordTextInput = false;
#ifdef DX12GE_UNICODE
	std::wstring text = _text;
#else
	std::string text = _text;
#endif
	_text.clear();
	return text;
}
