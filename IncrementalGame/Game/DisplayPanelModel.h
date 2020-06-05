#pragma once

#include "KmbNumber.h"

namespace MagicIdle 
{
	class DisplayPanelModel
	{
	public:
		DisplayPanelModel();
		virtual ~DisplayPanelModel();

		void AddCurrency(KmbNumber& value);
		void SubstractCurrency(KmbNumber& value);

		void AddCurrencyPerSecond(KmbNumber& value);

		KmbNumber* GetCurrency();
		KmbNumber* GetCurrencyPerSecond();

	private:
		KmbNumber _currency = KmbNumber::Zero;
		KmbNumber _currencyPerSecond = KmbNumber::Zero;
	};
}
