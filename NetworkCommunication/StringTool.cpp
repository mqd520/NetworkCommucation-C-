#include "stdafx.h"
#include "Include/nc/StringTool.h"

using namespace NetworkCommunication;

StringTool::StringTool()
{

}

StringTool::~StringTool()
{

}

int StringTool::UTF8_UTF16(BYTE* pBufUTF8, int len, BYTE* pBufUTF16, bool bBigEndian /*= true*/)
{
	UINT tmp[4] = { 0 };
	int index = 0;
	int index1 = 0;
	int index2 = 0;
	int size = 0;
	int count = 0;	// UTF16字节总数

	while (index < len)
	{
		if (index1 == 0)
		{
			memset(tmp, 0, 4);
			BYTE prefix = pBufUTF8[index] >> 4;	// 获取首字节高4位
			if ((BYTE)(prefix >> 3) == 0)	// 表示单字节字符串
			{
				size = 1;
			}
			else if (prefix == 6)	// 表示2字节字符串
			{
				size = 2;
			}
			else if (prefix == 14)	// 表示3字节字符串
			{
				size = 3;
			}
			else if (prefix == 15)	// 表示4字节字符串
			{
				size = 4;
			}
			tmp[index1] = (UINT)(((BYTE)(pBufUTF8[index] << size)) >> size);
		}
		else
		{
			tmp[index1] = (UINT)(((BYTE)(pBufUTF8[index] << 2)) >> 2);//去除高位10
		}

		index++;

		index1++;
		if (index1 == size)
		{
			index1 = 0;

			//计算出unicode对应值
			UINT encode = tmp[size - 1];
			int step = 1;
			for (int i = size - 2; i > -1; i--)
			{
				encode |= tmp[i] << (step * 6);
				step++;
			}

			if (bBigEndian)	// 大端字节序
			{
				pBufUTF16[index2++] = (BYTE)(encode >> 8);
				pBufUTF16[index2++] = (BYTE)((encode << 24) >> 24);
			}
			else // 小端字节序
			{
				pBufUTF16[index2++] = (BYTE)((encode << 24) >> 24);
				pBufUTF16[index2++] = (BYTE)(encode >> 8);
			}
			count += 2;
		}
	}

	return count;
}

wstring StringTool::UTF8_UTF16(BYTE* pBufUTF8, int len)
{
	BYTE buf[1024] = { 0 };
	int len1 = UTF8_UTF16(pBufUTF8, len, buf, false);
	wchar_t ch[1024] = { 0 };
	memcpy(ch, buf, len1);
	wstring str(ch);
	return str;
}

wstring StringTool::UTF8_UTF16(wstring str)
{
	int nlen = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
	char* strGB2312Byte = new char[nlen];
	WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, strGB2312Byte, nlen, NULL, NULL);
	string result = strGB2312Byte;
	delete strGB2312Byte;
	return GB2312_UTF16(result);
}

int StringTool::UTF8_GB2312(BYTE* pBufUTF8, int len, BYTE* pBufGB2312)
{
	wstring str = UTF8_UTF16(pBufUTF8, len);
	string str1 = UTF16_GB2312(str);
	int len1 = WriteGB2312ToBuf(str1, pBufGB2312);
	return len1;
}

string StringTool::UTF8_GB2312(BYTE* pBufUTF8, int len)
{
	wstring str = UTF8_UTF16(pBufUTF8, len);
	return UTF16_GB2312(str);
}

wstring StringTool::UTF16_UTF8(wstring str)
{
	return L"";
}

string StringTool::UTF16_GB2312(wstring str)
{
	int nlen = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
	char* strGB2312 = new char[nlen];
	WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, strGB2312, nlen, NULL, NULL);
	string result = strGB2312;
	delete strGB2312;
	return result;
}

string StringTool::UTF8_GB2312(wstring str)
{
	return "";
}

wstring StringTool::GB2312_UTF16(string str)
{
	int nlen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* strUTF = new wchar_t[nlen];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, strUTF, nlen);
	wstring result = strUTF;
	delete  strUTF;
	return result;
}

wstring StringTool::GB2312_UTF8(string str)
{
	int nlen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* strUTF8 = new wchar_t[nlen];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, strUTF8, nlen);
	wstring result = strUTF8;
	delete  strUTF8;
	return result;
}

int StringTool::GetGB2312ByteCount(string str)
{
	wstring wstr = GB2312_UTF16(str);
	int nlen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	return nlen;
}

int StringTool::WriteGB2312ToBuf(string str, BYTE* buf)
{
	int len1 = GetGB2312ByteCount(str);
	memcpy(buf, str.c_str(), len1);
	return len1;
}
