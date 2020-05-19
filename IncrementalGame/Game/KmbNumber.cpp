#include "KmbNumber.h"
#include <iomanip>
#include <sstream>

namespace MagicIdle 
{
	KmbNumber KmbNumber::Zero = KmbNumber(0, 0, 0);

	KmbNumber::KmbNumber(const KmbNumber& kmbNumber)
	{
		_firstDigits = kmbNumber._firstDigits;
		_trailingPercentage = kmbNumber._trailingPercentage;
		_exponent = kmbNumber._exponent;
	}

	KmbNumber::KmbNumber(float firstDigits, float trailing, int exponent)
	{
		_firstDigits = firstDigits;
		_trailingPercentage = trailing;
		_exponent = exponent;
	}

	KmbNumber::KmbNumber(float number, int exponent)
	{
		auto newKmb = Refactor(number, exponent);

		_firstDigits = newKmb._firstDigits;
		_trailingPercentage = newKmb._trailingPercentage;
		_exponent = newKmb._exponent;
	}

	KmbNumber KmbNumber::operator=(float number1)
	{
		auto newKmb = Zero;
		return newKmb.Refactor(number1, 0);
	}

	double KmbNumber::operator=(KmbNumber number1)
	{
		double castedNumber = GetRawNumber() * std::pow(10, _exponent);
		return castedNumber;
	}

	KmbNumber KmbNumber::RoundUp(KmbNumber& number)
	{
		if (number._trailingPercentage > 0)
		{
			number._trailingPercentage = (float)(std::round(number._trailingPercentage * std::pow(10, 2))) / std::pow(10, 2);
			number._firstDigits += 1;
			return number;
		}

		return number;
	}

	std::string KmbNumber::ToString()
	{
		SetSuffix();

		if (_firstDigits == 0)
		{
			std::stringstream stream;
			stream << std::fixed << std::setprecision(DECIMALS_TO_SHOW) << GetStringTrailingPercentage();
			return stream.str() + suffix;
		}

		if (_exponent == 0)
		{
			return std::to_string(_firstDigits);
		}

		std::stringstream stream;
		stream << std::fixed << std::setprecision(DECIMALS_TO_SHOW) << GetStringTrailingPercentage();
		return stream.str() + suffix;
	}

	float KmbNumber::GetStringTrailingPercentage()
	{
		auto trailingPercentage1000 = (_firstDigits + _trailingPercentage) * 1000.0f;
		trailingPercentage1000 = std::floor(trailingPercentage1000);
		auto trailingPercentage = trailingPercentage1000 / 1000;
		return trailingPercentage;
	}

	float KmbNumber::GetRawNumber()
	{
		return _firstDigits + _trailingPercentage;
	}

	float KmbNumber::GetInt()
	{
		return (int)_firstDigits * 
			   (int)std::pow(10, _exponent) + 
			   (int)_trailingPercentage * (int)std::pow(10, _exponent);
	}

	void KmbNumber::SetSuffix()
	{
		std::string suffixArray[] = SUFFIX;
		for (int i = 0; i < suffixArray->size(); i++)
		{
			if (_exponent == i)
			{
				suffix = suffixArray[i];
			}
		}
	}

	KmbNumber KmbNumber::Refactor(float value, int exponent)
	{
		auto trail = std::fmod(value, 1);
		value = value - trail;

		auto result = KmbNumber(value, trail, exponent);
		result = Refactor(result);

		return result;
	}

	KmbNumber KmbNumber::Refactor(KmbNumber number)
	{
		while (number._trailingPercentage < 0)
		{
			number._trailingPercentage = 1 + number._trailingPercentage;
			number._firstDigits -= 1;
		}

		while (number._trailingPercentage >= 1)
		{
			number._trailingPercentage -= 1;
			number._firstDigits++;
		}

		while (number._firstDigits > 999)
		{
			number._trailingPercentage = (number._trailingPercentage / 1000) + std::fmod(number._firstDigits, 1000) / 1000;
			number._firstDigits /= 1000;
			
			auto a = std::trunc(number._firstDigits);
			number._firstDigits = (float)a;
			number._exponent += 3;
		}

		if (number._firstDigits < 1 && number._firstDigits >= 0 && _exponent > 0)
		{
			if (number._firstDigits == 0 && number._trailingPercentage == 0)
			{
				number._exponent = 1;
				return number;
			}

			number._trailingPercentage = number._trailingPercentage * 1000;
			number._exponent -= 3;
			Refactor(number);
		}

		if (number._trailingPercentage >= 1)
		{
			Refactor(number);
		}


		return number;
	}

