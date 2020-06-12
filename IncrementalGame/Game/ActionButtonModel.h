#pragma once

#include <KmbNumber.h>

using namespace IncrementalEngine;

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

		void SetTotalTapsPtr(KmbNumber* totalTapsPtr);

	private:
		KmbNumber _tapValue = KmbNumber::Zero;
		KmbNumber* _totalTapsPtr;
	};
}