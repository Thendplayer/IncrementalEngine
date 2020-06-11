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
		auto upgradesPerClickPanel = Engine::Get()->Scene()->Create<UpgradesPanel>();

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

		_orbSpawner = Engine::Get()->Scene()->Create<OrbSpawner>();

		_profileButton = Engine::Get()->Scene()->Create<Button>();
		_profileButton->SetTexture(Engine::Get()->Resources()->GetTexture("ProfileButton"));
		_profileButton->SetScale(.66f, .66f);
		_profileButton->SetPosition(570, -288);

		_profile = Engine::Get()->Scene()->Create<ProfileMediator>();
		_profile->SetScale(.66f, .66f);
		_profile->SetActive(false);

		auto profileModel = _profile->GetModel();
		_displayPanel->SetTotalEarnedPtr(profileModel->GetTotalEarned());
		_actionButton->SetCurrencyPtrs(displayPanelModel->GetCurrency(), profileModel->GetTotalEarned());
		_actionButton->GetModel()->SetTotalTapsPtr(profileModel->GetTotalTaps());
		_orbSpawner->SetCurrencyPtrs(displayPanelModel->GetCurrency(), profileModel->GetTotalEarned());

		upgradesPerSecondPanel->AddElements(
			UpgradesPerSecondPanelData,
			displayPanelModel->GetCurrency(),
			profileModel->GetTotalSpent(),
			displayPanelModel->GetCurrencyPerSecond(),
			L"/s"
		);

		upgradesPerClickPanel->AddElements(
			UpgradesPerClickPanelData,
			displayPanelModel->GetCurrency(),
			profileModel->GetTotalSpent(),
			_actionButton->GetTapValue(),
			L"/tap"
		);

		auto audioSource = Engine::Get()->Audio()->CreateSource();
		Engine::Get()->Audio()->PlaySource(audioSource, Engine::Get()->Resources()->GetSound("MainTheme"), true);
		Engine::Get()->Audio()->SetGain(.35f);
	}
	
	void MainGame::DeInit()
	{
	}
	
	void MainGame::Update(float dt)
	{
		if (_profileButton->Released() || !Engine::Get()->Input()->IsKeyDown(DirectInputKey::Escape))
		{
			_profileButton->SetScale(.66f, .66f);
		}

		if (_profileButton->Pressed() || Engine::Get()->Input()->IsKeyDown(DirectInputKey::Escape))
		{
			_profileButton->SetScale(.675f, .675f);
			_profile->SetActive(true);
		}
	}
}