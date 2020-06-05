#include "KmbNumber.h"
#include <iomanip>
#include <sstream>

namespace MagicIdle 
{
	KmbNumber KmbNumber::Zero = KmbNumber(0, 0, 0);

	KmbNumber::KmbNumber()
	{
		FirstDigits = 0;
		TrailingPercentage = 0;
		Exponent = 0;
	}

	KmbNumber::KmbNumber(const KmbNumber& kmbNumber)
	{
		FirstDigits = kmbNumber.FirstDigits;
		TrailingPercentage = kmbNumber.TrailingPercentage;
		Exponent = kmbNumber.Exponent;
	}

	KmbNumber::KmbNumber(float firstDigits, float trailing, int exponent)
	{
		FirstDigits = firstDigits;
		TrailingPercentage = trailing;
		Exponent = exponent;
	}

	KmbNumber::KmbNumber(float number, int exponent)
	{
		Refactor(number, exponent);
	}

	void KmbNumber::RoundUp(KmbNumber& number)
	{
		if (number.TrailingPercentage > 0)
		{
			number.TrailingPercentage = (float)(std::round(number.TrailingPercentage * std::pow(10, 2))) / std::pow(10, 2);
			number.FirstDigits += 1;
		}
	}

	std::wstring KmbNumber::ToString()
	{
		SetSuffix();

		if (FirstDigits == 0)
		{
			if (GetStringTrailingPercentage() == 0)
			{
				return L"0" + Suffix;
			}

			std::wstringstream stream;
			stream << std::fixed << std::setprecision(DECIMALS_TO_SHOW) << GetStringTrailingPercentage();
			return stream.str() + Suffix;
		}

		if (Exponent == 0)
		{
			return std::to_wstring((int)FirstDigits);
		}

		std::wstringstream stream;
		stream << std::fixed << std::setprecision(DECIMALS_TO_SHOW) << GetStringTrailingPercentage();
		return stream.str() + Suffix;
	}

	float KmbNumber::GetStringTrailingPercentage()
	{
		auto trailingPercentage1000 = (FirstDigits + TrailingPercentage) * 1000.0f;
		trailingPercentage1000 = std::floor(trailingPercentage1000);
		auto trailingPercentage = trailingPercentage1000 / 1000;
		return trailingPercentage;
	}

	float KmbNumber::GetRawNumber()
	{
		return FirstDigits + TrailingPercentage;
	}

	float KmbNumber::GetInt()
	{
		return ((int)FirstDigits) * 
			   ((int)std::pow(10, Exponent)) + 
			   ((int)TrailingPercentage) * 
			   ((int)std::pow(10, Exponent));
	}

	void KmbNumber::SetSuffix()
	{
		std::wstring suffixArray[] = SUFFIX;
		for (int i = 0; i < sizeof(suffixArray) / sizeof(suffixArray[0]); i++)
		{
			if (Exponent / 3 == i)
			{
				Suffix = suffixArray[i];
			}
		}
	}

	void KmbNumber::Refactor(float value, int exponent)
	{
		auto trail = std::fmod(value, 1);

		FirstDigits = value - trail;
		TrailingPercentage = trail;
		Exponent = exponent;

		Refactor();
	}

	void KmbNumber::Refactor()
	{
		while (TrailingPercentage < 0)
		{
			TrailingPercentage = 1 + TrailingPercentage;
			FirstDigits -= 1;
		}

		while (TrailingPercentage >= 1)
		{
			TrailingPercentage -= 1;
			FirstDigits++;
		}

		while (FirstDigits > 999)
		{
			TrailingPercentage = (TrailingPercentage / 1000) + std::fmod(FirstDigits, 1000) / 1000;
			FirstDigits /= 1000;
			
			auto a = std::trunc(FirstDigits);
			FirstDigits = (float)a;
			Exponent += 3;
		}

		if (FirstDigits < 1 && FirstDigits >= 0 && Exponent > 0)
		{
			if (FirstDigits == 0 && TrailingPercentage == 0)
			{
				Exponent = 1;
				return;
			}

			TrailingPercentage = TrailingPercentage * 1000;
			Exponent -= 3;
			Refactor();
		}

		if (TrailingPercentage >= 1)
		{
			Refactor();
		}
	}

