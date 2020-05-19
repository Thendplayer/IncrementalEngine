#pragma once

#include <string>
#include <cmath>
#include <limits>

namespace MagicIdle 
{
	class KmbNumber
	{
	#define SUFFIX {"K", "M", "B", "T", "Q", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K"\
				  , "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"\
				  , "AA", "BB", "CC", "DD", "EE", "FF", "GG", "HH", "II", "JJ", "KK", "LL", "MM"\
				  , "NN", "OO", "PP", "QQ", "RR", "SS", "TT", "UU", "VV", "WW", "XX", "YY", "ZZ"}
	
	#define DECIMALS_TO_SHOW 2
	#define MAXFLOATEXPONENT 34

	public:
		float _firstDigits = 0;
		float _trailingPercentage = 0;
		int _exponent = 0;

		std::string suffix = "";

		static KmbNumber Zero;

		KmbNumber(const KmbNumber& kmbNumber);
		KmbNumber(float firstDigits, float trailing, int exponent);
		KmbNumber(float number, int exponent = 0);

		KmbNumber operator= (float number1);
		double operator= (KmbNumber number1);

		static KmbNumber RoundUp(KmbNumber& number);

		std::string ToString();
		bool Equals(KmbNumber other);

		float GetRawNumber();
		float GetInt();

		KmbNumber Refactor(float value, int exponent);
		KmbNumber Refactor(KmbNumber number);

		KmbNumber Add(KmbNumber adder);
		KmbNumber Subtract(KmbNumber subtractor);
		KmbNumber Multiply(KmbNumber multiplier);
		KmbNumber Divide(KmbNumber divider);

	private:
		void SetSuffix();
		float GetStringTrailingPercentage();
	};

	KmbNumber operator + (KmbNumber& number1, KmbNumber& number2);
	KmbNumber operator - (KmbNumber& number1, KmbNumber& number2);
	KmbNumber operator * (KmbNumber& number1, KmbNumber& number2);
	KmbNumber operator / (KmbNumber& number1, KmbNumber& number2);

	bool operator <  (KmbNumber& number1, KmbNumber& number2);
	bool operator <= (KmbNumber& number1, KmbNumber& number2);
	bool operator >  (KmbNumber& number1, KmbNumber& number2);
	bool operator >= (KmbNumber& number1, KmbNumber& number2);

	bool operator == (KmbNumber& left, KmbNumber& right);
	bool operator != (KmbNumber& left, KmbNumber& right);
}