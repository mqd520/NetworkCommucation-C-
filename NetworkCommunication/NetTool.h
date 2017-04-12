#pragma once
#pragma warning(disable:4996)

#include <string>
#include <WinSock2.h>

using namespace std;

namespace NetworkCommunication
{
	//************************************
	// Method:    ���ֽ������ж�ȡ���ֽ��ַ���
	// FullName:  NetTool::ReadMultiByteStr
	// Access:    public 
	// Returns:   std::string
	// Qualifier:
	// Parameter: �ֽ�����
	// Parameter: �ֽ����鳤��
	//************************************
	string ReadMultiByteStr(BYTE buf[], int len);

	//************************************
	// Method:    ���ֽ������ж�ȡUTF8�ַ���
	// FullName:  NetTool::ReadUTF8Str
	// Access:    public 
	// Returns:   std::wstring
	// Qualifier:
	// Parameter: �ֽ�����
	// Parameter: �ֽ����鳤��
	//************************************
	wstring ReadUTF8Str(BYTE buf[], int len);

	//************************************
	// Method:    д����ֽ��ַ������ֽ�����
	// FullName:  NetTool::WriteMultiByteStr
	// Access:    public 
	// Returns:   BYTE*
	// Qualifier:
	// Parameter: ���ֽ��ַ���
	// Parameter: �ֽ����鳤��(���)
	//************************************
	BYTE* WriteMultiByteStr(char* str, int* size);

	//************************************
	// Method:    д��UTF8�ַ������ֽ�����
	// FullName:  NetTool::WriteUTF8Str
	// Access:    public 
	// Returns:   BYTE*
	// Qualifier:
	// Parameter: UTF8�ַ���
	// Parameter: �ֽ����鳤��(���)
	//************************************
	BYTE* WriteUTF8Str(wchar_t* str, int* size);


	//************************************
	// Method:    ��ȡ����IP
	// FullName:  NetworkCommunication::GetLocalIP
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: TCHAR * ip
	//************************************
	bool GetLocalIP(TCHAR* ip);
}
