#include "ActionButtonModel.h"
#include <MainEngine.h>

using namespace IncrementalEngine;

namespace MagicIdle
{
	ActionButtonModel::ActionButtonModel()
	{
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
	}

	ActionButtonModel::~ActionButtonModel()
	{
		Engine::Get()->Storage()->SaveFloat(_tapValue.FirstDigits, "TapValue_FirstDigits");
		Engine::Get()->Storage()->SaveFloat(_tapValue.TrailingPercentage, "TapValue_TrailingPercentage");
		Engine::Get()->Storage()->SaveInt(_tapValue.Exponent, "TapValue_Exponent");
	}
	
	KmbNumber& ActionButtonModel::Tap()
	{
		_totalTapsPtr->Add(1);
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
	
	void ActionButtonModel::SetTotalTapsPtr(KmbNumber* totalTapsPtr)
	{
		_totalTapsPtr = totalTapsPtr;
	}
}