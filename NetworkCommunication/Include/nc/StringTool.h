#pragma once
#include <string>

using namespace std;

namespace NetworkCommunication
{
	/************************************************************************/
	/* �ַ���������                                                                     */
	/************************************************************************/
	class StringTool
	{
	public:
		StringTool();
		~StringTool();

	public:
		//************************************
		// Method:    UTF8������תUTF16������
		// Returns:   int:	UTF16����������
		// Parameter: BYTE * pBufUTF8:	UTF8������
		// Parameter: int len:			UTF8����������
		// Parameter: BYTE * pBufUTF16:	UTF16������
		// Parameter: bool bBigEndian:	UTF16��ʹ�õ��ֽ���
		//************************************
		static int UTF8_UTF16(BYTE* pBufUTF8, int len, BYTE* pBufUTF16, bool bBigEndian = true);

		//************************************
		// Method:    UTF8������תUTF16�ַ���
		// Returns:   std::wstring
		// Parameter: BYTE * pBufUTF8:	UTF8������
		// Parameter: int len:			UTF8����������
		//************************************
		static wstring UTF8_UTF16(BYTE* pBufUTF8, int len);

		//************************************
		// Method:    UTF8�ַ���תUTF16�ַ���
		//************************************
		static wstring UTF8_UTF16(wstring str);

		//************************************
		// Method:    UTF8������תGB2312������
		// Returns:   int:	GB2312����������
		// Parameter: BYTE * pBufUTF8:		UTF8������
		// Parameter: int len:				UTF8����������
		// Parameter: BYTE * pBufGB2312:	GB2312������
		//************************************
		static int UTF8_GB2312(BYTE* pBufUTF8, int len, BYTE* pBufGB2312);

		//************************************
		// Method:    UTF8������תGB2312�ַ���
		// Returns:   std::wstring
		// Parameter: BYTE * pBufUTF8:	UTF8������
		// Parameter: int len:			UTF8����������
		//************************************
		static string UTF8_GB2312(BYTE* pBufUTF8, int len);

		//************************************
		// Method:    UTF8�ַ���תGB2312�ַ���
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