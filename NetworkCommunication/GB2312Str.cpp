#include "stdafx.h"
#include "Include/nc/GB2312Str.h"

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
	return "";
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

string GB2312Str::FromUTF8(string str)
{
	string result;
	WCHAR *strSrc;
	char *szRes;

	int i = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, strSrc, i);

	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new char[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

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