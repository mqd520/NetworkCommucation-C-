#pragma once

namespace NetworkCommunication
{
	//����������(С�ֽ���)
	class CNetworkStream
	{
	public:
		CNetworkStream(int bufsize = 128);
		~CNetworkStream();

	private:
		int m_nBufLen;//�ֽ����ܳ���
		BYTE* m_pBuf;//�����ֽ���
		int m_nStartIndex;//���ݶ�(д)��ʼ����
		int m_nEndIndex;//���ݶ�(д)��������

	private:
		//���õ���ʼ��״̬
		void Reset();

	public:
		//�ɶ��ֽ���
		int AvaliableRead();

		//��д�ֽ���
		int AvaliableWrite();

		//д��BYTE����
		bool WriteByte(BYTE val);

		//д��32λint����
		bool WriteInt32(int val);

		//д��short����
		bool WriteShort(short val);

		//�����ж�ȡ����������
		int ReadBuf(BYTE* buf, int len);

		//д�뻺��������
		int WriteBuf(BYTE* buf, int len);

		//��ȡBYTE����
		BYTE ReadByte();

		//��ȡint32����
		int ReadInt32();

		//��ȡshort����
		short ReadShort();

		//д����ֽ��ַ���
		bool WriteMultiStr(char* str);

		//д��UTF-8�ַ���
		bool WriteUTF8Str(wchar_t* str);

		//��ָ�������ж�ȡ���ֽ��ַ���
		char* ReadMultiStr(int len);

		//��ָ�������ж�ȡUTF8�ַ���
		wchar_t* ReadUTF8Str(int len);
	};

	class MyClass
	{
	public:
		MyClass();
		~MyClass();
	};
}