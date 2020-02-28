#include <windows.h>
#include <windowsx.h>
#include "MainEngine.h"
#include "ExampleGame.h"

using namespace MyGame;
using namespace MyEngine;

auto const GAME = new ExampleGame;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Engine::Get()->Run(hInstance);
	return 0;
}