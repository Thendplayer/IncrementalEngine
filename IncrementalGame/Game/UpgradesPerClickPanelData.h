#pragma once

#include <vector>
#include "UpgradeData.h"

#define UpgradesPerClickPanelData vector<UpgradeData>\
		{\
			UpgradeData(L"Wool", Formula(1.f, 0, 0), Formula(100.f, 1.f, 1.6f)),\
			UpgradeData(L"Magic feather", Formula(10.f, 0, 0), Formula(500.f, 100.f, 1.6f)),\
			UpgradeData(L"Pitchfork", Formula(100.f, 0, 0), Formula(10000.f, 500.f, 1.6f)),\
			UpgradeData(L"Mace", Formula(1000.f, 0, 0), Formula(100000.f, 10000.f, 1.6f)),\
			UpgradeData(L"Bomb", Formula(10000.f, 0, 0), Formula(10000000.f, 100000.f, 1.6f)),\
			UpgradeData(L"Card club", Formula(100000.f, 0, 0), Formula(100000000.f, 10000000.f, 1.6f))\
		}