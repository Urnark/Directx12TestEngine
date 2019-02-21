#pragma once

#include "../Input/Key/KeyInput.h"
#include "../Input/Mouse/MouseInput.h"
#include "../Events/EventSystem.h"
#include "../../Utils/Clock.h"

using namespace dx12ge;

class Game
{
private:
	bool testingTextInput = false;

private:
	void processKeyInput(KeyInput* e);
	void processMouseInput(MouseInput* e);

public:
	Game();
	~Game();

	void update(double dt);
	void render();
};