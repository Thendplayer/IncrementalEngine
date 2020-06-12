#pragma once

#include <KmbNumber.h>

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class ProfileModel
	{
	public:
		ProfileModel();
		virtual ~ProfileModel();

		KmbNumber* GetTotalEarned();
		KmbNumber* GetTotalSpent();
		KmbNumber* GetTotalTaps();

	private:
		KmbNumber _totalEarned = KmbNumber::Zero;
		KmbNumber _totalSpent = KmbNumber::Zero;
		KmbNumber _totalTaps = KmbNumber::Zero;
	};
}