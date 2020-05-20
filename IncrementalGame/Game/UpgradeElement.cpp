#include "UpgradeElement.h"
#include <MainEngine.h>
#include <StringUtils.h>

namespace MagicIdle 
{
	void UpgradeElement::Init()
	{
		SetTexture(Engine::Get()->Resources()->GetTexture("UpgradeElementBackground"));
		SetScale(.66f, .66f);

		_foreground = Engine::Get()->Scene()->Create<Sprite>();
		_foreground->SetParent(this);
		_foreground->SetTexture(Engine::Get()->Resources()->GetTexture("UpgradeForeground"));
		_foreground->SetPosition(0, 0);
		_foreground->SetActive(false);

		_name = Engine::Get()->Scene()->Create<Text>();
		_name->SetParent(this);
		_name->SetFontAlignment(Text::TOP_LEFT);
		_name->SetFontSize(48);
		_name->SetTextColor(88, 62, 62);
		_name->SetText(L"UNKNOWN UPGRADE");
		_name->SetFont(L"Edo SZ");
		_name->SetPosition(-90, -45);

		_upgrade = Engine::Get()->Scene()->Create<Text>();
		_upgrade->SetParent(this);
		_upgrade->SetFontAlignment(Text::CENTER_LEFT);
		_upgrade->SetFontSize(32);
		_upgrade->SetTextColor(128, 92, 92);
		_upgrade->SetText(L"999.99W/s");
		_upgrade->SetFont(L"Edo SZ");
		_upgrade->SetPosition(-90, 0);

		_level = Engine::Get()->Scene()->Create<Text>();
		_level->SetParent(this);
		_level->SetFontAlignment(Text::BOTTOM_LEFT);
		_level->SetFontSize(32);
		_level->SetTextColor(88, 62, 62);
		_level->SetText(L"Lv. 999W");
		_level->SetFont(L"Edo SZ");
		_level->SetPosition(-90, 50);

		_cost = Engine::Get()->Scene()->Create<Text>();
		_cost->SetParent(this);
		_cost->SetFontAlignment(Text::BOTTOM_RIGHT);
		_cost->SetFontSize(42);
		_cost->SetTextColor(88, 62, 62);
		_cost->SetText(L"999.99W");
		_cost->SetFont(L"Edo SZ");
		_cost->SetPosition(195, 47);
	}
	
	void UpgradeElement::Update()
	{
		Button::Update();
	}
	
	void UpgradeElement::SetValues(
		std::wstring name, 
		KmbNumber& upgrade, 
		KmbNumber& cost, 
		int level
	)
	{
		_name->SetText(name);
		_upgrade->SetText(upgrade.ToString());
		_cost->SetText(cost.ToString());
		_level->SetText(L"Lv. " + level);

		WStringAsCHAR_ptr(name, std::string nameString);
		_sprite->SetTexture(Engine::Get()->Resources()->GetTexture(nameString));

		_costValue = cost;
	}
	
	bool UpgradeElement::SetAvailability(KmbNumber& currency)
	{
		bool available = currency >= _costValue;
		_foreground->SetActive(available);
		return available;
	}
}