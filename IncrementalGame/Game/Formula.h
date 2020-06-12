#pragma once

#include <string>
#include <cmath>
#include <KmbNumber.h>

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class Formula
	{
	public:
		Formula();
		Formula(KmbNumber initialValue, KmbNumber multiplier, float exponent);
		KmbNumber Calculate(int x);

		void operator =(Formula& other);

	private:
		KmbNumber _initialValue = 0;
		KmbNumber _multiplier = 0;
		float _exponent = 0;
	};

}