#pragma once

#include <Stringapiset.h>
#include <string>

using namespace std;

namespace Common
{
	//���ֽ�תUTF-8
	wstring MultiByteToUTF8(const char* str);

	//UTF-8ת���ֽ�
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

#ifdef _UNICODE
	//��ȡ�ַ����ֽ���
#define	GetStrByteCount	GetWStrByteCount
#else
#define GetStrByteCount	GetAStrByteCount
#endif
}