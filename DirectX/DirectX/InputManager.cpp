#include "InputManager.h"
#include "Utils.h"

#include <string>
#include <map>

namespace MyEngine
{
	InputManager::InputManager(HWND hWnd)
	{
		keyboardInput = new KeyboardInput(hWnd);
		mouseInput = new MouseInput(hWnd);
	}

	InputManager::~InputManager()
	{
		CHECKED_DELETE(mouseInput);
		CHECKED_DELETE(keyboardInput);
	}

	void InputManager::Update()
	{
		keyboardInput->Update();
		mouseInput->Update();
	}
}