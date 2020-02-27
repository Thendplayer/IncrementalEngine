#include "EngineGame.h"
#include <cassert>

namespace MyEngine
{
	EngineGame* EngineGame::GAME_INSTANCE = nullptr;
	
	EngineGame::EngineGame(EngineGame* game)
	{
		GAME_INSTANCE = game;
	}

	EngineGame::~EngineGame()
	{
		GAME_INSTANCE = nullptr;
	}
	
	EngineGame* EngineGame::Get()
	{
		assert(GAME_INSTANCE != NULL);
		return GAME_INSTANCE;
	}
}
