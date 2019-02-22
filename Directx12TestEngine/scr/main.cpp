#define EIGEN_MPL2_ONLY

#include "Core\Window\Window.h"
#include "Core\Input\Key\KeyInput.h"
#include "Core\Input\Mouse\MouseInput.h"

#include <Eigen/Dense>
#include "Utils/Logger.h"

#include "Core\TestGame\Game.h"

using namespace Eigen;
using namespace dx12ge;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WinMainParams winMainParams = { hInstance, hPrevInstance, lpCmdLine, nCmdShow };
	Window& window = Window::get();
	window.init(winMainParams, "Test window", true);

	// Set key input class
	window.setKeyInputFunc(&KeyInput::get(), &KeyInput::processInputs);
	// Set Mouse input class
	window.setMouseInputFunc(&MouseInput::get(), &MouseInput::processInputs);

	LogError("This is an error!");

	printf("HELLO!!! I AM THE CONSOLE!\n");

	std::cout << "hello world" << std::endl;
	
	Game game;
	window.setUpdateFunc(&game, &Game::update);
	window.setRenderFunc(&game, &Game::render);
	window.setDeltaTimeStep(0.1);
	window.showFPS(true);
	window.run();

	return window.mainReturn();
}