	KmbNumber KmbNumber::Add(KmbNumber adder)
	{
		if (adder._exponent == _exponent)
		{
			KmbNumber result = KmbNumber(_firstDigits + adder._firstDigits, 
				_trailingPercentage + adder._trailingPercentage, _exponent);
			return Refactor(result);
		}

		if (_exponent > adder._exponent)
		{
			_trailingPercentage = 
				_trailingPercentage + adder._firstDigits * (float)(std::pow(10, -(_exponent - adder._exponent)));
			KmbNumber result = KmbNumber(_firstDigits, _trailingPercentage, _exponent);
			return Refactor(result);
		}

		if (adder._exponent > _exponent)
		{
			adder._trailingPercentage = 
				adder._trailingPercentage + _firstDigits * (float)(std::pow(10, -(adder._exponent - _exponent)));
			KmbNumber result = KmbNumber(adder._firstDigits, adder._trailingPercentage, adder._exponent);
			return Refactor(result);
		}

		return NULL;

	}

	KmbNumber KmbNumber::Subtract(KmbNumber subtractor)
	{
		KmbNumber result = KmbNumber(Zero);

		if (_exponent == subtractor._exponent)
		{
			result._firstDigits = _firstDigits - subtractor._firstDigits;
			result._trailingPercentage = _trailingPercentage - subtractor._trailingPercentage;
			result._exponent = _exponent;
			result = KmbNumber(result._firstDigits, result._trailingPercentage, result._exponent);

			result = Refactor(result);
			return result;
		}

		auto exponentDif = _exponent - subtractor._exponent;

		auto value1 = _firstDigits + _trailingPercentage;
		auto value2 = subtractor._firstDigits + subtractor._trailingPercentage;
		if (exponentDif > MAXFLOATEXPONENT)
		{
			result = Refactor(*this);
			return result;
		}
		value1 *= (float)(std::pow(10, exponentDif));
		result = Refactor(value1 - value2, _exponent - exponentDif);

		return result;
	}

	KmbNumber KmbNumber::Multiply(KmbNumber multiplier)
	{
		auto firstNumber = _firstDigits + _trailingPercentage;
		auto secondNumber = multiplier._firstDigits + multiplier._trailingPercentage;
		auto resultFloat = firstNumber * secondNumber;
		auto resultExponents = _exponent + multiplier._exponent;

		auto result = Refactor(resultFloat, resultExponents);
		return result;

	}

	KmbNumber KmbNumber::Divide(KmbNumber divider)
	{
		auto firstNumber = _firstDigits + _trailingPercentage;
		auto secondNumber = divider._firstDigits + divider._trailingPercentage;
		
		if (secondNumber != 0)
		{
			auto resultFloat = firstNumber / secondNumber;
			auto resultExponents = _exponent - divider._exponent;

			auto result = Refactor(resultFloat, resultExponents);
			return result;
		}

		return NULL;
	}

	bool KmbNumber::Equals(KmbNumber other)
	{
		float trailingDiff = std::abs(_trailingPercentage - other._trailingPercentage);
		bool isTralingEqual = trailingDiff > std::numeric_limits<float>::epsilon() && trailingDiff < 0.000000001f;
		
		if (trailingDiff == 0)
		{
			isTralingEqual = true;
		}

		return _exponent == other._exponent && isTralingEqual && _firstDigits == other._firstDigits && suffix == other.suffix;
	}

	KmbNumber operator+(KmbNumber& number1, KmbNumber& number2)
	{
		auto result = KmbNumber(number1);
		return result.Add(number2);

	}

	KmbNumber operator-(KmbNumber& number1, KmbNumber& number2)
	{
		auto result = KmbNumber(number1);
		return result.Subtract(number2);

	}

	KmbNumber operator*(KmbNumber& number1, KmbNumber& number2)
	{
		auto result = KmbNumber(number1);
		return result.Multiply(number2);
	}

	KmbNumber operator/(KmbNumber& number1, KmbNumber& number2)
	{
		auto result = KmbNumber(number1);
		return result.Divide(number2);
	}

