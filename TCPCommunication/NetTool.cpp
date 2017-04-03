#include "stdafx.h"
#include "NetTool.h"

namespace NetTool
{
	//���ֽ������ж�ȡ���ֽ��ַ���
	string ReadMultiByteStr(BYTE buf[], int len)
	{
		char* str = new char[len + 1];
		memcpy(str, buf, len);
		str[len] = 0;
		string result = str;
		delete str;
		return result;
	}

	//���ֽ������ж�ȡUTF8�ַ���
	wstring ReadUTF8Str(BYTE buf[], int len)
	{
		int size = MultiByteToWideChar(CP_ACP, 0, (char*)buf, len, NULL, 0);
		wchar_t* strUTF = new wchar_t[size + 1];
		MultiByteToWideChar(CP_ACP, 0, (char*)buf, len, strUTF, len);
		strUTF[size] = 0;
		wstring result = strUTF;
		delete strUTF;
		return result;
	}

	//д����ֽ��ַ������ֽ�����
	BYTE* WriteMultiByteStr(char* str)
	{
		int len = strlen(str);
		BYTE* buf = new BYTE[len + 1];
		memcpy(buf, str, len);
		buf[len] = 0;
		return buf;
	}

	//д��UTF8�ַ������ֽ�����
	BYTE* WriteUTF8Str(wchar_t* str, int* size)
	{
		int len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
		*size = len;
		char* buf = new char[len];
		WideCharToMultiByte(CP_ACP, 0, str, -1, buf, len, NULL, NULL);
		return (BYTE*)buf;
	}
}