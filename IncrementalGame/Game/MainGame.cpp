#include "MainGame.h"
#include <MainEngine.h>

namespace MagicIdle
{
	void MainGame::Init()
	{
		_actionButton = Engine::Get()->Scene()->Create<ActionButton>();
		_actionButton->SetPosition(355, -7);

		_displayPanel = Engine::Get()->Scene()->Create<DisplayPanel>();
		_displayPanel->SetPosition(-332, -272);
		_displayPanel->SetScale(.66f, .66f);

		_upgradeElement = Engine::Get()->Scene()->Create<UpgradeElement>();
		_upgradeElement->SetPosition(-332, -120);
	}
	
	void MainGame::DeInit()
	{
	}
	
	void MainGame::Update(float dt)
	{
	}
}