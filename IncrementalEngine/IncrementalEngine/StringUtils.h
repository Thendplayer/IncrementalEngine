#ifndef _STRING_UTILS_H
#define _STRING_UTILS_H

#include <Windows.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <locale>
#include <codecvt>

using namespace std;

#define StringAsWCHAR_ptr(s, w) wstring_convert<codecvt_utf8_utf16<wchar_t>> c; \
								wstring r = c.from_bytes(s); w = (WCHAR*)(r.c_str());

#endif