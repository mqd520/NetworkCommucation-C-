#pragma once

#include <string>

using namespace std;

namespace tc
{
	/************************************************************************/
	/* GB2312字符串处理                                                                     */
	/************************************************************************/
	class GB2312Str
	{
	public:
		GB2312Str();
		~GB2312Str();

		//************************************
		// Method:    从缓冲区中读取 GB2312 字符串
		// Parameter: BYTE * pBuf:	缓冲区指针
		// Parameter: int len:		缓冲区长度
		//************************************
		static string FromBuf(BYTE* pBuf, int len);

		//************************************
		// Method:    从 UTF8 缓冲区中读取 GB2312 字符串
		// Parameter: BYTE * pBuf:	缓冲区指针
		// Parameter: int len:		缓冲区长度
		//************************************
		static string FromUTF8Buf(BYTE* pBuf, int len);

		//************************************
		// Method:    从 UTF16 字符串中读取 GB2312 字符串
		// Parameter: str:	UTF16字符串
		//************************************
		static string FromUTF16(wstring str);

		//************************************
		// Method:    获取字符串字节长度(不含结束符号)
		//************************************
		static int GetByteCount(string str);

		//************************************
		// Method:    写入到缓冲区中
		// Return:	  写入缓冲区的长度
		// Parameter: BYTE * pBuf:	缓冲区指针
		// Parameter: hasEndChar:	是否写入结束符
		//************************************
		static int ToBuf(string str, BYTE* pBuf, bool hasEndChar = false);

		//************************************
		// Method:    写入到 UTF8 缓冲区中
		// Return:	  写入缓冲区的长度
		// Parameter: BYTE * pBuf:	缓冲区指针
		// Parameter: hasEndChar:	是否写入结束符
		//************************************
		static int ToUTF8Buf(string str, BYTE* pBuf, bool hasEndChar = false);

	private:

	};
}