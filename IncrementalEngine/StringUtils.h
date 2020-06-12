#ifndef _STRING_UTILS_H
#define _STRING_UTILS_H

#include <string>
#include <fstream>

#define StringAsWCHAR_ptr(s, w) std::wstring ws(s.begin(), s.end()); w = ws.c_str();
#define WStringAsCHAR_ptr(w, s) std::string str(w.begin(), w.end()); s = str.c_str();

#endif