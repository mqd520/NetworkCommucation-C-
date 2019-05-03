#pragma once

namespace tc
{
	class CEncryptBuffer
	{
	public:
		CEncryptBuffer();
		~CEncryptBuffer();

		//************************************
		// Method:    �����ֽڻ�����
		// FullName:  EncryptBuffer::Encrypt
		// Access:    public 
		// Returns:   ������
		// Qualifier:
		// Parameter: ������
		// Parameter: ����������
		//************************************
		BYTE Encrypt(BYTE buf[], int len);

		//************************************
		// Method:    �����ֽڻ�����
		// FullName:  NetworkCommunication::EncryptBuffer::DeEncrypt
		// Access:    public 
		// Returns:   �Ƿ���ܳɹ�
		// Qualifier:
		// Parameter: ������
		// Parameter: ����������
		// Parameter: ������
		//************************************
		bool DeEncrypt(BYTE buf[], int len, BYTE code);

	private:
		static const BYTE m_sendByteMap[256];//�����ֽ�ӳ��
		static const BYTE m_recvByteMap[256];//�����ֽ�ӳ��
	};
}