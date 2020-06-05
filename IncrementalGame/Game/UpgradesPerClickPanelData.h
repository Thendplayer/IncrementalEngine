#pragma once

#include <vector>
#include "UpgradeData.h"

#define UpgradesPerClickPanelData vector<UpgradeData>\
		{\
			UpgradeData(L"Wool", Formula(15.f, 1.f, 2), Formula(15.f, 1.f, 2)),\
			UpgradeData(L"Magic feather", Formula(100.f, 1.f, 2), Formula(100.f, 1.f, 2)),\
			UpgradeData(L"Pitchfork", Formula(1100.f, 1.f, 2), Formula(1100.f, 1.f, 2)),\
			UpgradeData(L"Mace", Formula(12000.f, 1.f, 2), Formula(12000.f, 1.f, 2)),\
			UpgradeData(L"Bomb", Formula(130000.f, 1.f, 2), Formula(130000.f, 1.f, 2)),\
			UpgradeData(L"Card club", Formula(1400000.f, 1.f, 2), Formula(1400000.f, 1.f, 2))\
		}