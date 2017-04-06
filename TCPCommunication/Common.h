#pragma once

#include <string>

using namespace std;

namespace Common
{
	
	//************************************
	// Method:    多字节字符串转UTF8字符串
	// FullName:  Common::MultiByteToUTF8
	// Access:    public 
	// Returns:   std::wstring
	// Qualifier:
	// Parameter: const char * str
	//************************************
	wstring MultiByteToUTF8(const char* str);

	
	//************************************
	// Method:    UTF8字符串转多字节字符串
	// FullName:  Common::UTF8ToMultiByte
	// Access:    public 
	// Returns:   std::string
	// Qualifier:
	// Parameter: const wchar_t * str
	//************************************
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

	//************************************
	// Method:    获取字符串字节数
	// FullName:  Common::GetStrByteCount
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: TCHAR * str
	//************************************
	int GetStrByteCount(TCHAR* str);
}