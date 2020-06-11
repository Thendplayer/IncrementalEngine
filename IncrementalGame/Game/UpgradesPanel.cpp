#include "UpgradesPanel.h"
#include <MainEngine.h>

namespace MagicIdle 
{
	void UpgradesPanel::Init()
	{
		SetScale(.67f, .67f);
		SetPosition(-315, -205);
		SetTexture(Engine::Get()->Resources()->GetTexture("UpgradesPerSecondPanelBackground"));
		SetValues(3, 25);

		_upButton = Engine::Get()->Scene()->Create<Button>(this);
		_upButton->SetTexture(Engine::Get()->Resources()->GetTexture("PanelUpButton"));
		_upButton->SetPosition(300, 300);

		_downButton = Engine::Get()->Scene()->Create<Button>(this);
		_downButton->SetTexture(Engine::Get()->Resources()->GetTexture("PanelDownButton"));
		_downButton->SetPosition(170, 300);
	}

	void UpgradesPanel::Update(float dt)
	{
		Panel::Update(dt);

		if (_upButton->Pressed()) 
		{
			Engine::Get()->Audio()->Play(Engine::Get()->Resources()->GetSound("ButtonSound"));
		}

		if (_downButton->Pressed())
		{
			Engine::Get()->Audio()->Play(Engine::Get()->Resources()->GetSound("ButtonSound"));
		}
	}

	void UpgradesPanel::AddElements(
		std::vector<UpgradeData> data, 
		KmbNumber* currency, 
		KmbNumber* totalSpent, 
		KmbNumber* valueToUpgrade,
		std::wstring upgradeSuffix
	)
	{
		for (int i = 0; i < data.size(); i++)
		{
			auto element = Engine::Get()->Scene()->Create<UpgradeElementMediator>();
			element->SetValues(data[i].Name, data[i].Upgrade, data[i].Cost, upgradeSuffix);
			element->SetCurrencyPtrs(currency, totalSpent);
			element->SetValueToUpgradePtr(valueToUpgrade);
			AddElement(element->GetView());
		}
	}
}