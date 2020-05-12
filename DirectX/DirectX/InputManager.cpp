#include "InputManager.h"
#include "Utils.h"

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

	HRESULT InputManager::Init(RenderWindow* renderWindow)
	{
		_renderWindow = renderWindow;
		_mouseX = _mouseY = 0;

		return S_OK;
	}

	HRESULT InputManager::Update()
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(_renderWindow->GetHWND(), &pt);

		_mouseX = pt.x - _renderWindow->GetScreenWidth() * .5f;
		_mouseY = pt.y - _renderWindow->GetScreenHeight() * .5f;

		return S_OK;
	}

	void InputManager::GetMousePosition(float& mouseX, float& mouseY)
	{
		mouseX = _mouseX;
		mouseY = _mouseY;
	}

	bool InputManager::IsKeyDown(DirectInputKey key)
	{
		return _keys[(unsigned int)key];
	}

	bool InputManager::IsMouseButtonDown(DirectInputMouseButton button)
	{
		switch (button)
		{
			case DirectInputMouseButton::MouseLeft:
			{
				return _leftMousePressed;
			};
			case DirectInputMouseButton::MouseRight:
			{
				return _rightMousePressed;
			}
		}

		return false;
	}

	void InputManager::KeyDown(unsigned int key)
	{
		_keys[key] = true;
		return;
	}

	void InputManager::KeyUp(unsigned int key)
	{
		_keys[key] = false;
		return;
	}

	bool InputManager::MouseInsideScreen()
	{
		return _mouseX > -_renderWindow->GetScreenWidth() * .5f &&
			   _mouseX < _renderWindow->GetScreenWidth() * .5f &&
			   _mouseY > -_renderWindow->GetScreenHeight() * .5f &&
			   _mouseY < _renderWindow->GetScreenHeight() * .5f;
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
			case WM_LBUTTONDOWN:
			{
				_leftMousePressed = true;
				return 0;
			}
			case WM_LBUTTONUP:
			{
				_leftMousePressed = false;
				return 0;
			}
			case WM_RBUTTONDOWN:
			{
				_rightMousePressed = true;
				return 0;
			}
			case WM_RBUTTONUP:
			{
				_rightMousePressed = false;
				return 0;
			}
			default:
			{
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
	}
}