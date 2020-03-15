#ifndef _INPUTCLASS_H
#define _INPUTCLASS_H

#include "WindowsInput.h"

namespace MyEngine
{
	#define KEY_NUM 256
	
	class InputManager : public WindowsInput
	{
	private:
		bool _keys[KEY_NUM];
		
		void KeyDown(unsigned int input);
		void KeyUp(unsigned int input);
		
	public:
		InputManager();
		~InputManager();

		bool IsKeyDown(unsigned int key);

		virtual LRESULT MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	};
}

#endif