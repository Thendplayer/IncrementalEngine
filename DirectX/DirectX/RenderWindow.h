#ifndef _RenderWindow_H
#define _RenderWindow_H

#include <windows.h>
#include <windowsx.h>

namespace MyEngine
{
	class RenderWindow
	{
		private:
			HINSTANCE _hinstance;
			HWND _hWnd;

		public:
			int ScreenWidth, ScreenHeight;

			void Update(float dt);
			void Draw();

			HWND GetHWND();

			RenderWindow();
			~RenderWindow();
	};
}

#endif