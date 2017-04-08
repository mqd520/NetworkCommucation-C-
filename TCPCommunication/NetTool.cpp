#include "stdafx.h"
#include "NetTool.h"
#include "Common.h"

namespace TCPCommunication
{
	string ReadMultiByteStr(BYTE buf[], int len)
	{
		char* str = new char[len + 1];
		memcpy(str, buf, len);
		str[len] = 0;
		string result = str;
		delete str;
		return result;
	}

	wstring ReadUTF8Str(BYTE buf[], int len)
	{
		int size = len / 2;
		wchar_t* strUTF8 = new wchar_t[size + 1];
		memcpy(strUTF8, buf, len);
		strUTF8[size] = 0;
		wstring result = strUTF8;
		delete strUTF8;
		return result;
	}

	BYTE* WriteMultiByteStr(char* str, int* size)
	{
		*size = strlen(str) + 1;
		BYTE* buf = new BYTE[*size];
		memcpy(buf, str, *size);
		return buf;
	}

	BYTE* WriteUTF8Str(wchar_t* str, int* size)
	{
		*size = GetWStrByteCount(str);
		BYTE* buf = new BYTE[*size];
		memcpy(buf, str, *size);
		return buf;
	}
}