	bool operator<(KmbNumber& number1, KmbNumber& number2)
	{
		auto number1Refactored = number1.Refactor(number1);
		auto number2Refactored = number2.Refactor(number2);

		if (number1Refactored._firstDigits >= 0 && number2Refactored._firstDigits < 0)
		{
			return false;
		}
		if (number1Refactored._trailingPercentage >= 0 && number2Refactored._trailingPercentage < 0)
		{
			return false;
		}

		if (number1Refactored._exponent < number2Refactored._exponent)
		{
			return true;
		}
		if (number1Refactored._exponent == number2Refactored._exponent)
		{
			if (number1Refactored._firstDigits < number2Refactored._firstDigits)
			{
				return true;
			}
			if (number1Refactored._firstDigits == number2Refactored._firstDigits)
			{
				if (number1Refactored._trailingPercentage < number2Refactored._trailingPercentage)
				{
					return true;
				}
			}
		}

		return false;

	}

	bool operator<=(KmbNumber& number1, KmbNumber& number2)
	{
		auto number1Refactored = number1.Refactor(number1);
		auto number2Refactored = number2.Refactor(number2);

		if (number1Refactored._firstDigits >= 0 && number2Refactored._firstDigits < 0)
		{
			return false;
		}

		if (number1Refactored._trailingPercentage >= 0 && number2Refactored._trailingPercentage < 0)
		{
			return false;
		}

		if (number1Refactored._exponent < number2Refactored._exponent)
		{
			return true;
		}
		if (number1Refactored._exponent == number2Refactored._exponent)
		{
			if (number1Refactored._firstDigits < number2Refactored._firstDigits)
			{
				return true;
			}
			if (number1Refactored._firstDigits == number2Refactored._firstDigits)
			{
				if (number1Refactored._trailingPercentage < number2Refactored._trailingPercentage)
				{
					return true;
				}
			}
		}

		return number1.Equals(number2);

	}
	
	bool operator>(KmbNumber& number1, KmbNumber& number2)
	{
		auto number1Refactored = number1.Refactor(number1);
		auto number2Refactored = number2.Refactor(number2);

		if (number1Refactored._firstDigits < 0 && number2Refactored._firstDigits >= 0)
		{
			return false;
		}
		if (number1Refactored._trailingPercentage < 0 && number2Refactored._trailingPercentage >= 0)
		{
			return false;
		}
		if (number1Refactored._firstDigits < 0 && number2Refactored._firstDigits >= 0)
		{
			return false;
		}
		if (number1Refactored._trailingPercentage < 0 && number2Refactored._trailingPercentage >= 0)
		{
			return false;
		}
		if (number1Refactored._exponent > number2Refactored._exponent)
		{
			return true;
		}
		if (number1Refactored._exponent == number2Refactored._exponent)
		{
			if (number1Refactored._firstDigits > number2Refactored._firstDigits)
			{
				return true;
			}
			if (number1Refactored._firstDigits == number2Refactored._firstDigits)
			{
				if (number1Refactored._trailingPercentage > number2Refactored._trailingPercentage)
				{
					return true;
				}
			}
		}

		return false;

	}
	
	bool operator>=(KmbNumber& number1, KmbNumber& number2)
	{
		auto number1Refactored = number1.Refactor(number1);
		auto number2Refactored = number2.Refactor(number2);

		if (number1Refactored._firstDigits < 0 && number2Refactored._firstDigits >= 0)
		{
			return false;
		}

		if (number1Refactored._trailingPercentage < 0 && number2Refactored._trailingPercentage >= 0)
		{
			return false;
		}

		if (number1Refactored._firstDigits < 0 && number2Refactored._firstDigits >= 0)
		{
			return false;
		}

		if (number1Refactored._trailingPercentage < 0 && number2Refactored._trailingPercentage >= 0)
		{
			return false;
		}

		if (number1Refactored._exponent > number2Refactored._exponent)
		{
			return true;
		}
		if (number1Refactored._exponent == number2Refactored._exponent)
		{
			if (number1Refactored._firstDigits > number2Refactored._firstDigits)
			{
				return true;
			}
			if (number1Refactored._firstDigits == number2Refactored._firstDigits)
			{
				if (number1Refactored._trailingPercentage > number2Refactored._trailingPercentage)
				{
					return true;
				}
			}
		}

		return number1.Equals(number2);

	}

	bool operator==(KmbNumber& left, KmbNumber& right)
	{
		return left.Equals(right);
	}

	bool operator!=(KmbNumber& left, KmbNumber& right)
	{
		return !left.Equals(right);
	}
}