#pragma once

namespace NetworkCommunication
{
	//************************************
	// Method:    UTF8字节流转UTF16字节流
	// Returns:	  返回UTF16字节总数
	// Parameter: UTF8字节流缓冲区
	// Parameter: UTF8字节流长度
	// Parameter: UTF16字节流缓冲区
	// Parameter: UTF16字节流是否采用大端字节序,默认大端
	//************************************
	int UTF8ByteToUTF16Byte(BYTE* pBufSrc, int len, BYTE* pBufDest, bool bBigEndian = true);
}