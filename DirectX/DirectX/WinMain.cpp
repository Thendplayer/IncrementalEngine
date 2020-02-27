#include <windows.h>
#include <windowsx.h>
#include "MainEngine.h"

#include "ExampleGame.h"
using namespace MyGame;

using namespace MyEngine;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	auto a = new ExampleGame;
	Engine::Get()->Run(hInstance);
	return 0;
}