#pragma once

#include <string>

using namespace std;

namespace NetworkCommunication
{
	/************************************************************************/
	/* UTF8字符串处理                                                                     */
	/************************************************************************/
	class UTF8Str
	{
	public:
		UTF8Str();
		~UTF8Str();

		//************************************
		// Method:    从缓冲区中读取 UTF8 字符串
		// Parameter: BYTE * pBuf:	缓冲区指针
		// Parameter: int len:		缓冲区长度
		//************************************
		static wstring FromBuf(BYTE* pBuf, int len);

		//************************************
		// Method:    从缓冲区中读取 UTF8 字符串
		// Parameter: BYTE * pBuf:	缓冲区指针
		// Parameter: int len:		缓冲区长度
		//************************************
		static string FromBuf1(BYTE* pBuf, int len);

		//************************************
		// Method:    从 UTF16 字符串中读取 UTF8 字符串
		// Parameter: str:	UTF16字符串
		//************************************
		static wstring FromUTF16(wstring str);

		//************************************
		// Method:    从 UTF16 字符串中读取 UTF8 字符串
		// Parameter: str:	UTF16字符串
		//************************************
		static string FromUTF161(wstring str);

		//************************************
		// Method:    从 GB2312 字符串中读取 UTF8 字符串
		// Parameter: str:	GB2312字符串
		//************************************
		static wstring FromGB2312(string str);

		//************************************
		// Method:    从 GB2312 字符串中读取 UTF8 字符串
		// Parameter: str:	GB2312字符串
		//************************************
		static string FromGB23121(string str);

		//************************************
		// Method:    获取字符串字节长度
		//************************************
		static int GetByteCount(string str);

		//************************************
		// Method:    获取字符串字节长度
		//************************************
		static int GetByteCount(wstring str);

		//************************************
		// Method:    写入到缓冲区中
		// Return:	  写入缓冲区的长度
		// Parameter: BYTE * pBuf:	缓冲区指针
		// Parameter: prefixLen:	字符串前缀长度, 范围: 1-4, 0: 无前缀
		// Parameter: hasEndChar:	是否写入结束符
		//************************************
		static int ToBuf(wstring str, BYTE* pBuf, int prefixLen = 4, bool hasEndChar = false);

		//************************************
		// Method:    写入到缓冲区中
		// Return:	  写入缓冲区的长度
		// Parameter: BYTE * pBuf:	缓冲区指针
		// Parameter: prefixLen:	字符串前缀长度, 范围: 1-4, 0: 无前缀
		// Parameter: hasEndChar:	是否写入结束符
		//************************************
		static int ToBuf(string str, BYTE* pBuf, int prefixLen = 4, bool hasEndChar = false);

	private:

	};
}