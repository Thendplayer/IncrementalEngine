#pragma once
#include <WinUser.h>

enum class DirectInputKey : unsigned int
{
	Backspace = VK_BACK,
	Delete = VK_DELETE,
	Tab = VK_TAB,
	Clear = VK_CLEAR,
	Return = VK_RETURN,
	Pause = VK_PAUSE,
	Escape = VK_ESCAPE,
	Space = VK_SPACE,
	Keypad0 = VK_NUMPAD0,
	Keypad1 = VK_NUMPAD1,
	Keypad2 = VK_NUMPAD2,
	Keypad3 = VK_NUMPAD3,
	Keypad4 = VK_NUMPAD4,
	Keypad5 = VK_NUMPAD5,
	Keypad6 = VK_NUMPAD6,
	Keypad7 = VK_NUMPAD7,
	Keypad8 = VK_NUMPAD8,
	Keypad9 = VK_NUMPAD9,
	KeypadPeriod = VK_DECIMAL,
	KeypadDivide = VK_DIVIDE,
	KeypadMultiply = VK_MULTIPLY,
	KeypadMinus = VK_SUBTRACT,
	KeypadPlus = VK_ADD,
	UpArrow = VK_UP,
	DownArrow = VK_DOWN,
	RightArrow = VK_RIGHT,
	LeftArrow = VK_LEFT,
	Insert = VK_INSERT,
	Home = VK_HOME,
	End = VK_END,
	PageUp = VK_PRIOR,
	PageDown = VK_NEXT,
	F1 = VK_F1,
	F2 = VK_F2,
	F3 = VK_F3,
	F4 = VK_F4,
	F5 = VK_F5,
	F6 = VK_F6,
	F7 = VK_F7,
	F8 = VK_F8,
	F9 = VK_F9,
	F10 = VK_F10,
	F11 = VK_F11,
	F12 = VK_F12,
	F13 = VK_F13,
	F14 = VK_F14,
	F15 = VK_F15,
	F16 = VK_F16,
	F17 = VK_F17,
	F18 = VK_F18,
	F19 = VK_F19,
	F20 = VK_F20,
	F21 = VK_F21,
	F22 = VK_F22,
	F23 = VK_F23,
	F24 = VK_F24,
	Alpha0 = 0x30,
	Alpha1 = 0x31,
	Alpha2 = 0x32,
	Alpha3 = 0x33,
	Alpha4 = 0x34,
	Alpha5 = 0x35,
	Alpha6 = 0x36,
	Alpha7 = 0x37,
	Alpha8 = 0x38,
	Alpha9 = 0x39,
	Quote = VK_OEM_7,
	Plus = VK_OEM_PLUS,
	Comma = VK_OEM_COMMA,
	Minus = VK_OEM_MINUS,
	Period = VK_OEM_PERIOD,
	Slash = VK_OEM_2,
	Colon = VK_OEM_1,
	Less = VK_OEM_102,
	Equals = VK_OEM_NEC_EQUAL,
	Greater = VK_OEM_102,
	LeftBracket = VK_OEM_4,
	Backslash = VK_OEM_5,
	RightBracket = VK_OEM_6,
	BackQuote = VK_OEM_3,
	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A,
	Numlock = VK_NUMLOCK,
	CapsLock = VK_CAPITAL,
	Shift = VK_SHIFT,
	LeftShift = VK_LSHIFT,
	RightShift = VK_RSHIFT,
	Control = VK_CONTROL,
	LeftControl = VK_LCONTROL,
	RightControl = VK_RCONTROL,
	Alt = VK_MENU,
	LeftAlt = VK_LMENU,
	RightAlt = VK_RMENU,
	Help = VK_HELP,
	Print = VK_PRINT,
	LeftWindows = VK_LWIN,
	RightWindows = VK_RWIN,
	MouseRight = VK_RBUTTON,
	MouseLeft = VK_LBUTTON,
	MouseMiddle = VK_MBUTTON
};