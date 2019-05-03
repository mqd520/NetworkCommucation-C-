#pragma once

namespace tc
{
	class CEncryptBuffer
	{
	public:
		CEncryptBuffer();
		~CEncryptBuffer();

		//************************************
		// Method:    加密字节缓冲区
		// FullName:  EncryptBuffer::Encrypt
		// Access:    public 
		// Returns:   加密码
		// Qualifier:
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		BYTE Encrypt(BYTE buf[], int len);

		//************************************
		// Method:    解密字节缓冲区
		// FullName:  NetworkCommunication::EncryptBuffer::DeEncrypt
		// Access:    public 
		// Returns:   是否解密成功
		// Qualifier:
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		// Parameter: 加密码
		//************************************
		bool DeEncrypt(BYTE buf[], int len, BYTE code);

	private:
		static const BYTE m_sendByteMap[256];//发送字节映射
		static const BYTE m_recvByteMap[256];//接收字节映射
	};
}