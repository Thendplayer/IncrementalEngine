#include "MainGame.h"
#include <MainEngine.h>

namespace MagicIdle
{
	void MainGame::Init()
	{
		_actionButton = Engine::Get()->Scene()->Create<ActionButton>();
		_actionButton->SetPosition(355, -7);
	}
	
	void MainGame::DeInit()
	{
	}
	
	void MainGame::Update(float dt)
	{
	}
}