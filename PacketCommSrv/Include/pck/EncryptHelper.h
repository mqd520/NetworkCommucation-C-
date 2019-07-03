#pragma once
#include <minwindef.h>

namespace pck
{
	// 加密类
	class EncryptHelper final
	{
	private:
		EncryptHelper();

	public:
		//************************************
		// Method:    缓冲区加密
		// Parameter: char * pBuf
		// Parameter: int len
		//************************************
		static BYTE Encrypt(BYTE* pBuf, int len);

		//************************************
		// Method:    缓冲区解密
		// Parameter: char * pBuf
		// Parameter: int len
		// Parameter: BYTE code
		//************************************
		static bool Decrypt(BYTE* pBuf, int len, BYTE code);
	};
}