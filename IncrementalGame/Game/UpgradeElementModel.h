#pragma once

#include <string>
#include "Formula.h"

namespace MagicIdle 
{
	class UpgradeElementModel
	{
	public:
		void SetValues(
			std::wstring& name,
			Formula& costFormula,
			Formula& upgradeFormula
		);

		void LevelUp();
		bool IsAvailable(KmbNumber& currency);

		std::wstring& GetName();
		int GetLevel();

		KmbNumber GetCost();
		KmbNumber GetUpgrade();

	private:
		int _level;
		std::wstring _name;

		Formula _costFormula;
		Formula _upgradeFormula;
	};
}
