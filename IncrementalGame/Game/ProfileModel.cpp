#include "ProfileModel.h"
#include <MainEngine.h>

namespace MagicIdle 
{
	ProfileModel::ProfileModel()
	{
		auto totalEarned = KmbNumber(
			Engine::Get()->Storage()->GetFloat("TotalEarned_FirstDigits"),
			Engine::Get()->Storage()->GetFloat("TotalEarned_TrailingPercentage"),
			Engine::Get()->Storage()->GetInt("TotalEarned_Exponent")
		);

		auto totalSpent = KmbNumber(
			Engine::Get()->Storage()->GetFloat("TotalSpent_FirstDigits"),
			Engine::Get()->Storage()->GetFloat("TotalSpent_TrailingPercentage"),
			Engine::Get()->Storage()->GetInt("TotalSpent_Exponent")
		);

		auto totalTaps = KmbNumber(
			Engine::Get()->Storage()->GetFloat("TotalTaps_FirstDigits"),
			Engine::Get()->Storage()->GetFloat("TotalTaps_TrailingPercentage"),
			Engine::Get()->Storage()->GetInt("TotalTaps_Exponent")
		);

		_totalEarned = totalEarned;
		_totalSpent = totalSpent;
		_totalTaps = totalTaps;
	}

	ProfileModel::~ProfileModel()
	{
		Engine::Get()->Storage()->SaveFloat(_totalEarned.FirstDigits, "TotalEarned_FirstDigits");
		Engine::Get()->Storage()->SaveFloat(_totalEarned.TrailingPercentage, "TotalEarned_TrailingPercentage");
		Engine::Get()->Storage()->SaveInt(_totalEarned.Exponent, "TotalEarned_Exponent");

		Engine::Get()->Storage()->SaveFloat(_totalSpent.FirstDigits, "TotalSpent_FirstDigits");
		Engine::Get()->Storage()->SaveFloat(_totalSpent.TrailingPercentage, "TotalSpent_TrailingPercentage");
		Engine::Get()->Storage()->SaveInt(_totalSpent.Exponent, "TotalSpent_Exponent");

		Engine::Get()->Storage()->SaveFloat(_totalTaps.FirstDigits, "TotalTaps_FirstDigits");
		Engine::Get()->Storage()->SaveFloat(_totalTaps.TrailingPercentage, "TotalTaps_TrailingPercentage");
		Engine::Get()->Storage()->SaveInt(_totalTaps.Exponent, "TotalTaps_Exponent");
	}
	
	KmbNumber* ProfileModel::GetTotalEarned()
	{
		return &_totalEarned;
	}
	
	KmbNumber* ProfileModel::GetTotalSpent()
	{
		return &_totalSpent;
	}
	
	KmbNumber* ProfileModel::GetTotalTaps()
	{
		return &_totalTaps;
	}
}