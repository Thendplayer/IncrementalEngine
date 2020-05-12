#ifndef _INPUTCLASS_H
#define _INPUTCLASS_H

#include "WindowsInput.h"
#include "DirectInputKey.h"
#include "RenderWindow.h"

namespace IncrementalEngine
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
		bool IsMouseButtonDown(DirectInputMouseButton button);

		void GetMousePosition(float& mouseX, float& mouseY);
		bool MouseInsideScreen();

		virtual LRESULT MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
		
	private:
		RenderWindow* _renderWindow;

		unsigned char _keys[KEY_NUM];

		float _mouseX, _mouseY;
		bool _leftMousePressed, _rightMousePressed;
		
		void KeyDown(unsigned int key);
		void KeyUp(unsigned int key);
	};
}

#endif