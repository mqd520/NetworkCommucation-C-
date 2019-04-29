#include "stdafx.h"
#include "Include/nc/UTF16Str.h"

using namespace NetworkCommunication;

void swap(BYTE arr[], int startIndex, int len)
{
	for (int i = 0; i < len / 2; i++)
	{
		BYTE tmp = arr[startIndex + len - 1 - i];
		arr[startIndex + len - 1 - i] = arr[startIndex + i];
		arr[startIndex + i] = tmp;
	}
}

UTF16Str::UTF16Str()
{

}

UTF16Str::~UTF16Str()
{

}

wstring UTF16Str::FromBuf(BYTE* pBuf, int len, EByteOrder bo /*= EByteOrder::big*/)
{
	wstring str;
	wchar_t ch[1024] = { 0 };

	int n = 0;
	for (int i = 0; i < len; i += 2)
	{
		BYTE arr[2];
		memcpy(arr, pBuf + i, 2);
		if (bo == EByteOrder::big)
		{
			swap(arr, 0, 2);
		}
		memcpy(ch + n, arr, 2);
		n++;
	}
	str = ch;

	return str;
}

wstring UTF16Str::FromUTF8(wstring str)
{
	return L"";
}

wstring UTF16Str::FromUTF8(string str)
{
	return L"";
}

wstring UTF16Str::FromGB2312(string str)
{
	int nlen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* strUTF16 = new wchar_t[nlen];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, strUTF16, nlen);
	wstring result = strUTF16;
	delete  strUTF16;
	return result;
}

int UTF16Str::GetByteCount(wstring str)
{
	return str.size() * 2;
}

int UTF16Str::ToBuf(wstring str, BYTE* pBuf, EByteOrder bo /*= EByteOrder::big*/, bool hasEndChar /*= false*/)
{
	int len = GetByteCount(str);
	if (len > 0)
	{
		memcpy(pBuf, str.c_str(), len);
		if (NCTool::GetHostByteOrder() != bo)
		{
			for (int i = 0; i < len; i += 2)
			{
				swap(pBuf + i, i, 2);
			}
		}

		if (hasEndChar)
		{
			pBuf[len] = 0;
			pBuf[len + 1] = 0;
		}
	}

	return len;
}