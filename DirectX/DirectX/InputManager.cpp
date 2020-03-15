#include "InputManager.h"

namespace MyEngine
{
	InputManager::InputManager()
	{
		for (int i = 0; i < KEY_NUM; i++)
		{
			_keys[i] = false;
		}
	}

	InputManager::~InputManager()
	{
	}

	void InputManager::KeyDown(unsigned int input)
	{
		_keys[input] = true;
	}

	void InputManager::KeyUp(unsigned int input)
	{
		_keys[input] = false;
	}

	bool InputManager::IsKeyDown(unsigned int key)
	{
		return _keys[key];
	}

	LRESULT InputManager::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			case WM_KEYDOWN:
			{
				KeyDown((unsigned int)wParam);
				return 0;
			}
			case WM_KEYUP:
			{
				KeyUp((unsigned int)wParam);
				return 0;
			}
			default:
			{
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
	}
}