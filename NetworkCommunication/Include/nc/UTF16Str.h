#pragma once

#include "NCTool.h"
#include <string>

using namespace std;

namespace NetworkCommunication
{
	/************************************************************************/
	/* UTF16�ַ�������                                                                     */
	/************************************************************************/
	class UTF16Str
	{
	public:
		UTF16Str();
		~UTF16Str();

		//************************************
		// Method:    �ӻ������ж�ȡ UTF16 �ַ���
		// Parameter: BYTE * pBuf:		������ָ��
		// Parameter: int len:			����������
		// Parameter: EByteOrder bo:	�������ֽ���, Ĭ��: ����ֽ���
		//************************************
		static wstring FromBuf(BYTE* pBuf, int len, EByteOrder bo = EByteOrder::big);

		//************************************
		// Method:    �� UTF8 �ַ����ж�ȡ UTF16 �ַ���
		// Parameter: str:	UTF8�ַ���
		//************************************
		static wstring FromUTF8(wstring str);

		//************************************
		// Method:    �� UTF8 �ַ����ж�ȡ UTF16 �ַ���
		// Parameter: str:	UTF8�ַ���
		//************************************
		static wstring FromUTF8(string str);

		//************************************
		// Method:    �� GB2312 �ַ����ж�ȡ UTF16 �ַ���
		// Parameter: str:	GB2312�ַ���
		//************************************
		static wstring FromGB2312(string str);

		//************************************
		// Method:    ��ȡ�ַ����ֽڳ���
		//************************************
		static int GetByteCount(wstring str);

		//************************************
		// Method:    д�뵽��������
		// Return:	  д�뻺�����ĳ���
		// Parameter: BYTE * pBuf:	������ָ��
		// Parameter: hasEndChar:	�Ƿ�д�������
		// Parameter: EByteOrder bo:�������ֽ���, Ĭ��: ����ֽ���
		//************************************
		static int ToBuf(wstring str, BYTE* pBuf, EByteOrder bo = EByteOrder::big, bool hasEndChar = false);

	private:

	};
}