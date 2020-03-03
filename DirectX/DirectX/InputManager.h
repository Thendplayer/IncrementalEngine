#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include "MouseInput.h"
#include "KeyboardInput.h"

namespace MyEngine
{
	class InputManager
	{
	private:
		MouseInput* mouseInput;
		KeyboardInput* keyboardInput;
	public:
		InputManager(HWND hWnd);
		~InputManager();  

		void Update();
	
		MouseInput* GetMouse()
		{
			return mouseInput;
		}

		KeyboardInput* GetKeyboard()
		{
			return keyboardInput;
		}
	};
}

#endif
