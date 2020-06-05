#include "MainGame.h"
#include <MainEngine.h>

#include <UpgradesPerSecondPanelData.h>
#include <UpgradesPerClickPanelData.h>

namespace MagicIdle
{
	void MainGame::Init()
	{
		_displayPanel = Engine::Get()->Scene()->Create<DisplayPanelMediator>();
		auto displayPanelModel = _displayPanel->GetModel();

		_actionButton = Engine::Get()->Scene()->Create<ActionButtonMediator>();
		_actionButton->SetDisplayPanelModel(displayPanelModel);

		auto upgradesPerSecondPanel = Engine::Get()->Scene()->Create<UpgradesPanel>();
		upgradesPerSecondPanel->AddElements(
			UpgradesPerSecondPanelData, 
			displayPanelModel->GetCurrency(), 
			_actionButton->GetTapValue()
		);

		auto upgradesPerClickPanel = Engine::Get()->Scene()->Create<UpgradesPanel>();
		upgradesPerClickPanel->AddElements(
			UpgradesPerClickPanelData, 
			displayPanelModel->GetCurrency(),
			_actionButton->GetTapValue() //TODO: Change with the Seconds Value
		);

		_upgradesPerSecondButton = Engine::Get()->Scene()->Create<Button>();
		_upgradesPerSecondButton->SetScale(.66f, .66f);
		_upgradesPerSecondButton->SetPosition(-547, -185);

		_upgradesPerClickButton = Engine::Get()->Scene()->Create<Button>();
		_upgradesPerClickButton->SetScale(.66f, .66f);
		_upgradesPerClickButton->SetPosition(-474, -182);

		_multiPanel = Engine::Get()->Scene()->Create<MultiPanel>();
		
		_multiPanel->AddPair(
			upgradesPerSecondPanel, 
			_upgradesPerSecondButton, 
			Engine::Get()->Resources()->GetTexture("UpgradesPerSecondPanelButtonPressed"),
			Engine::Get()->Resources()->GetTexture("UpgradesPerSecondPanelButton")
		);

		_multiPanel->AddPair(
			upgradesPerClickPanel,
			_upgradesPerClickButton,
			Engine::Get()->Resources()->GetTexture("UpgradesPerClickPanelButtonPressed"),
			Engine::Get()->Resources()->GetTexture("UpgradesPerClickPanelButton")
		);
	}
	
	void MainGame::DeInit()
	{
	}
	
	void MainGame::Update(float dt)
	{
	}
}