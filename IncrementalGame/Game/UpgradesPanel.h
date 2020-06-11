#pragma once

#include "Panel.h"
#include "UpgradeElementMediator.h"
#include "UpgradeData.h"

using namespace IncrementalEngine;

namespace MagicIdle
{
	class UpgradesPanel : public Panel
	{
	public:
		virtual void Init() override;
		void AddElements(
			std::vector<UpgradeData> data, 
			KmbNumber* currency, 
			KmbNumber* totalSpent,
			KmbNumber* valueToUpgrade,
			std::wstring upgradeSuffix
		);
	};
}