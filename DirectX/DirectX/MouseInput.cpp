#include "MouseInput.h"
#include "Utils.h"

namespace MyEngine
{
	MouseInput::MouseInput(HWND hWnd) :
		movement(0, 0, 0),
		buttonLeft(false),
		buttonMiddle(false),
		buttonRight(false),
		previousButtonLeft(false),
		previousButtonMiddle(false),
		previousButtonRight(false)
	{
		HRESULT hr;
		DWORD coopFlags = 0;

		hr = DirectInput8Create(
			GetModuleHandle(NULL), 
			DIRECTINPUT_VERSION, 
			IID_IDirectInput8, 
			(VOID**)&directInput, 
			NULL
		);
	
		if(FAILED(hr))
		{
			return;
		}

		hr = directInput->CreateDevice(
			GUID_SysMouse,
			&mouseInput,
			NULL
		);
	
		if (FAILED(hr))
		{
			return;
		}
	
		hr = mouseInput->SetDataFormat(&c_dfDIMouse2);

		if (FAILED(hr))
		{
			return;
		}
	
		hr = mouseInput->SetCooperativeLevel(hWnd, coopFlags);
	
		if (FAILED(hr))
		{
			return;
		}

		if (mouseInput != NULL)
		{
			mouseInput->Acquire();
		}
		else
		{
			MessageBox(
				hWnd, 
				L"Problem with the mouse input!", 
				L"Mouse", 
				MB_ICONERROR | MB_OK
			);
		}
	}

	MouseInput::~MouseInput()
	{
		if (mouseInput != NULL)
		{
			mouseInput->Unacquire();
		}

		CHECKED_RELEASE(mouseInput);
		CHECKED_RELEASE(directInput);
	}

	bool MouseInput::Update()
	{
		HRESULT result;
		DIMOUSESTATE2 mouseState;

		if (mouseInput == NULL)
		{
			return false;
		}

		ZeroMemory(&mouseState, sizeof(mouseState));
	
		result = mouseInput->GetDeviceState(sizeof(DIMOUSESTATE2), &mouseState);

		if (FAILED(result))
		{
			result = mouseInput->Acquire();

			while (result == DIERR_INPUTLOST)
			{
				result = mouseInput->Acquire();
			}

			return true;
		}

		movement = Eigen::Vector3i(mouseState.lX, mouseState.lY, mouseState.lZ);
	
		previousButtonLeft = buttonLeft;
		previousButtonMiddle = buttonMiddle;
		previousButtonRight = buttonRight;

		buttonRight = (mouseState.rgbButtons[1] & 0x80) != 0;
		buttonLeft = (mouseState.rgbButtons[0] & 0x80) != 0;
		buttonMiddle = (mouseState.rgbButtons[2] & 0x80) != 0;

		return true;
	}

	Eigen::Vector3i MouseInput::GetMovement() const
	{
		return movement;
	}

	bool MouseInput::IsRightButtonPressed() const
	{
		return buttonRight;
	}

	bool MouseInput::IsLeftButtonPressed() const
	{
		return buttonLeft;
	}

	bool MouseInput::IsMiddleButtonPressed() const
	{
		return buttonMiddle;
	}

	bool MouseInput::LeftButtonBecomesPressed() const
	{
		return buttonLeft && !previousButtonLeft;
	}

	bool MouseInput::MiddleButtonBecomesPressed() const
	{
		return buttonMiddle && !previousButtonMiddle;
	}

	bool MouseInput::RightButtonBecomesPressed() const
	{
		return buttonRight && !previousButtonRight;
	}

	bool MouseInput::LeftButtonBecomesReleased() const
	{
		return !buttonLeft && previousButtonLeft;
	}

	bool MouseInput::MiddleButtonBecomesReleased() const
	{
		return !buttonMiddle && previousButtonMiddle;
	}

	bool MouseInput::RightButtonBecomesReleased() const
	{
		return !buttonRight && previousButtonRight;
	}
}
