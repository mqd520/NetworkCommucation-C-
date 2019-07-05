#include "stdafx.h"
#include "Include/tc/UTF16Str.h"

using namespace tc;

//************************************
// Method:    翻转字节数组
//************************************
void Reverse(BYTE arr[], int len)
{
	for (int i = 0; i < len / 2; i++)
	{
		BYTE tmp = arr[len - 1 - i];
		arr[len - 1 - i] = arr[i];
		arr[i] = tmp;
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
	wchar_t* ch = new wchar_t[(len / 2) + 1];
	memset(ch, 0, len + 2);

	if (bo == NCTool::GetHostByteOrder())
	{
		memcpy(ch, pBuf, len);
	}
	else
	{
		int n = 0;
		for (int i = 0; i < len; i += 2)
		{
			BYTE arr[2] = { 0 };
			arr[0] = pBuf[i + 1];
			arr[1] = pBuf[i];
			memcpy(ch + n, arr, 2);
			n++;
		}
	}

	str = ch;
	delete ch;

	return str;
}

void UTF16Str::UTF8_2_UTF16(BYTE* pBuf1, int len1, BYTE* pBuf2, int* len2, EByteOrder bo /*= EByteOrder::big*/)
{
	UINT tmp[4] = { 0 };
	int index = 0;
	int index1 = 0;
	int index2 = 0;
	int size = 0;
	int count = 0;	// UTF16字节总数

	while (index < len1)
	{
		if (index1 == 0)
		{
			memset(tmp, 0, 4);
			BYTE prefix = pBuf1[index] >> 4;	// 获取首字节高4位
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
			tmp[index1] = (UINT)(((BYTE)(pBuf1[index] << size)) >> size);
		}
		else
		{
			tmp[index1] = (UINT)(((BYTE)(pBuf1[index] << 2)) >> 2);//去除高位10
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

			if (bo == EByteOrder::big)	// 大端字节序
			{
				pBuf2[index2++] = (BYTE)(encode >> 8);
				pBuf2[index2++] = (BYTE)((encode << 24) >> 24);
			}
			else // 小端字节序
			{
				pBuf2[index2++] = (BYTE)((encode << 24) >> 24);
				pBuf2[index2++] = (BYTE)(encode >> 8);
			}
			count += 2;
		}
	}

	*len2 = count;
}

void UTF16Str::UTF16_2_UTF8(BYTE* pBuf1, int len1, BYTE* pBuf2, int* len2, EByteOrder bo /*= EByteOrder::big*/)
{
	int index = 0;

	for (int i = 0; i < len1; i += 2)
	{
		wchar_t ch = 0;
		if (bo == NCTool::GetHostByteOrder())
		{
			memcpy(&ch, pBuf1 + i, 2);
		}
		else
		{
			BYTE arr[2] = { 0 };
			arr[0] = pBuf1[i + 1];
			arr[1] = pBuf1[i];
			memcpy(&ch, arr, 2);
		}

		UINT encode = (UINT)ch;				// unicode码值
		BYTE highVal = encode >> 8;			// 高位字节数据
		BYTE lowVal = (encode << 24) >> 24;	// 地位字节数据

		if (encode >= 0x0000 && encode <= 0x007F)	// 1个字节存储
		{
			pBuf2[index] = encode;
			index++;
		}
		else if (encode >= 0x0080 && encode <= 0x07FF)	// 2个字节存储
		{
			BYTE b1 = ((BYTE)(((BYTE)(highVal << 3)) >> 3)) | 192;
			BYTE b2 = ((BYTE)(((BYTE)(lowVal << 2)) >> 2)) | 128;
			pBuf2[index] = b1;
			pBuf2[index + 1] = b2;
			index += 2;
		}
		else if (encode >= 0x0800 && encode <= 0xFFFF)	// 3个字节存储
		{
			BYTE b1 = (BYTE)((BYTE)(highVal >> 4)) | 224;
			BYTE b2 = ((BYTE)(((BYTE)(highVal << 4)) >> 2)) | ((BYTE)(lowVal >> 6)) | 128;
			BYTE b3 = ((BYTE)(((BYTE)(lowVal << 2)) >> 2)) | 128;
			pBuf2[index] = b1;
			pBuf2[index + 1] = b2;
			pBuf2[index + 2] = b3;
			index += 3;
		}
	}

	*len2 = index;
}

wstring UTF16Str::FromUTF8Buf(BYTE* pBuf, int len)
{
	BYTE* pBuf1 = new BYTE[len * 2];
	memset(pBuf1, 0, len * 2);
	int len1 = 0;
	UTF8_2_UTF16(pBuf, len, pBuf1, &len1, NCTool::GetHostByteOrder());
	if (len1 > 0)
	{
		wchar_t* ch = new wchar_t[(len1 / 2) + 1];
		memset(ch, 0, len1 + 2);
		memcpy(ch, pBuf1, len1);
		wstring strUTF16 = ch;
		delete pBuf1;
		delete ch;
		return strUTF16;
	}
	delete pBuf1;
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
				Reverse(pBuf + i, 2);
			}
		}

		if (hasEndChar)
		{
			pBuf[len] = 0;
			pBuf[len + 1] = 0;

			len += 2;
		}
	}

	return len;
}

int UTF16Str::ToUTF8Buf(wstring str, BYTE* pBuf, bool hasEndChar /*= false*/)
{
	int result = 0;
	int n = GetByteCount(str);
	if (n > 0)
	{
		int n1 = hasEndChar == true ? n + 2 : n;
		BYTE* pBufUTF16 = new BYTE[n1];
		int len = ToBuf(str, pBufUTF16, EByteOrder::litte, hasEndChar);
		UTF16_2_UTF8(pBufUTF16, len, pBuf, &result, EByteOrder::litte);
		delete pBufUTF16;
	}

	return result;
}