#pragma once

#include "KmbNumber.h"

namespace MagicIdle 
{
	class ActionButtonModel
	{
	public:
		ActionButtonModel();
		virtual ~ActionButtonModel();
		
		KmbNumber& Tap();
		void AddTapValue(KmbNumber& value);

		KmbNumber* GetTapValue();

	private:
		KmbNumber _taps = KmbNumber::Zero;
		KmbNumber _tapValue = KmbNumber::Zero;
	};
}