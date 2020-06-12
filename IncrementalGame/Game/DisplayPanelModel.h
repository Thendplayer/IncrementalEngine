#pragma once

#include <KmbNumber.h>

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class DisplayPanelModel
	{
	public:
		DisplayPanelModel();
		virtual ~DisplayPanelModel();

		KmbNumber* GetCurrency();
		KmbNumber* GetCurrencyPerSecond();

	private:
		KmbNumber _currency = KmbNumber::Zero;
		KmbNumber _currencyPerSecond = KmbNumber::Zero;
	};
}
