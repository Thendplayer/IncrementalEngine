#ifndef _STRING_UTILS_H
#define _STRING_UTILS_H

#include <Windows.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <locale>
#include <codecvt>

#define StringAsWCHAR_ptr(s, w) std::wstring ws(s.begin(), s.end()); w = ws.c_str();

#endif