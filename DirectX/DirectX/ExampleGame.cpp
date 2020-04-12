#include "ExampleGame.h"
#include "MainEngine.h"

namespace MyGame
{
	ExampleGame::ExampleGame(): EngineGame()
	{
	}

	ExampleGame::~ExampleGame()
	{
		
	}

	void ExampleGame::Init()
	{
		Engine::Get()->GetScene()->Create<Actor>();
	}

	void ExampleGame::DeInit()
	{
		delete this;
	}

	void ExampleGame::Update(float dt)
	{
	}
}