	void KmbNumber::Add(KmbNumber adder)
	{
		if (adder.Exponent == Exponent)
		{
			FirstDigits += adder.FirstDigits;
			TrailingPercentage += adder.TrailingPercentage;
			Refactor();
			return;
		}

		if (Exponent > adder.Exponent)
		{
			TrailingPercentage += adder.FirstDigits * (float)(std::pow(10, -(Exponent - adder.Exponent)));
			Refactor();
			return;
		}

		if (adder.Exponent > Exponent)
		{
			adder.TrailingPercentage += FirstDigits * (float)(std::pow(10, -(adder.Exponent - Exponent)));

			FirstDigits = adder.FirstDigits;
			TrailingPercentage = adder.TrailingPercentage;
			Exponent = adder.Exponent;

			Refactor();
			return;
		}
	}

	void KmbNumber::Subtract(KmbNumber subtractor)
	{
		if (Exponent == subtractor.Exponent)
		{
			FirstDigits -= subtractor.FirstDigits;
			TrailingPercentage -= subtractor.TrailingPercentage;
			Refactor();
			return;
		}

		auto exponentDif = Exponent - subtractor.Exponent;

		auto value1 = FirstDigits + TrailingPercentage;
		auto value2 = subtractor.FirstDigits + subtractor.TrailingPercentage;
		
		if (exponentDif > MAXFLOATEXPONENT)
		{
			Refactor();
			return;
		}
		
		value1 *= (float)(std::pow(10, exponentDif));
		Refactor(value1 - value2, Exponent - exponentDif);
	}

	void KmbNumber::Multiply(KmbNumber multiplier)
	{
		auto firstNumber = FirstDigits + TrailingPercentage;
		auto secondNumber = multiplier.FirstDigits + multiplier.TrailingPercentage;
		auto resultFloat = firstNumber * secondNumber;
		auto resultExponents = Exponent + multiplier.Exponent;

		Refactor(resultFloat, resultExponents);
	}

	void KmbNumber::Divide(KmbNumber divider)
	{
		auto firstNumber = FirstDigits + TrailingPercentage;
		auto secondNumber = divider.FirstDigits + divider.TrailingPercentage;
		
		if (secondNumber != 0)
		{
			auto resultFloat = firstNumber / secondNumber;
			auto resultExponents = Exponent - divider.Exponent;

			Refactor(resultFloat, resultExponents);
		}
	}

	bool KmbNumber::Equals(KmbNumber& other)
	{
		float trailingDiff = std::abs(TrailingPercentage - other.TrailingPercentage);
		bool isTralingEqual = trailingDiff > std::numeric_limits<float>::epsilon() && trailingDiff < 0.000000001f;
		
		if (trailingDiff == 0)
		{
			isTralingEqual = true;
		}

		return Exponent == other.Exponent && isTralingEqual && FirstDigits == other.FirstDigits && Suffix == other.Suffix;
	}

	void KmbNumber::operator=(float number1)
	{
		Refactor(number1, 0);
	}

	void KmbNumber::operator=(KmbNumber& number1)
	{
		FirstDigits = number1.FirstDigits;
		TrailingPercentage = number1.TrailingPercentage;
		Exponent = number1.Exponent;

		Refactor();
	}

	KmbNumber operator+(KmbNumber number1, KmbNumber number2)
	{
		number1.Add(number2);
		return number1;
	}

	void operator+=(KmbNumber& number1, KmbNumber number2)
	{
		number1.Add(number2);
	}

	KmbNumber operator-(KmbNumber number1, KmbNumber number2)
	{
		number1.Subtract(number2);
		return number1;
	}

	void operator-=(KmbNumber& number1, KmbNumber number2)
	{
		number1.Subtract(number2);
	}

