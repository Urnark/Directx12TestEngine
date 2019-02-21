#pragma once

#include <Windows.h>
#include <unordered_map>

#include "../VirtualInputCodes.h"
#include "../../Events/EventSystem.h"

// define UNICODE to use wstring

namespace dx12ge
{
	enum E_KeyState {
		DX12GE_KEY_STATE_START = 0,

		DX12GE_KEY_STATE_IS_UP,
		DX12GE_KEY_STATE_DOWN,
		DX12GE_KEY_STATE_IS_DOWN,
		DX12GE_KEY_STATE_UP,

		DX12GE_KEY_STATE_END
	};

	class KeyInput : public dx12ge::Event
	{
	private:
		std::unordered_map<dx12ge::E_KeyCode, E_KeyState> _keys;
#ifdef UNICODE
		std::wstring _text;
#else
		std::string _text;
#endif
		bool _recordTextInput = false;
		bool _enteredText = false;
		bool _pressed = false;

	private:
		KeyInput();
		void createKeyMap();

	public:
		KeyInput(const dx12ge::KeyInput& keyInput) = delete;
		~KeyInput();

		static dx12ge::KeyInput& get();
		void processInputs(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		E_KeyState getKeyState(dx12ge::E_KeyCode keyCode);

		bool isKeyClicked(dx12ge::E_KeyCode keyCode);
		bool isKeyPressed(dx12ge::E_KeyCode keyCode);
		bool isKeyReleased(dx12ge::E_KeyCode keyCode);
		bool isAnyKeyPressed();
		
		// Text input
		bool hasEnteredText();
		void startRecordTextInput();
#ifdef UNICODE
		std::wstring& getText();
		std::wstring stopRecordTextInput();
#else
		std::string& getText();
		std::string stopRecordTextInput();
#endif
	};
}