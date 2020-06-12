#pragma once

#include <vector>
#include "UpgradeData.h"

#define UpgradesPerSecondPanelData vector<UpgradeData>\
		{\
			UpgradeData(L"Willow", Formula(.1f, 0, 0), Formula(15.f, 1.f, 1.6f)),\
			UpgradeData(L"Book", Formula(1.f, 0, 0), Formula(100.f, 15.f, 1.2f)),\
			UpgradeData(L"Enchanted willow", Formula(8.f, 0, 0), Formula(1100.f, 100.f, 1.6f)),\
			UpgradeData(L"Oak wand", Formula(47.f, 0, 0), Formula(12000.f, 1100.f, 1.6f)),\
			UpgradeData(L"Ruby ring", Formula(260.f, 0, 0), Formula(130000.f, 12000.f, 1.6f)),\
			UpgradeData(L"Oak staff", Formula(1400.f, 0, 0), Formula(1400000.f, 130000.f, 1.6f)),\
			UpgradeData(L"Fire spells", Formula(7800.f, 0, 0), Formula(20000000.f, 1400000.f, 1.6f)),\
			UpgradeData(L"Fire staff", Formula(44000.f, 0, 0), Formula(330000000.f, 20000000.f, 1.6f)),\
			UpgradeData(L"Yellow potion", Formula(260000.f, 0, 0), Formula(5100000000.f, 330000000.f, 1.6f)),\
			UpgradeData(L"Regeneration spells", Formula(1600000.f, 0, 0), Formula(75000000000.f, 5100000000.f, 1.6f)),\
			UpgradeData(L"Skull", Formula(10000000.f, 0, 0), Formula(1000000000000.f, 75000000000.f, 1.6f)),\
			UpgradeData(L"Dark spells", Formula(65000000.f, 0, 0), Formula(14000000000000.f, 1000000000000.f, 1.6f)),\
			UpgradeData(L"Green potion", Formula(430000000.f, 0, 0), Formula(170000000000000.f, 14000000000000.f, 1.6f)),\
			UpgradeData(L"Sapphire amulet", Formula(2900000000.f, 0, 0), Formula(2100000000000000.f, 170000000000000.f, 1.6f))\
		}