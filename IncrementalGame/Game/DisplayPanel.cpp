#include "DisplayPanel.h"
#include <MainEngine.h>

namespace MagicIdle 
{
	void DisplayPanel::Init()
	{
		SetTexture(Engine::Get()->Resources()->GetTexture("DisplayPanelBackground"));

		_currencyText = Engine::Get()->Scene()->Create<Text>();
		_currencyText->SetParent(this);

		_currencyText->SetFont(L"Edo SZ");
		_currencyText->SetPosition(20, 20);
		_currencyText->SetTextColor(255, 255, 255);
		_currencyText->SetFontSize(98);
		_currencyText->SetFontAlignment(Text::BOTTOM_RIGHT);
		_currencyText->SetText(L"999.99W");

		_currencyPerSecondText = Engine::Get()->Scene()->Create<Text>();
		_currencyPerSecondText->SetParent(this);

		_currencyPerSecondText->SetFont(L"Edo SZ");
		_currencyPerSecondText->SetPosition(164, 20);
		_currencyPerSecondText->SetTextColor(255, 255, 255);
		_currencyPerSecondText->SetFontSize(35.5f);
		_currencyPerSecondText->SetText(L"999.99W/S");

	}
	
	void DisplayPanel::Update()
	{
		Sprite::Update();
	}
}