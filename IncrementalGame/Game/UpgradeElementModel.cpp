#include "UpgradeElementModel.h"
#include <MainEngine.h>
#include <StringUtils.h>

using namespace IncrementalEngine;

namespace MagicIdle 
{
	void UpgradeElementModel::SetValues(
		std::wstring& name, 
		Formula& costFormula, 
		Formula& upgradeFormula
	)
	{
		_name = name;
		WStringAsCHAR_ptr(name, std::string nameString);

		_level = 0;
		if (Engine::Get()->Storage()->HasKey(nameString + "_level"))
		{
			_level = Engine::Get()->Storage()->GetInt(nameString + "_level");
		}

		_upgradeFormula = upgradeFormula;
		_costFormula = costFormula;
	}
	
	void UpgradeElementModel::LevelUp()
	{
		_level++;
		WStringAsCHAR_ptr(_name, std::string nameString);
		Engine::Get()->Storage()->SaveInt(_level, nameString + "_level");
	}

	bool UpgradeElementModel::IsAvailable(KmbNumber& currency)
	{
		KmbNumber cost = _costFormula.Calculate(_level);
		return currency >= cost;
	}
	
	std::wstring& UpgradeElementModel::GetName()
	{
		return _name;
	}
	
	int UpgradeElementModel::GetLevel()
	{
		return _level;
	}
	
	KmbNumber UpgradeElementModel::GetCost()
	{
		return _costFormula.Calculate(_level);
	}
	
	KmbNumber UpgradeElementModel::GetUpgrade()
	{
		return _upgradeFormula.Calculate(_level);
	}
}