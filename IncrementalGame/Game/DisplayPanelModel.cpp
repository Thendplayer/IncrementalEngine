#include "DisplayPanelModel.h"
#include <MainEngine.h>

using namespace IncrementalEngine;

namespace MagicIdle 
{
	DisplayPanelModel::DisplayPanelModel()
	{
		auto currency = KmbNumber(
			Engine::Get()->Storage()->GetFloat("Currency_FirstDigits"),
			Engine::Get()->Storage()->GetFloat("Currency_TrailingPercentage"),
			Engine::Get()->Storage()->GetInt("Currency_Exponent")
		);

		auto currencyPerSecond = KmbNumber(
			Engine::Get()->Storage()->GetFloat("CurrencyPerSecond_FirstDigits"),
			Engine::Get()->Storage()->GetFloat("CurrencyPerSecond_TrailingPercentage"),
			Engine::Get()->Storage()->GetInt("CurrencyPerSecond_Exponent")
		);

		_currency = currency;
		_currencyPerSecond = currencyPerSecond;
	}
	
	DisplayPanelModel::~DisplayPanelModel()
	{
		Engine::Get()->Storage()->SaveFloat(_currency.FirstDigits, "Currency_FirstDigits");
		Engine::Get()->Storage()->SaveFloat(_currency.TrailingPercentage, "Currency_TrailingPercentage");
		Engine::Get()->Storage()->SaveInt(_currency.Exponent, "Currency_Exponent");

		Engine::Get()->Storage()->SaveFloat(_currencyPerSecond.FirstDigits, "CurrencyPerSecond_FirstDigits");
		Engine::Get()->Storage()->SaveFloat(_currencyPerSecond.TrailingPercentage, "CurrencyPerSecond_TrailingPercentage");
		Engine::Get()->Storage()->SaveInt(_currencyPerSecond.Exponent, "CurrencyPerSecond_Exponent");
	}
	
	KmbNumber* DisplayPanelModel::GetCurrency()
	{
		return &_currency;
	}
	
	KmbNumber* DisplayPanelModel::GetCurrencyPerSecond()
	{
		return &_currencyPerSecond;
	}
}