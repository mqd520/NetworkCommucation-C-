#pragma once

#include <Stringapiset.h>
#include <string>

using namespace std;

namespace Common
{
	//多字节转UTF-8
	wstring MultiByteToUTF8(const char* str);

	//UTF-8转多字节
	string UTF8ToMultiByte(const wchar_t* str);

	//************************************
	// Method:    获取多字节字符串字节数
	// FullName:  NetTool::GetStrByteCount
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: TCHAR * str
	//************************************
	int GetAStrByteCount(char* str);

	//************************************
	// Method:    获取宽字节字符串字节数
	// FullName:  NetTool::GetStrByteCount
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: TCHAR * str
	//************************************
	int GetWStrByteCount(wchar_t* str);

#ifdef _UNICODE
	//获取字符串字节数
#define	GetStrByteCount	GetWStrByteCount
#else
#define GetStrByteCount	GetAStrByteCount
#endif
}