#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

#include <dinput.h>

class KeyboardInput
{
private:
	char previousDiks[256];
	char diks[256];
	LPDIRECTINPUT8 dI;
	LPDIRECTINPUTDEVICE8 keyboard;
public:
	KeyboardInput(HWND hWnd);
	~KeyboardInput();

	bool Update();
	bool IsKeyPressed(int keyCode);
	bool KeyBecomesPressed(int keyCode);
	bool KeyBecomesReleased(int keyCode);
};

#endif
