#include "stdafx.h"
#include "Common.h"

//多字节转UTF-8
wchar_t* MultiByteToUTF8(const char* str)
{
	int nlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	wchar_t* strUTF = new wchar_t[nlen + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strUTF, nlen);
	return strUTF;
}

//UTF-8转多字节
char* UTF8ToMultiByte(const wchar_t* str)
{
	int nlen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	char* strMultiByte = new char[nlen + 1];
	WideCharToMultiByte(CP_ACP, 0, str, -1, strMultiByte, nlen, NULL, NULL);
	return strMultiByte;
}