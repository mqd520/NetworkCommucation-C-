#pragma once

#include <string>

using namespace std;

namespace NetworkCommunication
{
	/************************************************************************/
	/* GB2312�ַ�������                                                                     */
	/************************************************************************/
	class GB2312Str
	{
	public:
		GB2312Str();
		~GB2312Str();

		//************************************
		// Method:    �ӻ������ж�ȡ GB2312 �ַ���
		// Parameter: BYTE * pBuf:	������ָ��
		// Parameter: int len:		����������
		//************************************
		static string FromBuf(BYTE* pBuf, int len);

		//************************************
		// Method:    �� UTF16 �ַ����ж�ȡ GB2312 �ַ���
		// Parameter: str:	UTF16�ַ���
		//************************************
		static string FromUTF16(wstring str);

		//************************************
		// Method:    �� UTF8 �ַ����ж�ȡ GB2312 �ַ���
		// Parameter: str:	UTF8�ַ���
		//************************************
		static string FromUTF8(wstring str);

		//************************************
		// Method:    �� UTF8 �ַ����ж�ȡ GB2312 �ַ���
		// Parameter: str:	UTF8�ַ���
		//************************************
		static string FromUTF8(string str);

		//************************************
		// Method:    ��ȡ�ַ����ֽڳ���(������������)
		//************************************
		static int GetByteCount(string str);

		//************************************
		// Method:    д�뵽��������
		// Return:	  д�뻺�����ĳ���
		// Parameter: BYTE * pBuf:	������ָ��
		// Parameter: hasEndChar:	�Ƿ�д�������
		//************************************
		static int ToBuf(string str, BYTE* pBuf, bool hasEndChar = false);

	private:

	};
}