#pragma once

#include <Windows.h>
#include <unordered_map>
#include <windowsx.h>

#include "../VirtualInputCodes.h"
#include "../../Events/EventSystem.h"

namespace dx12ge
{
	using namespace dx12ge;

	enum E_MouseState
	{
		DX12GE_MOUSE_STATE_START = 0,

		DX12GE_MOUSE_STATE_IS_UP,
		DX12GE_MOUSE_STATE_UP,
		DX12GE_MOUSE_STATE_IS_DOWN,
		DX12GE_MOUSE_STATE_DOWN,
		DX12GE_MOUSE_STATE_DOUBLE_CLICK,
		DX12GE_MOUSE_STATE_MOVE,
		DX12GE_MOUSE_STATE_IDLE,

		DX12GE_MOUSE_STATE_END
	};

	class MouseInput : public Event
	{
	private:
		static const int MOUSE_WHEEL_STEP = 120;
		std::unordered_map<dx12ge::E_MouseCode, E_MouseState> _mouse;
		int mouseX;
		int mouseY;
		int mouseWheel;

	private:
		MouseInput();
		void createMouseMap();
		void setMouseDownSates(dx12ge::E_MouseCode mouseCode);

	public:
		MouseInput(const MouseInput& mouseInput) = delete;
		~MouseInput();

		static MouseInput& get();
		void processInputs(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		E_MouseState getMouseState(dx12ge::E_MouseCode mouseCode);
		int getMouseX();
		int getMouseY();
		int getMouseWheel();

		bool isButtonClicked(dx12ge::E_MouseCode mouseCode);
		bool isButtonPressed(dx12ge::E_MouseCode mouseCode);
		bool isButtonReleased(dx12ge::E_MouseCode mouseCode);
		bool isButtonDoubleClicked(dx12ge::E_MouseCode mouseCode);
		bool mouseWheelMoved();
		bool mouseMoved();
	};
}