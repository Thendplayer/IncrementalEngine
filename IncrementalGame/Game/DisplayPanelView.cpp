#include "DisplayPanelView.h"
#include <MainEngine.h>

namespace MagicIdle 
{
	void DisplayPanelView::Init()
	{
		SetTexture(Engine::Get()->Resources()->GetTexture("DisplayPanelBackground"));

		_currencyText = Engine::Get()->Scene()->Create<Text>(this);

		_currencyText->SetFont(L"Edo SZ");
		_currencyText->SetPosition(20, 20);
		_currencyText->SetTextColor(255, 255, 255);
		_currencyText->SetFontSize(98);
		_currencyText->SetFontAlignment(Text::BOTTOM_RIGHT);
		_currencyText->SetText(L"999.99W");

		_currencyPerSecondText = Engine::Get()->Scene()->Create<Text>(this);

		_currencyPerSecondText->SetFont(L"Edo SZ");
		_currencyPerSecondText->SetPosition(246, 30);
		_currencyPerSecondText->SetTextColor(255, 255, 255);
		_currencyPerSecondText->SetFontSize(35.5f);
		_currencyPerSecondText->SetText(L"999.99W/S");

	}

	void DisplayPanelView::UpdateValues(std::wstring& currency, std::wstring& earningsPerSecond)
	{
		_currencyText->SetText(currency);
		_currencyPerSecondText->SetText(earningsPerSecond + L"/S");
	}
	
	void DisplayPanelView::SetCurrency(std::wstring& value)
	{
		_currencyText->SetText(value);
	}
	
	void DisplayPanelView::SetCurrencyPerSecond(std::wstring& value)
	{
		_currencyPerSecondText->SetText(value + L"/S");
	}
}