#pragma once
#include <string>

using namespace std;

namespace NetworkCommunication
{
	/************************************************************************/
	/* 字符串工具类                                                                     */
	/************************************************************************/
	class StringTool
	{
	public:
		StringTool();
		~StringTool();

	public:
		//************************************
		// Method:    UTF8缓冲区转UTF16缓冲区
		// Returns:   int:	UTF16缓冲区长度
		// Parameter: BYTE * pBufUTF8:	UTF8缓冲区
		// Parameter: int len:			UTF8缓冲区长度
		// Parameter: BYTE * pBufUTF16:	UTF16缓冲区
		// Parameter: bool bBigEndian:	UTF16所使用的字节序
		//************************************
		static int UTF8_UTF16(BYTE* pBufUTF8, int len, BYTE* pBufUTF16, bool bBigEndian = true);

		//************************************
		// Method:    UTF8缓冲区转UTF16字符串
		// Returns:   std::wstring
		// Parameter: BYTE * pBufUTF8:	UTF8缓冲区
		// Parameter: int len:			UTF8缓冲区长度
		//************************************
		static wstring UTF8_UTF16(BYTE* pBufUTF8, int len);

		//************************************
		// Method:    UTF8字符串转UTF16字符串
		//************************************
		static wstring UTF8_UTF16(wstring str);

		//************************************
		// Method:    UTF8缓冲区转GB2312缓冲区
		// Returns:   int:	GB2312缓冲区长度
		// Parameter: BYTE * pBufUTF8:		UTF8缓冲区
		// Parameter: int len:				UTF8缓冲区长度
		// Parameter: BYTE * pBufGB2312:	GB2312缓冲区
		//************************************
		static int UTF8_GB2312(BYTE* pBufUTF8, int len, BYTE* pBufGB2312);

		//************************************
		// Method:    UTF8缓冲区转GB2312字符串
		// Returns:   std::wstring
		// Parameter: BYTE * pBufUTF8:	UTF8缓冲区
		// Parameter: int len:			UTF8缓冲区长度
		//************************************
		static string UTF8_GB2312(BYTE* pBufUTF8, int len);

		//************************************
		// Method:    UTF8字符串转GB2312字符串
		//************************************
		static string UTF8_GB2312(wstring str);

		static wstring UTF16_UTF8(wstring str);

		static string UTF16_GB2312(wstring str);

		static wstring GB2312_UTF16(string str);

		static wstring GB2312_UTF8(string str);

		static int GetGB2312ByteCount(string str);

		static int GetUTF16ByteCount(string str);

		static int GetUTF8ByteCount(string str);

		static int WriteGB2312ToBuf(string str, BYTE* buf);

	private:

	};
}