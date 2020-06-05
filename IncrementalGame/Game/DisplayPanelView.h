#pragma once

#include <Sprite.h>
#include <Text.h>

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class DisplayPanelView : public Sprite
	{
	public:
		virtual void Init() override;
		
		void SetCurrency(std::wstring& value);
		void SetCurrencyPerSecond(std::wstring& value);
		void UpdateValues(std::wstring& currency, std::wstring& earningsPerSecond);

	private:
		Text* _currencyText;
		Text* _currencyPerSecondText;
	};
}
