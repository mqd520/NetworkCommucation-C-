#pragma once

namespace NetworkCommunication
{
	//************************************
	// Method:    UTF8�ֽ���תUTF16�ֽ���
	// Returns:	  ����UTF16�ֽ�����
	// Parameter: UTF8�ֽ���������
	// Parameter: UTF8�ֽ�������
	// Parameter: UTF16�ֽ���������
	// Parameter: UTF16�ֽ����Ƿ���ô���ֽ���,Ĭ�ϴ��
	//************************************
	int UTF8ByteToUTF16Byte(BYTE* pBufSrc, int len, BYTE* pBufDest, bool bBigEndian = true);
}