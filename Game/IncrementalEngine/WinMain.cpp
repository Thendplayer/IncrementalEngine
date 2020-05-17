#include <windows.h>
#include <windowsx.h>

#include "Description.h"
#include "MainEngine.h"
#include GAME_HEADER

using namespace IncrementalEngine;
using namespace GAME_NAMESPACE;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	auto game = new GAME_CLASS;
	auto engine = Engine::Get();
	
	engine->Run(game);
	
	delete game;
	delete engine;
	
	return 0;
}