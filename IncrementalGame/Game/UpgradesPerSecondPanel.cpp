#include "UpgradesPerSecondPanel.h"
#include <MainEngine.h>

namespace MagicIdle 
{
	void UpgradesPerSecondPanel::Init()
	{
		SetScale(.67f, .67f);
		SetTexture(Engine::Get()->Resources()->GetTexture("UpgradesPerSecondPanelBackground"));
		SetValues(3, 25);
		
		_panelButton = Engine::Get()->Scene()->Create<Button>();
		_panelButton->SetParent(this);
		_panelButton->SetTexture(Engine::Get()->Resources()->GetTexture("UpgradesPerSecondPanelButton"));
		_panelButton->SetPosition(
			GetLocalBounds().width() * -.5f + 100, 
			GetLocalBounds().height() * -.5f + 35
		);

		auto kmb = KmbNumber::Zero;

		auto element = Engine::Get()->Scene()->Create<UpgradeElement>();
		element->SetValues(L"Sapphire amulet", kmb, kmb, 0);
		AddElement(element);
		
		kmb += 500;
		
		element = Engine::Get()->Scene()->Create<UpgradeElement>();
		element->SetValues(L"Sapphire amulet", kmb, kmb, 0);
		AddElement(element);
		
		kmb += 500;
		
		element = Engine::Get()->Scene()->Create<UpgradeElement>();
		element->SetValues(L"Sapphire amulet", kmb, kmb, 0);
		AddElement(element);
		
		kmb += 500;
		
		element = Engine::Get()->Scene()->Create<UpgradeElement>();
		element->SetValues(L"Sapphire amulet", kmb, kmb, 0);
		AddElement(element);
		
		kmb += 500;
		
		element = Engine::Get()->Scene()->Create<UpgradeElement>();
		element->SetValues(L"Sapphire amulet", kmb, kmb, 0);
		AddElement(element);
		
		kmb += 500;
		
		element = Engine::Get()->Scene()->Create<UpgradeElement>();
		element->SetValues(L"Sapphire amulet", kmb, kmb, 0);
		AddElement(element);
		
		kmb += 500;
		
		element = Engine::Get()->Scene()->Create<UpgradeElement>();
		element->SetValues(L"Sapphire amulet", kmb, kmb, 0);
		AddElement(element);
		
		kmb += 500;
		
		element = Engine::Get()->Scene()->Create<UpgradeElement>();
		element->SetValues(L"Sapphire amulet", kmb, kmb, 0);
		AddElement(element);
		
		kmb += 500;
	}
	
	Button* UpgradesPerSecondPanel::GetPanelButton()
	{
		return _panelButton;
	}
}