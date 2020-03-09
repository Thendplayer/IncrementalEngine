#include "KeyboardInput.h"
#include "Utils.h"

namespace MyEngine
{
	KeyboardInput::KeyboardInput(HWND hWnd)
	{
		ZeroMemory(diks, 256);
		ZeroMemory(previousDiks, 256);

		HRESULT result;
		DWORD coopFlags = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;

		result = DirectInput8Create(
			GetModuleHandle(NULL), 
			DIRECTINPUT_VERSION, 
			IID_IDirectInput8, 
			(VOID**)&dI, 
			NULL
		);
	
		if(FAILED(result))
		{
			return;
		}

		result = dI->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	
		if(FAILED(result))
		{
			return;
		}
	
		result = keyboard->SetDataFormat(&c_dfDIKeyboard);
	
		if(FAILED(result))
		{
			return;
		}
    
		result = keyboard->SetCooperativeLevel(hWnd, coopFlags);
 
		if(FAILED(result))
		{
			return;
		}

		keyboard->Acquire();
	}

	KeyboardInput::~KeyboardInput()
	{
		if(keyboard)
		{
			keyboard->Unacquire();
		}
    
		CHECKED_RELEASE(keyboard);
		CHECKED_RELEASE(dI);
	}

	bool KeyboardInput::Update()
	{
		HRESULT result;
	
		if(NULL == keyboard)
		{
			return false;
		}
    
		memcpy(previousDiks, diks, 256);
		ZeroMemory(diks, 256);

		result = keyboard->GetDeviceState(sizeof(diks), (LPVOID)&diks);

		if(FAILED(result)) 
		{
			result = keyboard->Acquire();
			while(result == DIERR_INPUTLOST)
			{
				result = keyboard->Acquire();
			}

			return true;
		}
	
		return true;
	}

	bool KeyboardInput::IsKeyPressed(int keyCode)
	{
		return (diks[keyCode]&0x80) != 0;
	}

	bool KeyboardInput::KeyBecomesPressed(int keyCode)
	{
		return diks[keyCode]&0x80 && !(previousDiks[keyCode]&0x80);
	}

	bool KeyboardInput::KeyBecomesReleased(int keyCode)
	{
		return !(diks[keyCode]&0x80) && previousDiks[keyCode]&0x80;
	}
}
