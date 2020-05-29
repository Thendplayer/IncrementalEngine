#include "MainGame.h"
#include <MainEngine.h>

namespace MagicIdle
{
	void MainGame::Init()
	{
		_actionButton = Engine::Get()->Scene()->Create<ActionButton>();
		_actionButton->SetPosition(355, -7);

		_displayPanel = Engine::Get()->Scene()->Create<DisplayPanel>();
		_displayPanel->SetPosition(-332, -275);
		_displayPanel->SetScale(.66f, .66f);

		auto upgradesPerSecondPanel = Engine::Get()->Scene()->Create<UpgradesPerSecondPanel>();
		upgradesPerSecondPanel->SetPosition(-315, -205);
		
		_multiPanel = Engine::Get()->Scene()->Create<MultiPanel>();
		_multiPanel->AddPair(upgradesPerSecondPanel, upgradesPerSecondPanel->GetPanelButton());
	}
	
	void MainGame::DeInit()
	{
	}
	
	void MainGame::Update(float dt)
	{
	}
}