	KmbNumber operator*(KmbNumber number1, KmbNumber number2)
	{
		number1.Multiply(number2);
		return number1;
	}

	void operator*=(KmbNumber& number1, KmbNumber number2)
	{
		number1.Multiply(number2);
	}

	KmbNumber operator/(KmbNumber number1, KmbNumber number2)
	{
		number1.Divide(number2);
		return number1;
	}

	void operator/=(KmbNumber& number1, KmbNumber number2)
	{
		number1.Divide(number2);
	}

	bool operator<(KmbNumber& number1, KmbNumber& number2)
	{
		number1.Refactor();
		number2.Refactor();

		if (number1.FirstDigits >= 0 && number2.FirstDigits < 0)
		{
			return false;
		}
		if (number1.TrailingPercentage >= 0 && number2.TrailingPercentage < 0)
		{
			return false;
		}

		if (number1.Exponent < number2.Exponent)
		{
			return true;
		}
		if (number1.Exponent == number2.Exponent)
		{
			if (number1.FirstDigits < number2.FirstDigits)
			{
				return true;
			}
			if (number1.FirstDigits == number2.FirstDigits)
			{
				if (number1.TrailingPercentage < number2.TrailingPercentage)
				{
					return true;
				}
			}
		}

		return false;
	}

	bool operator<=(KmbNumber& number1, KmbNumber& number2)
	{
		number1.Refactor();
		number2.Refactor();

		if (number1.FirstDigits >= 0 && number2.FirstDigits < 0)
		{
			return false;
		}

		if (number1.TrailingPercentage >= 0 && number2.TrailingPercentage < 0)
		{
			return false;
		}

		if (number1.Exponent < number2.Exponent)
		{
			return true;
		}
		if (number1.Exponent == number2.Exponent)
		{
			if (number1.FirstDigits < number2.FirstDigits)
			{
				return true;
			}
			if (number1.FirstDigits == number2.FirstDigits)
			{
				if (number1.TrailingPercentage < number2.TrailingPercentage)
				{
					return true;
				}
			}
		}

		return number1.Equals(number2);
	}
	
	bool operator>(KmbNumber& number1, KmbNumber& number2)
	{
		number1.Refactor();
		number2.Refactor();

		if (number1.FirstDigits < 0 && number2.FirstDigits >= 0)
		{
			return false;
		}
		if (number1.TrailingPercentage < 0 && number2.TrailingPercentage >= 0)
		{
			return false;
		}
		if (number1.FirstDigits < 0 && number2.FirstDigits >= 0)
		{
			return false;
		}
		if (number1.TrailingPercentage < 0 && number2.TrailingPercentage >= 0)
		{
			return false;
		}
		if (number1.Exponent > number2.Exponent)
		{
			return true;
		}
		if (number1.Exponent == number2.Exponent)
		{
			if (number1.FirstDigits > number2.FirstDigits)
			{
				return true;
			}
			if (number1.FirstDigits == number2.FirstDigits)
			{
				if (number1.TrailingPercentage > number2.TrailingPercentage)
				{
					return true;
				}
			}
		}

		return false;
	}
	
	bool operator>=(KmbNumber& number1, KmbNumber& number2)
	{
		number1.Refactor();
		number2.Refactor();

		if (number1.FirstDigits < 0 && number2.FirstDigits >= 0)
		{
			return false;
		}

		if (number1.TrailingPercentage < 0 && number2.TrailingPercentage >= 0)
		{
			return false;
		}

		if (number1.FirstDigits < 0 && number2.FirstDigits >= 0)
		{
			return false;
		}

		if (number1.TrailingPercentage < 0 && number2.TrailingPercentage >= 0)
		{
			return false;
		}

		if (number1.Exponent > number2.Exponent)
		{
			return true;
		}

		if (number1.Exponent == number2.Exponent)
		{
			if (number1.FirstDigits > number2.FirstDigits)
			{
				return true;
			}
			if (number1.FirstDigits == number2.FirstDigits)
			{
				if (number1.TrailingPercentage > number2.TrailingPercentage)
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