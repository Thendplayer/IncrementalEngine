#include "InputManager.h"
#include "defines.h"

#include <string>
#include <map>

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
