#pragma once

#include <string>

using namespace std;

namespace NetworkCommunication
{
	/************************************************************************/
	/* UTF8�ַ�������                                                                     */
	/************************************************************************/
	class UTF8Str
	{
	public:
		UTF8Str();
		~UTF8Str();

		//************************************
		// Method:    �ӻ������ж�ȡ UTF8 �ַ���
		// Parameter: BYTE * pBuf:	������ָ��
		// Parameter: int len:		����������
		//************************************
		static wstring FromBuf(BYTE* pBuf, int len);

		//************************************
		// Method:    �ӻ������ж�ȡ UTF8 �ַ���
		// Parameter: BYTE * pBuf:	������ָ��
		// Parameter: int len:		����������
		//************************************
		static string FromBuf1(BYTE* pBuf, int len);

		//************************************
		// Method:    �� UTF16 �ַ����ж�ȡ UTF8 �ַ���
		// Parameter: str:	UTF16�ַ���
		//************************************
		static wstring FromUTF16(wstring str);

		//************************************
		// Method:    �� UTF16 �ַ����ж�ȡ UTF8 �ַ���
		// Parameter: str:	UTF16�ַ���
		//************************************
		static string FromUTF161(wstring str);

		//************************************
		// Method:    �� GB2312 �ַ����ж�ȡ UTF8 �ַ���
		// Parameter: str:	GB2312�ַ���
		//************************************
		static wstring FromGB2312(string str);

		//************************************
		// Method:    �� GB2312 �ַ����ж�ȡ UTF8 �ַ���
		// Parameter: str:	GB2312�ַ���
		//************************************
		static string FromGB23121(string str);

		//************************************
		// Method:    ��ȡ�ַ����ֽڳ���
		//************************************
		static int GetByteCount(string str);

		//************************************
		// Method:    ��ȡ�ַ����ֽڳ���
		//************************************
		static int GetByteCount(wstring str);

		//************************************
		// Method:    д�뵽��������
		// Return:	  д�뻺�����ĳ���
		// Parameter: BYTE * pBuf:	������ָ��
		// Parameter: prefixLen:	�ַ���ǰ׺����, ��Χ: 1-4, 0: ��ǰ׺
		// Parameter: hasEndChar:	�Ƿ�д�������
		//************************************
		static int ToBuf(wstring str, BYTE* pBuf, int prefixLen = 4, bool hasEndChar = false);

		//************************************
		// Method:    д�뵽��������
		// Return:	  д�뻺�����ĳ���
		// Parameter: BYTE * pBuf:	������ָ��
		// Parameter: prefixLen:	�ַ���ǰ׺����, ��Χ: 1-4, 0: ��ǰ׺
		// Parameter: hasEndChar:	�Ƿ�д�������
		//************************************
		static int ToBuf(string str, BYTE* pBuf, int prefixLen = 4, bool hasEndChar = false);

	private:

	};
}