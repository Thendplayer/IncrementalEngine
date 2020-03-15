#include <Windows.h>

#include "RenderWindow.h"
#include "WindowsInput.h"
#include "Config.h"

namespace MyEngine
{	
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	RenderWindow::RenderWindow()
	{
		WNDCLASSEX wc;
		DEVMODE dmScreenSettings;
		int posX, posY;

		_hinstance = GetModuleHandle(NULL);

		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = _hinstance;
		wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wc.hIconSm = wc.hIcon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = APPLICATION_NAME;
		wc.cbSize = sizeof(WNDCLASSEX);

		RegisterClassEx(&wc);

		ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

		if (FULLSCREEN)
		{
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = (unsigned long)ScreenWidth;
			dmScreenSettings.dmPelsHeight = (unsigned long)ScreenHeight;
			dmScreenSettings.dmBitsPerPel = 32;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

			posX = posY = 0;
		}
		else
		{
			ScreenWidth = DEFAULT_WINDOWED_SCREEN_WIDTH;
			ScreenHeight = DEFAULT_WINDOWED_SCREEN_HEIGHT;

			posX = (GetSystemMetrics(SM_CXSCREEN) - ScreenWidth) / 2;
			posY = (GetSystemMetrics(SM_CYSCREEN) - ScreenHeight) / 2;
		}

		_hWnd = CreateWindowEx(
			WS_EX_APPWINDOW,
			APPLICATION_NAME,
			APPLICATION_NAME,
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
			posX,
			posY,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			_hinstance,
			NULL
		);

		ShowWindow(_hWnd, SW_SHOW);
		SetForegroundWindow(_hWnd);
		SetFocus(_hWnd);

		ShowCursor(SHOW_CURSOR);
	}

	RenderWindow::~RenderWindow()
	{
	}

	void RenderWindow::Update(float dt)
	{

	}

	void RenderWindow::Draw()
	{

	}

	HWND RenderWindow::GetHWND()
	{
		return _hWnd;
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