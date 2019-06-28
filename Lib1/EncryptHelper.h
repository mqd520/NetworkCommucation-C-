#pragma once

namespace lib1
{
	// 加密类
	class EncryptHelper
	{
	public:
		EncryptHelper();
		~EncryptHelper();

	public:
		//************************************
		// Method:    缓冲区加密
		// Parameter: char * pBuf
		// Parameter: int len
		//************************************
		static BYTE Encrypt(char* pBuf, int len);

		//************************************
		// Method:    缓冲区解密
		// Parameter: char * pBuf
		// Parameter: int len
		// Parameter: BYTE code
		//************************************
		static bool Decrypt(char* pBuf, int len, BYTE code);
	};
}