#ifndef _INPUTCLASS_H
#define _INPUTCLASS_H

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>
#include "WindowsInput.h"
#include "DirectInputKey.h"
#include "RenderWindow.h"

namespace MyEngine
{
	#define KEY_NUM 256
	
	class InputManager : public WindowsInput
	{
	public:
		InputManager();
		virtual ~InputManager();

		HRESULT Init(RenderWindow* renderWindow);
		HRESULT Update();

		bool IsKeyDown(DirectInputKey key);
		void GetMouseLocation(int& mouseX, int& mouseY);

		virtual LRESULT MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
		
	private:
		RenderWindow* _renderWindow;

		IDirectInput8* _directInput;
		IDirectInputDevice8* _mouseInput;

		unsigned char _keys[KEY_NUM];
		DIMOUSESTATE _mouseState;

		int _mouseX, _mouseY;

		HRESULT ReadMouse();
		void ProcessInput();
		
		void KeyDown(unsigned int key);
		void KeyUp(unsigned int key);
	};
}

#endif