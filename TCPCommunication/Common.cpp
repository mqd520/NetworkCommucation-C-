#include "stdafx.h"
#include "Common.h"

namespace Common
{
	//多字节转UTF-8
	wstring MultiByteToUTF8(const char* str)
	{
		int nlen = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
		wchar_t* strUTF = new wchar_t[nlen];
		MultiByteToWideChar(CP_ACP, 0, str, -1, strUTF, nlen);
		wstring result = strUTF;
		delete  strUTF;
		return result;
	}

	//UTF-8转多字节
	string UTF8ToMultiByte(const wchar_t* str)
	{
		int nlen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
		char* strMultiByte = new char[nlen];
		WideCharToMultiByte(CP_ACP, 0, str, -1, strMultiByte, nlen, NULL, NULL);
		string result = strMultiByte;
		delete strMultiByte;
		return result;
	}

	int GetAStrByteCount(char* str)
	{
		wstring wstr = MultiByteToUTF8((char*)str);
		int nlen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
		return nlen;
	}

	int GetWStrByteCount(wchar_t* str)
	{
		return (wcslen(str) + 1) * 2;
	}
}