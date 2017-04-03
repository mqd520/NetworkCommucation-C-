#include "stdafx.h"
#include "NetTool.h"

namespace NetTool
{
	//从字节数组中读取多字节字符串
	string ReadMultiByteStr(BYTE buf[], int len)
	{
		char* str = new char[len + 1];
		memcpy(str, buf, len);
		str[len] = 0;
		string result = str;
		delete str;
		return result;
	}

	//从字节数组中读取UTF8字符串
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

	//写入多字节字符串到字节数组
	BYTE* WriteMultiByteStr(char* str)
	{
		int len = strlen(str);
		BYTE* buf = new BYTE[len + 1];
		memcpy(buf, str, len);
		buf[len] = 0;
		return buf;
	}

	//写入UTF8字符串到字节数组
	BYTE* WriteUTF8Str(wchar_t* str, int* size)
	{
		int len = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
		*size = len;
		char* buf = new char[len];
		WideCharToMultiByte(CP_ACP, 0, str, -1, buf, len, NULL, NULL);
		return (BYTE*)buf;
	}
}