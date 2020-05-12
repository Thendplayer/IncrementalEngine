#include <Windows.h>

#include "RenderWindow.h"
#include "WindowsInput.h"
#include "Config.h"

namespace IncrementalEngine
{	
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	RenderWindow::RenderWindow()
	{
		WNDCLASSEX wc;
		DEVMODE dmScreenSettings;
		int posX, posY;

		_hInstance = GetModuleHandle(NULL);

		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = _hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = APPLICATION_NAME;
		wc.cbSize = sizeof(WNDCLASSEX);

		RegisterClassEx(&wc);

		_screenWidth = GetSystemMetrics(SM_CXSCREEN);
		_screenHeight = GetSystemMetrics(SM_CYSCREEN);

		if (FULLSCREEN)
		{
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = (unsigned long)_screenWidth;
			dmScreenSettings.dmPelsHeight = (unsigned long)_screenHeight;
			dmScreenSettings.dmBitsPerPel = 32;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

			posX = posY = 0;
		}
		else
		{
			_screenWidth = DEFAULT_WINDOWED_SCREEN_WIDTH;
			_screenHeight = DEFAULT_WINDOWED_SCREEN_HEIGHT;

			posX = (GetSystemMetrics(SM_CXSCREEN) - _screenWidth) / 2;
			posY = (GetSystemMetrics(SM_CYSCREEN) - _screenHeight) / 2;
		}

		RECT wr = { 0, 0, _screenWidth, _screenHeight };
		AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
		
		_hWnd = CreateWindowEx(
			WS_EX_APPWINDOW,
			APPLICATION_NAME,
			APPLICATION_NAME,
			WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
			posX,
			posY,
			wr.right - wr.left,
			wr.bottom - wr.top,
			NULL,
			NULL,
			_hInstance,
			NULL
		);

		ShowWindow(_hWnd, SW_SHOW);
		SetForegroundWindow(_hWnd);
		SetFocus(_hWnd);

		ShowCursor(SHOW_CURSOR);
	}

	RenderWindow::~RenderWindow()
	{
		ShowCursor(true);

		if (FULLSCREEN)
		{
			ChangeDisplaySettings(NULL, 0);
		}

		DestroyWindow(_hWnd);
		_hWnd = NULL;

		UnregisterClass(APPLICATION_NAME, _hInstance);
		_hInstance = NULL;
	}

	HWND RenderWindow::GetHWND()
	{
		return _hWnd;
	}

	HINSTANCE* RenderWindow::GetHInstance()
	{
		return &_hInstance;
	}

	int RenderWindow::GetScreenWidth()
	{
		return _screenWidth;
	}

	int RenderWindow::GetScreenHeight()
	{
		return _screenHeight;
	}

	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
			case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}

			case WM_CLOSE:
			{
				PostQuitMessage(0);
				return 0;
			}

			default:
			{
				return WindowsInput::WINDOWS_INPUT->MessageHandler(hWnd, message, wParam, lParam);
			}
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}