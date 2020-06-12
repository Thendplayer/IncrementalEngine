#include "UpgradeElementView.h"
#include <MainEngine.h>
#include <StringUtils.h>

namespace MagicIdle 
{
	void UpgradeElementView::Init()
	{
		SetTexture(Engine::Get()->Resources()->GetTexture("UpgradeElementBackground"));

		_foreground = Engine::Get()->Scene()->Create<Sprite>(this);
		_foreground->SetTexture(Engine::Get()->Resources()->GetTexture("UpgradeForeground"));
		_foreground->SetPosition(0, 0);
		_foreground->SetActive(false);

		_sprite = Engine::Get()->Scene()->Create<Sprite>(this);
		_sprite->SetTexture(Engine::Get()->Resources()->GetTexture("Sapphire amulet"));
		_sprite->SetScale(1.2f, 1.2f);
		_sprite->SetPosition(-240, 5);

		_nameText = Engine::Get()->Scene()->Create<Text>(this);
		_nameText->SetFontAlignment(Text::TOP_LEFT);
		_nameText->SetFontSize(48);
		_nameText->SetTextColor(88, 62, 62);
		_nameText->SetText(L"UNKNOWN UPGRADE");
		_nameText->SetFont(L"Edo SZ");
		_nameText->SetPosition(-130, -70);

		_upgradeText = Engine::Get()->Scene()->Create<Text>(this);
		_upgradeText->SetFontAlignment(Text::CENTER_LEFT);
		_upgradeText->SetFontSize(32);
		_upgradeText->SetTextColor(128, 92, 92);
		_upgradeText->SetText(L"999.99W/s");
		_upgradeText->SetFont(L"Edo SZ");
		_upgradeText->SetPosition(-130, 5);

		_levelText = Engine::Get()->Scene()->Create<Text>(this);
		_levelText->SetFontAlignment(Text::BOTTOM_LEFT);
		_levelText->SetFontSize(32);
		_levelText->SetTextColor(88, 62, 62);
		_levelText->SetText(L"Lv. 999W");
		_levelText->SetFont(L"Edo SZ");
		_levelText->SetPosition(-130, 75);

		_costText = Engine::Get()->Scene()->Create<Text>(this);
		_costText->SetFontAlignment(Text::BOTTOM_RIGHT);
		_costText->SetFontSize(42);
		_costText->SetTextColor(88, 62, 62);
		_costText->SetText(L"999.99W");
		_costText->SetFont(L"Edo SZ");
		_costText->SetPosition(290, 70);
	}

	void UpgradeElementView::Update(float dt)
	{
		Button::Update(dt);

		if (Pressed())
		{
			SetScale(1.03f, 1.03f);
		}

		if (Released())
		{
			SetScale(1, 1);
		}
	}

	void UpgradeElementView::SetAvailability(bool available)
	{
		_foreground->SetActive(!available);
	}

	void UpgradeElementView::SetName(std::wstring& name)
	{
		_nameText->SetText(name);
		WStringAsCHAR_ptr(name, std::string nameString);
		_sprite->SetTexture(Engine::Get()->Resources()->GetTexture(nameString));
	}
	
	void UpgradeElementView::SetValues(
		int level, 
		std::wstring& cost, 
		std::wstring& upgrade
	)
	{
		_levelText->SetText(L"Lv. " + std::to_wstring(level));
		_costText->SetText(cost);
		_upgradeText->SetText(upgrade);
	}
}