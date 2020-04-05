#include <windows.h>
#include <windowsx.h>

#include "MainEngine.h"
#include "ExampleGame.h"

using namespace MyGame;
using namespace MyEngine;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	auto game = new ExampleGame;
	auto engine = Engine::Get();
	
	engine->Run(game);
	
	delete engine;
	
	return 0;
}