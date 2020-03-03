#include "KeyboardInput.h"
#include "Utils.h"

KeyboardInput::KeyboardInput(HWND hWnd)
{
	ZeroMemory(diks, 256);
	ZeroMemory(previousDiks, 256);

	HRESULT hr;
    DWORD coopFlags = DISCL_NONEXCLUSIVE | DISCL_FOREGROUND;

    hr = DirectInput8Create(
        GetModuleHandle(NULL), 
        DIRECTINPUT_VERSION, 
        IID_IDirectInput8, 
        (VOID**)&dI, 
        NULL
    );
	
    if(FAILED(hr))
    {
	    return;
    }

    hr = dI->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	
	if(FAILED(hr))
	{
		return;
	}
	
    hr = keyboard->SetDataFormat(&c_dfDIKeyboard);
	
	if(FAILED(hr))
	{
		return;
	}
    
    hr = keyboard->SetCooperativeLevel(hWnd, coopFlags);
 
    if(FAILED(hr))
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
	HRESULT hr;
	
    if(NULL == keyboard)
    {
	    return false;
    }
    
	memcpy(previousDiks, diks, 256);
    ZeroMemory(diks, 256);

	hr = keyboard->GetDeviceState(sizeof(diks), (LPVOID)&diks);

	if(FAILED(hr)) 
    {
        hr = keyboard->Acquire();
        while(hr == DIERR_INPUTLOST)
            hr = keyboard->Acquire();

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