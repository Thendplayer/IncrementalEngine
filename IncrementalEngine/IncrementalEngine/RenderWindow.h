#ifndef _RenderWindow_H
#define _RenderWindow_H

#include <windows.h>
#include <windowsx.h>
#include "Config.h"

namespace IncrementalEngine
{
	class RenderWindow
	{
		public:
			RenderWindow(Config config);
			virtual ~RenderWindow();
			
			HWND GetHWND();
			HINSTANCE* GetHInstance();
			int GetScreenWidth();
			int GetScreenHeight();
			float GetScreenNear();
			float GetScreenDepth();

			void SetIcon(LPCWSTR icon);

		private:
			HINSTANCE _hInstance;
			HWND _hWnd;
			Config _config;
			int _screenWidth, _screenHeight;
	};
}

#endif