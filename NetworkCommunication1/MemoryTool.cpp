#include "stdafx.h"
#include "MemoryTool.h"

namespace NetworkCommunication
{
	wstring MultiByteToUTF8(const char* str)
	{
		int nlen = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
		wchar_t* strUTF = new wchar_t[nlen];
		MultiByteToWideChar(CP_ACP, 0, str, -1, strUTF, nlen);
		wstring result = strUTF;
		delete  strUTF;
		return result;
	}

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

	int GetStrByteCount(TCHAR* str)
	{
		if (sizeof(TCHAR) == 1)
		{
			return	GetAStrByteCount((char*)str);
		}
		else
		{
			return GetWStrByteCount((wchar_t*)str);
		}
	}

	BYTE GetFstByteFromInt(int n)
	{
		return (BYTE)(n >> 24);
	}

	BYTE GetSecByteFromInt(int n)
	{
		return (BYTE)((n << 8) >> 24);
	}

	BYTE GetTrdByteFromInt(int n)
	{
		return (BYTE)((n << 16) >> 24);
	}

	BYTE GetFouthByteFromInt(int n)
	{
		return (BYTE)((n << 24) >> 24);
	}

	int MergeByte(BYTE fouth, BYTE trd, BYTE sec, BYTE fst)
	{
		int result = 0;
		if (fst != 0)
		{
			result += (int)(fst << 24);
		}
		if (sec != 0)
		{
			result += (int)(sec << 16);
		}
		if (trd != 0)
		{
			result += (int)(trd << 8);
		}
		if (fouth != 0)
		{
			result += (int)fouth;
		}
		return result;
	}

	int GetLenFromMultiByteBuf(BYTE* buf, int start, int end)
	{
		char* buf1 = new char[end - start];
		memcpy(buf1, buf + start, end - start);
		int len = strlen(buf1) + 1;
		delete buf1;
		return len;
	}

	BYTE* WriteIntToBuf(int val, bool bLittleEndian)
	{
		int len = sizeof(int);
		BYTE* buf = new BYTE[len];
		if (bLittleEndian)
		{
			for (int i = 0; i < len; i++)
			{
				int left = (len - (1 + i)) * 8;//向左平移位数
				int right = 3 * 8;//向右平移位数
				buf[i] = (val << left) >> right;
			}
		}
		else
		{
			for (int i = 0; i < len; i++)
			{
				int left = i * 8;//向左平移位数
				int right = 3 * 8;//向右平移位数
				buf[i] = (val << left) >> right;
			}
		}
		return buf;
	}

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

	BYTE* WriteShortToBuf(short val, bool bLittleEndian)
	{
		int len = sizeof(short);
		BYTE* buf = new BYTE[len];
		if (bLittleEndian)
		{
			buf[0] = (val << 8) >> 8;
			buf[1] = val >> 8;
		}
		else
		{
			buf[0] = val >> 8;
			buf[1] = (val << 8) >> 8;
		}
		return buf;
	}
}
