#include "Game.h"

using namespace dx12ge;

void Game::processKeyInput(KeyInput * e)
{
	if (e->hasEnteredText())
	{
		if (e->isKeyPressed(E_KeyCode::DX12GE_KEY_BACKSPACE))
		{
			e->getText() = e->getText().substr(0, e->getText().length() - 1);
		}
		LogInfo(e->getText());
	}

	if (e->isKeyReleased(E_KeyCode::DX12GE_KEY_SPACEBAR))
	{
		LogInfo("Clicked on SPACEBAR");
	}

	if (e->isKeyPressed(E_KeyCode::DX12GE_KEY_SHIFT) && e->isKeyClicked(E_KeyCode::DX12GE_KEY_X))
	{
		LogInfo("Clicked on shift and X");
	}
}

void Game::processMouseInput(MouseInput * e)
{
	if (e->isButtonDoubleClicked(E_MouseCode::DX12GE_MOUSE_CODE_LBUTTON))
	{
		LogInfo("Mouse double clicked L");
	}
	if (e->isButtonClicked(E_MouseCode::DX12GE_MOUSE_CODE_RBUTTON))
	{
		if (!testingTextInput)
		{
			KeyInput::get().startRecordTextInput();
			testingTextInput = true;
		}
		else
		{
			LogInfo(KeyInput::get().stopRecordTextInput());
			testingTextInput = false;
		}
	}
	if (e->mouseWheelMoved())
	{
		LogInfo("Mouse wheel: ", e->getMouseWheel());
	}
}

Game::Game()
{
	EventSystem::subscribe(this, &Game::processKeyInput);
	EventSystem::subscribe(this, &Game::processMouseInput);
}

Game::~Game()
{
	EventSystem::unsubscribe(this, &Game::processKeyInput);
	EventSystem::unsubscribe(this, &Game::processMouseInput);
}

void Game::update(double dt)
{
}

void Game::render()
{
}
