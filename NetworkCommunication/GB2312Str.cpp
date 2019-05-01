#include "stdafx.h"
#include "Include/nc/GB2312Str.h"
#include "Include/nc/NCTool.h"
#include "Include/nc/UTF16Str.h"

using namespace NetworkCommunication;

GB2312Str::GB2312Str()
{

}

GB2312Str::~GB2312Str()
{

}

string GB2312Str::FromBuf(BYTE* pBuf, int len)
{
	char* ch = new char[len + 1];
	memset(ch, 0, len + 1);
	memcpy(ch, pBuf, len);
	string str = ch;
	delete ch;
	return str;
}

string GB2312Str::FromUTF8Buf(BYTE* pBuf, int len)
{
	int len1 = 0;
	wstring strUTF16 = UTF16Str::FromUTF8Buf(pBuf, len);
	return FromUTF16(strUTF16);
}

string GB2312Str::FromUTF16(wstring str)
{
	string result = "";

	if (str.size() > 0)
	{
		int nlen = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
		char* strGB2312 = new char[nlen];
		WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, strGB2312, nlen, NULL, NULL);
		result = strGB2312;
		delete strGB2312;
	}

	return result;
}

int GB2312Str::GetByteCount(string str)
{
	int result = 0;

	if (str.size() > 0)
	{
		int nlen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
		wchar_t* strUTF = new wchar_t[nlen];
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, strUTF, nlen);
		result = WideCharToMultiByte(CP_ACP, 0, strUTF, -1, NULL, 0, NULL, NULL);
		delete  strUTF;
		result -= 1;
	}

	return result;
}

int GB2312Str::ToBuf(string str, BYTE* pBuf, bool hasEndChar /*= false*/)
{
	int len = GetByteCount(str);
	if (len > 0)
	{
		memcpy(pBuf, str.c_str(), len);
		if (hasEndChar)
		{
			pBuf[len] = 0;
			len++;
		}
	}
	return len;
}

int GB2312Str::ToUTF8Buf(string str, BYTE* pBuf, bool hasEndChar /*= false*/)
{
	wstring strUTF16 = UTF16Str::FromGB2312(str);
	return UTF16Str::ToUTF8Buf(strUTF16, pBuf, hasEndChar);
}