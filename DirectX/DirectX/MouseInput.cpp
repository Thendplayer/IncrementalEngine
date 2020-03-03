#include "MouseInput.h"
#include "defines.h"

MouseInput::MouseInput(HWND hWnd) :
	movementX(0),
	movementY(0),
	movementZ(0),
	buttonLeft(false),
	buttonMiddle(false),
	buttonRight(false),
	previousButtonLeft(false),
	previousButtonMiddle(false),
	previousButtonRight(false)
{
	HRESULT l_HR;
	DWORD l_CoopFlags=0;
    
	if(FAILED(l_HR=DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&directInput, NULL)))
		return;
	if (FAILED(l_HR = directInput->CreateDevice(GUID_SysMouse, &mouseInput, NULL)))
		return;
	if (FAILED(l_HR = mouseInput->SetDataFormat(&c_dfDIMouse2)))
		return;
	if (FAILED(l_HR = mouseInput->SetCooperativeLevel(hWnd, l_CoopFlags)))
		return;

	if (mouseInput != NULL)
		mouseInput->Acquire();
	else
		MessageBox(hWnd, L"Problem with the mouse input!", L"Mouse", MB_ICONERROR | MB_OK);
}

MouseInput::~MouseInput()
{
	if (mouseInput != NULL)
		mouseInput->Unacquire();

	CHECKED_RELEASE(mouseInput);
	CHECKED_RELEASE(directInput);
}

bool MouseInput::Update()
{
	DIMOUSESTATE2 l_DIMouseState;

	if (mouseInput == NULL)
		return false;

	ZeroMemory(&l_DIMouseState, sizeof(l_DIMouseState));
	HRESULT l_HR = mouseInput->GetDeviceState(sizeof(DIMOUSESTATE2), &l_DIMouseState);
	if (FAILED(l_HR))
	{
		l_HR = mouseInput->Acquire();
		while (l_HR == DIERR_INPUTLOST)
			l_HR = mouseInput->Acquire();
        return true;
    }
    
	movementX=l_DIMouseState.lX; 
	movementY=l_DIMouseState.lY;
	movementZ=l_DIMouseState.lZ;


	previousButtonLeft=buttonLeft;
	previousButtonMiddle=buttonMiddle;
	previousButtonRight=buttonRight;

	buttonRight=(l_DIMouseState.rgbButtons[1] & 0x80)!=0;
	buttonLeft=(l_DIMouseState.rgbButtons[0] & 0x80)!=0;
	buttonMiddle=(l_DIMouseState.rgbButtons[2] & 0x80)!=0;

	return true;
}

int MouseInput::GetMovementX() const
{
	return movementX;
}

int MouseInput::GetMovementY() const
{
	return movementY;
}

int MouseInput::GetMovementZ() const
{
	return movementZ;
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
