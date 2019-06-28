#pragma once

namespace lib1
{
	// ������
	class EncryptHelper
	{
	public:
		EncryptHelper();
		~EncryptHelper();

	public:
		//************************************
		// Method:    ����������
		// Parameter: char * pBuf
		// Parameter: int len
		//************************************
		static BYTE Encrypt(char* pBuf, int len);

		//************************************
		// Method:    ����������
		// Parameter: char * pBuf
		// Parameter: int len
		// Parameter: BYTE code
		//************************************
		static bool Decrypt(char* pBuf, int len, BYTE code);
	};
}