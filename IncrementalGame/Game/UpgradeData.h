#pragma once

#include <string>
#include "Formula.h"

namespace MagicIdle 
{
	struct UpgradeData 
	{
		std::wstring Name; 
		Formula Upgrade; 
		Formula Cost;

		UpgradeData(std::wstring name, Formula upgrade, Formula cost)
		{
			Name = name;
			Upgrade = upgrade;
			Cost = cost;
		};
	};
}