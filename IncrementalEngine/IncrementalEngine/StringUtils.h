#ifndef _STRING_UTILS_H
#define _STRING_UTILS_H

#include <Windows.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <locale>
#include <codecvt>

#define StringAsWCHAR_ptr(s, w) std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> c; \
								std::wstring r = c.from_bytes(s); w = (WCHAR*)(r.c_str());

#endif