#pragma once

#include <string>

using namespace std;

namespace Common
{
	
	//************************************
	// Method:    ���ֽ��ַ���תUTF8�ַ���
	// FullName:  Common::MultiByteToUTF8
	// Access:    public 
	// Returns:   std::wstring
	// Qualifier:
	// Parameter: const char * str
	//************************************
	wstring MultiByteToUTF8(const char* str);

	
	//************************************
	// Method:    UTF8�ַ���ת���ֽ��ַ���
	// FullName:  Common::UTF8ToMultiByte
	// Access:    public 
	// Returns:   std::string
	// Qualifier:
	// Parameter: const wchar_t * str
	//************************************
	string UTF8ToMultiByte(const wchar_t* str);

	//************************************
	// Method:    ��ȡ���ֽ��ַ����ֽ���
	// FullName:  NetTool::GetStrByteCount
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: TCHAR * str
	//************************************
	int GetAStrByteCount(char* str);

	//************************************
	// Method:    ��ȡ���ֽ��ַ����ֽ���
	// FullName:  NetTool::GetStrByteCount
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: TCHAR * str
	//************************************
	int GetWStrByteCount(wchar_t* str);

	//************************************
	// Method:    ��ȡ�ַ����ֽ���
	// FullName:  Common::GetStrByteCount
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: TCHAR * str
	//************************************
	int GetStrByteCount(TCHAR* str);
}