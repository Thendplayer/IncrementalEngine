#include "InputManager.h"
#include "Utils.h"

namespace MyEngine
{
	InputManager::InputManager() : 
		_directInput(NULL),
		_mouseInput(NULL)
	{
		for (int i = 0; i < KEY_NUM; i++)
		{
			_keys[i] = false;
		}
	}

	InputManager::~InputManager() 
	{
		if (_mouseInput)
		{
			_mouseInput->Unacquire();
			CHECKED_RELEASE(_mouseInput);
		}

		CHECKED_RELEASE(_directInput);
	}

	HRESULT InputManager::Init(RenderWindow* renderWindow)
	{
		HRESULT result;

		_renderWindow = renderWindow;
		_mouseX = _mouseY = 0;

		result = DirectInput8Create(
			*_renderWindow->GetHInstance(), 
			DIRECTINPUT_VERSION, 
			IID_IDirectInput8, 
			(void**)&_directInput, 
			NULL
		);

		if (FAILED(result))
		{
			return FALSE;
		}

		result = _directInput->CreateDevice(
			GUID_SysMouse, 
			&_mouseInput, 
			NULL
		);

		if (FAILED(result))
		{
			return FALSE;
		}

		result = _mouseInput->SetDataFormat(&c_dfDIMouse);

		if (FAILED(result))
		{
			return FALSE;
		}

		result = _mouseInput->SetCooperativeLevel(
			_renderWindow->GetHWND(), 
			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE
		);

		if (FAILED(result))
		{
			return FALSE;
		}

		result = _mouseInput->Acquire();

		if (FAILED(result))
		{
			return FALSE;
		}

		return S_OK;
	}

	HRESULT InputManager::Update()
	{
		HRESULT result;

		result = ReadMouse();
		if (FAILED(result))
		{
			return FALSE;
		}

		ProcessInput();

		return S_OK;
	}

	HRESULT InputManager::ReadMouse()
	{
		HRESULT result;

		result = _mouseInput->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&_mouseState);
		if (FAILED(result))
		{
			if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			{
				_mouseInput->Acquire();
			}
			else
			{
				return FALSE;
			}
		}

		return S_OK;
	}


	void InputManager::ProcessInput()
	{
		_mouseX += _mouseState.lX;
		_mouseY += _mouseState.lY;

		if (_mouseX < 0) 
		{
			_mouseX = 0; 
		}

		if (_mouseY < 0) 
		{ 
			_mouseY = 0; 
		}

		if (_mouseX > _renderWindow->GetScreenWidth()) 
		{ 
			_mouseX = _renderWindow->GetScreenWidth(); 
		}

		if (_mouseY > _renderWindow->GetScreenHeight()) 
		{ 
			_mouseY = _renderWindow->GetScreenHeight(); 
		}
	}

	void InputManager::GetMouseLocation(int& mouseX, int& mouseY)
	{
		mouseX = _mouseX;
		mouseY = _mouseY;
	}

	bool InputManager::IsKeyDown(DirectInputKey key)
	{
		return _keys[(unsigned int)key];
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