#ifndef _WINDOWSINPUTCLASS_H
#define _WINDOWSINPUTCLASS_H

#include <windows.h>

namespace IncrementalEngine 
{
	class WindowsInput
	{
	public:
		static WindowsInput* WINDOWS_INPUT;
		virtual LRESULT MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;

		WindowsInput();
	};
}

#endif