#include "ActionButtonModel.h"
#include <MainEngine.h>

using namespace IncrementalEngine;

namespace MagicIdle
{
	ActionButtonModel::ActionButtonModel()
	{
		auto taps = KmbNumber(
			Engine::Get()->Storage()->GetFloat("Taps_FirstDigits"),
			Engine::Get()->Storage()->GetFloat("Taps_TrailingPercentage"),
			Engine::Get()->Storage()->GetInt("Taps_Exponent")
		);

		auto tapValue = KmbNumber(
			Engine::Get()->Storage()->GetFloat("TapValue_FirstDigits"),
			Engine::Get()->Storage()->GetFloat("TapValue_TrailingPercentage"),
			Engine::Get()->Storage()->GetInt("TapValue_Exponent")
		);

		if (tapValue == KmbNumber::Zero)
		{
			_tapValue = 1;
		}
		else 
		{
			_tapValue = tapValue;
		}

		_taps = taps;
	}

	ActionButtonModel::~ActionButtonModel()
	{
		Engine::Get()->Storage()->SaveFloat(_taps.FirstDigits, "Taps_FirstDigits");
		Engine::Get()->Storage()->SaveFloat(_taps.TrailingPercentage, "Taps_TrailingPercentage");
		Engine::Get()->Storage()->SaveInt(_taps.Exponent, "Taps_Exponent");

		Engine::Get()->Storage()->SaveFloat(_tapValue.FirstDigits, "TapValue_FirstDigits");
		Engine::Get()->Storage()->SaveFloat(_tapValue.TrailingPercentage, "TapValue_TrailingPercentage");
		Engine::Get()->Storage()->SaveInt(_tapValue.Exponent, "TapValue_Exponent");
	}
	
	KmbNumber& ActionButtonModel::Tap()
	{
		_taps += 1;
		return _tapValue;
	}
	
	void ActionButtonModel::AddTapValue(KmbNumber& value)
	{
		_tapValue += value;
	}
	
	KmbNumber* ActionButtonModel::GetTapValue()
	{
		return &_tapValue;
	}
}