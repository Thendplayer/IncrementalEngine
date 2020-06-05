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

	void UpgradesPanel::AddElements(
		std::vector<UpgradeData> data, 
		KmbNumber* currency, 
		KmbNumber* valueToUpgrade
	)
	{
		for (int i = 0; i < data.size(); i++)
		{
			auto element = Engine::Get()->Scene()->Create<UpgradeElementMediator>();
			element->SetValues(data[i].Name, data[i].Upgrade, data[i].Cost);
			element->SetCurrencyPtr(currency);
			element->SetValueToUpgradePtr(valueToUpgrade);
			AddElement(element->GetView());
		}
	}
}