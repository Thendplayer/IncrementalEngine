#include "Formula.h"

namespace MagicIdle 
{
	Formula::Formula()
		: _initialValue(0),
		_multiplier(0),
		_exponent(0)
	{
	}
	
	Formula::Formula(
		KmbNumber initialValue, 
		KmbNumber multiplier, 
		float exponent
	) : _initialValue(initialValue),
		_multiplier(multiplier),
		_exponent(exponent)
	{
	}
	
	KmbNumber Formula::Calculate(int x)
	{
		KmbNumber result = _initialValue + _multiplier * std::pow(x, _exponent);
		return result;
	}
	
	void Formula::operator=(Formula& other)
	{
		_initialValue = other._initialValue;
		_multiplier = other._multiplier;
		_exponent = other._exponent;
	}
}
