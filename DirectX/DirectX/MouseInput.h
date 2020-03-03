#ifndef INC_MOUSE_H_
#define INC_MOUSE_H_

#include <dinput.h>
#include "Math.h"

class MouseInput
{
private:
	LPDIRECTINPUT8 directInput;
	LPDIRECTINPUTDEVICE8 mouseInput;	

	Vector2Int movement;
	bool buttonRight, previousButtonRight;
	bool buttonLeft, previousButtonLeft;
	bool buttonMiddle, previousButtonMiddle;
public:
	MouseInput(HWND hWnd);
	virtual ~MouseInput();
	
	bool Update();
	int GetMovementX() const;
	int GetMovementY() const;
	int GetMovementZ() const;
	bool IsLeftButtonPressed() const;
	bool IsMiddleButtonPressed() const;
	bool IsRightButtonPressed() const;

	bool LeftButtonBecomesPressed() const;
	bool MiddleButtonBecomesPressed() const;
	bool RightButtonBecomesPressed() const;

	bool LeftButtonBecomesReleased() const;
	bool MiddleButtonBecomesReleased() const;
	bool RightButtonBecomesReleased() const;
};

#endif
