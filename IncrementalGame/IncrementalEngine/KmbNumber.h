#pragma once

#include <string>
#include <cmath>
#include <limits>

namespace IncrementalEngine 
{
	class KmbNumber
	{
	#define SUFFIX {L" ", L"K", L"M", L"B", L"T", L"Q", L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J"\
				  , L"K", L"L", L"M", L"N", L"O", L"P", L"Q", L"R", L"S", L"T", L"U", L"V", L"W", L"X", L"Y", L"Z"\
				  , L"AA", L"BB", L"CC", L"DD", L"EE", L"FF", L"GG", L"HH", L"II", L"JJ", L"KK", L"LL", L"MM"\
				  , L"NN", L"OO", L"PP", L"QQ", L"RR", L"SS", L"TT", L"UU", L"VV", L"WW", L"XX", L"YY", L"ZZ"}
	
	#define DECIMALS_TO_SHOW 2
	#define MAXFLOATEXPONENT 34

	public:
		static KmbNumber Zero;

		float FirstDigits = 0;
		float TrailingPercentage = 0;
		int Exponent = 0;

		std::wstring Suffix = L" ";

		KmbNumber();
		KmbNumber(const KmbNumber& kmbNumber);
		KmbNumber(float firstDigits, float trailing, int exponent);
		KmbNumber(float number, int exponent = 0);

		static void RoundUp(KmbNumber& number);

		std::wstring ToString();
		bool Equals(KmbNumber& other);

		float GetRawNumber();
		float GetInt();

		void Refactor(float value, int exponent);
		void Refactor();

		void Add(KmbNumber adder);
		void Subtract(KmbNumber subtractor);
		void Multiply(KmbNumber multiplier);
		void Divide(KmbNumber divider);

		void operator= (float number1);
		void operator= (KmbNumber& number1);

	private:
		void SetSuffix();
		float GetStringTrailingPercentage();
	};

	KmbNumber operator + (KmbNumber number1, KmbNumber number2);
	void operator += (KmbNumber& number1, KmbNumber number2);
	KmbNumber operator - (KmbNumber number1, KmbNumber number2);
	void operator -= (KmbNumber& number1, KmbNumber number2);
	KmbNumber operator * (KmbNumber number1, KmbNumber number2);
	void operator *= (KmbNumber& number1, KmbNumber number2);
	KmbNumber operator / (KmbNumber number1, KmbNumber number2);
	void operator /= (KmbNumber& number1, KmbNumber number2);

	bool operator <  (KmbNumber& number1, KmbNumber& number2);
	bool operator <= (KmbNumber& number1, KmbNumber& number2);
	bool operator >  (KmbNumber& number1, KmbNumber& number2);
	bool operator >= (KmbNumber& number1, KmbNumber& number2);

	bool operator == (KmbNumber& left, KmbNumber& right);
	bool operator != (KmbNumber& left, KmbNumber& right);
}