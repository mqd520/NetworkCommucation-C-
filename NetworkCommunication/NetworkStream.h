#pragma once

namespace NetworkCommunication
{
	//����������
	class CNetworkStream
	{
	public:
		CNetworkStream(BYTE* pBuf, int len, bool bigEndian = true);
		~CNetworkStream();

	private:
		bool m_bHostBigEndian;//�����Ƿ���ô���ֽ���
		bool m_bNetBigEndian;//�������Ƿ���ô���ֽ���
		int m_nBufLen;//����������
		BYTE* m_pBuf;//������
		bool m_bDelete;//�Ƿ���Ҫ�����ͷŻ�����
		int m_nReadIndex;//���ݶ�(д)��ʼ����
		int m_nWriteIndex;//���ݶ�(д)��������

	private:
		bool ReadData(void* pDest, int len);

	public:
		//************************************
		// Method:    ���ػ���������
		//************************************
		int GetLen();

		//************************************
		// Method:    ���ػ�����ָ��
		//************************************
		BYTE* GetBuf();

		//************************************
		// Method:    ���ؿɶ����ֽ���
		//************************************
		int AvaliableRead();

		int AvaliableReadIndex();

		//************************************
		// Method:    ��ȡһ�λ���������
		// Returns:	  ʵ�ʶ�ȡ����
		// Parameter: ���ջ�����
		// Parameter: Ԥ�ƶ�ȡ����
		//************************************
		int ReadBuf(BYTE* buf, int len);

		//************************************
		// Method:    ��ȡһ��BYTE����
		//************************************
		BYTE ReadByte();

		//************************************
		// Method:    ��ȡһ��USHORT����
		//************************************
		USHORT ReadUShort();

		//************************************
		// Method:    ��ȡһ��UINT����
		//************************************
		UINT ReadUInt();

		//************************************
		// Method:    ��ȡһ��UINT16����
		//************************************
		UINT16 ReadUInt16();

		//************************************
		// Method:    ��ȡһ��UINT64����
		//************************************
		UINT64 ReadUInt64();

		//************************************
		// Method:    ��ȡһ��short����
		//************************************
		short ReadShort();

		//************************************
		// Method:    ��ȡһ��int����
		//************************************
		int ReadInt();

		//************************************
		// Method:    ��ȡһ��INT16����
		//************************************
		INT16 ReadInt16();

		//************************************
		// Method:    ��ȡһ��INT64����
		//************************************
		INT64 ReadInt64();

		//************************************
		// Method:    ��ȡһ��float����
		//************************************
		float ReadFloat();

		//************************************
		// Method:    ��ȡһ��double����
		//************************************
		double ReadDouble();

		//************************************
		// Method:    ��ȡ���ֽ��ַ���
		// Parameter: �ַ���ָ��
		// Parameter: ��ȡ�ֽڳ���
		//************************************
		bool ReadMultiByteStr(char* dest, int len);

		//************************************
		// Method:    ��ȡUTF16�ַ���
		// Parameter: �ַ���ָ��
		// Parameter: ��ȡ�ֽڳ���
		//************************************
		bool ReadUTF16Str(wchar_t* dest, int len);

		//************************************
		// Method:    ��ȡUTF8�ַ���
		// Parameter: �ַ���ָ��
		// Parameter: ��ȡ�ֽڳ���
		//************************************
		bool ReadUTF8Str(wchar_t* dest, int len);

		//************************************
		// Method:    ���ؿ�д���ֽ���
		//************************************
		int AvaliableWrite();

		//************************************
		// Method:    д��һ�λ���������
		// Returns:	  ʵ��д�볤��
		// Parameter: ������
		// Parameter: Ԥ��д�볤��
		//************************************
		int WriteBuf(BYTE* buf, int len);

		//д��BYTE����
		bool WriteByte(BYTE val);

		//д��32λint����
		bool WriteInt32(int val);

		bool WriteSignInt32(int val);

		//д��64λint����
		bool WriteInt64(INT64 val);

		//д��short����
		bool WriteShort(short val);

		//д�뻺��������
		int Write(BYTE* buf, int len);

		//д����ֽ��ַ���
		bool WriteMultiStr(char* str);

		//д��UTF-8�ַ���
		bool WriteUTF8Str(wchar_t* str);
	};
}