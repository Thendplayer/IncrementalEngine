#include "MainEngine.h"
#include "EngineGame.h"
#include <cassert>

namespace MyEngine
{
	Engine* Engine::ENGINE_INSTANCE = nullptr;
	
	Engine* Engine::Get()
	{
		if (ENGINE_INSTANCE == nullptr)
		{
			ENGINE_INSTANCE = new Engine;
		}

		return ENGINE_INSTANCE;
	}

	Engine::Engine()
	{
	}

	Engine::~Engine()
	{
		ENGINE_INSTANCE = nullptr;
	}

	void Engine::Run(HINSTANCE hInstance, EngineGame* game)
	{
		Init();
		game->Init();

		//Update and things...
	}

	void Engine::Init()
	{
	}

	void Engine::Update()
	{
	}

	void Engine::Draw()
	{
	}
}
