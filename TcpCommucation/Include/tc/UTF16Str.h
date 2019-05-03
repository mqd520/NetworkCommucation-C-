#pragma once

#include "NCTool.h"
#include <string>

using namespace std;

namespace tc
{
	/************************************************************************/
	/* UTF16字符串处理                                                                     */
	/************************************************************************/
	class UTF16Str
	{
	public:
		UTF16Str();
		~UTF16Str();

		//************************************
		// Method:    从缓冲区中读取 UTF16 字符串
		// Parameter: BYTE * pBuf:		缓冲区指针
		// Parameter: int len:			缓冲区长度
		// Parameter: EByteOrder bo:	缓冲区字节序, 默认: 大端字节序
		//************************************
		static wstring FromBuf(BYTE* pBuf, int len, EByteOrder bo = EByteOrder::big);

		//************************************
		// Method:    将 UTF8 缓冲区转换成 UTF16 缓冲区
		// Parameter: BYTE * pBuf1:		UTF8缓冲区指针
		// Parameter: int len1:			UTF8缓冲区长度
		// Parameter: BYTE * pBuf2:		UTF16缓冲区指针
		// Parameter: int len2:			UTF16缓冲区长度
		// Parameter: EByteOrder bo:	UTF16缓冲区字节序, 默认: 大端字节序
		//************************************
		static void UTF8_2_UTF16(BYTE* pBuf1, int len1, BYTE* pBuf2, int* len2, EByteOrder bo = EByteOrder::big);

		//************************************
		// Method:    将 UTF16 缓冲区转换成 UTF8 缓冲区
		// Parameter: BYTE * pBuf1:		UTF16缓冲区指针
		// Parameter: int len1:			UTF16缓冲区长度
		// Parameter: BYTE * pBuf2:		UTF8缓冲区指针
		// Parameter: int len2:			UTF8缓冲区长度
		// Parameter: EByteOrder bo:	UTF16缓冲区字节序, 默认: 大端字节序
		//************************************
		static void UTF16_2_UTF8(BYTE* pBuf1, int len1, BYTE* pBuf2, int* len2, EByteOrder bo = EByteOrder::big);

		//************************************
		// Method:    从 UTF8 缓冲区中读取 UTF16 字符串
		// Parameter: BYTE * pBuf:		缓冲区指针
		// Parameter: int len:			缓冲区长度
		//************************************
		static wstring FromUTF8Buf(BYTE* pBuf, int len);

		//************************************
		// Method:    从 GB2312 字符串中读取 UTF16 字符串
		// Parameter: str:	GB2312字符串
		//************************************
		static wstring FromGB2312(string str);

		//************************************
		// Method:    获取字符串字节长度
		//************************************
		static int GetByteCount(wstring str);

		//************************************
		// Method:    写入到缓冲区中
		// Return:	  写入缓冲区的长度
		// Parameter: BYTE * pBuf:	缓冲区指针
		// Parameter: hasEndChar:	是否写入结束符
		// Parameter: EByteOrder bo:缓冲区字节序, 默认: 大端字节序
		//************************************
		static int ToBuf(wstring str, BYTE* pBuf, EByteOrder bo = EByteOrder::big, bool hasEndChar = false);

		//************************************
		// Method:    写入到缓冲区中(UTF8)
		// Return:	  写入缓冲区的长度
		// Parameter: BYTE * pBuf:	缓冲区指针
		// Parameter: hasEndChar:	是否写入结束符
		//************************************
		static int ToUTF8Buf(wstring str, BYTE* pBuf, bool hasEndChar = false);

	private:

	};
}