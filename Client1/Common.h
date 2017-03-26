#pragma once

//#include <tchar.h>
#include <Stringapiset.h>

using namespace std;

//多字节转UTF-8
wchar_t* MultiByteToUTF8(const char* str);
//UTF-8转多字节
char* UTF8ToMultiByte(const wchar_t* str);