#ifndef _STRING_UTILS_H
#define _STRING_UTILS_H

#include <Windows.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <locale>
#include <codecvt>

using namespace std;

static class StringUtils 
{
public:
	static WCHAR* AsWCHAR_ptr(string string) 
	{
		wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
		wstring result = converter.from_bytes(string); 
		return (WCHAR*)(result.c_str());
	}
};

#endif