#ifndef _RenderWindow_H
#define _RenderWindow_H

#include <windows.h>
#include <windowsx.h>

namespace MyEngine
{
	class RenderWindow
	{
		private:
			HINSTANCE _hInstance;
			HWND _hWnd;
			int _screenWidth, _screenHeight;

		public:

			HWND GetHWND();
			HINSTANCE* GetHInstance();
			int GetScreenWidth();
			int GetScreenHeight();

			RenderWindow();
			virtual ~RenderWindow();
	};
}

#endif