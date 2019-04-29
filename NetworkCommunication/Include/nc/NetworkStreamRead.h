#pragma once

#include "NCTool.h"

namespace NetworkCommunication
{
	/************************************************************************/
	/* ������(ֻ��)��
	/************************************************************************/
	class CNetworkStreamRead
	{
	public:
		//************************************
		// Method:    CNetworkStream
		// FullName:  NetworkCommunication::CNetworkStream::CNetworkStream
		// Access:    public 
		// Returns:   
		// Qualifier: 
		// Parameter: BYTE * pBuf:	������ָ��
		// Parameter: int len:		����������
		// Parameter: EByteOrder bo:��������ʹ�õ��ֽ��� 	
		//************************************
		CNetworkStreamRead(BYTE* pBuf, int len, EByteOrder bo = EByteOrder::big);
		~CNetworkStreamRead();

	private:
		EByteOrder m_bNSByteOrder;		// ��ǰ������ʹ�õ��ֽ���
		int m_nBufLen;					// ����������
		BYTE* m_pBuf;					// ������
		int m_nReadIndex;				// ���ݶ�(д)��ʼ����

	private:
		//************************************
		// Method:    ��ת������
		// Access:    private 
		// Returns:   bool
		// Parameter: BYTE * pBuf: ������ָ��
		// Parameter: int len:	   ����������
		//************************************
		void ReverseBuf(BYTE* pBuf, int len);

		//************************************
		// Method:    ��ȡ����
		// Access:    private 
		// Returns:   bool
		// Parameter: void * pDest:	���ݽ��յ�ַ
		// Parameter: int len:		��ȡ����
		//************************************
		bool ReadData(void* pDest, int len);

		//************************************
		// Method:    ��ȡ�ַ���ǰ׺
		// Returns:   int:	�ַ����ֽڳ���
		// Parameter: ǰ׺��ռ���ֽڳ���
		//************************************
		UINT32 ReadStrPrefix(int len);

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

		//************************************
		// Method:    �����Ѷ��ֽ���
		//************************************
		int ReadedCount();

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
		// Method:    ��ȡһ��SHORT����
		//************************************
		SHORT ReadShort();

		//************************************
		// Method:    ��ȡһ��USHORT����
		//************************************
		USHORT ReadUShort();

		//************************************
		// Method:    ��ȡһ��int16����
		//************************************
		INT16 ReadInt16();

		//************************************
		// Method:    ��ȡһ��uint16����
		//************************************
		UINT16 ReadUInt16();

		//************************************
		// Method:    ��ȡһ��INT32����
		//************************************
		INT32 ReadInt32();

		//************************************
		// Method:    ��ȡһ��UINT32����
		//************************************
		UINT32 ReadUInt32();

		//************************************
		// Method:    ��ȡһ��INT64����
		//************************************
		INT64 ReadInt64();

		//************************************
		// Method:    ��ȡһ��UINT64����
		//************************************
		UINT64 ReadUInt64();

		//************************************
		// Method:    ��ȡһ��float����
		//************************************
		float ReadFloat();

		//************************************
		// Method:    ��ȡһ��double����
		//************************************
		double ReadDouble();

		//************************************
		// Method:    ��ȡGB2312�ַ���
		// Parameter: char* pDest:				�ַ���ָ��
		// Parameter: int len:					��ȡ�ֽڳ���
		// Parameter: bool hasEndChar = false:	�����Ƿ�����ַ���������'\0'
		//************************************
		bool ReadGB2312Str(char* pDest, int len, bool hasEndChar = false);

		//************************************
		// Method:    ��ȡGB2312�ַ���
		// Parameter: char* pDest:				�ַ���ָ��
		// Parameter: int prefixLen = 4:		˵���ַ����ֽڳ��ȵ�ǰ׺������ռ�ֽڳ���, ȡֵ��Χ: 1-4
		// Parameter: bool hasEndChar = false:	�����Ƿ�����ַ���������'\0'
		//************************************
		bool ReadGB2312Str(char* pDest, unsigned int prefixLen = 4, bool hasEndChar = false);

		//************************************
		// Method:    ��ȡUTF16�ַ���
		// Parameter: wchar_t* pDest:			�ַ���ָ��
		// Parameter: int len:					��ȡ�ֽڳ���
		// Parameter: bool hasEndChar = false:	�����Ƿ�����ַ���������'\0'
		//************************************
		bool ReadUTF16Str(wchar_t* pDest, int len, bool hasEndChar = false);

		//************************************
		// Method:    ��ȡUTF16�ַ���
		// Parameter: wchar_t* pDest:			�ַ���ָ��
		// Parameter: int prefixLen = 4:		˵���ַ����ֽڳ��ȵ�ǰ׺������ռ�ֽڳ���, ȡֵ��Χ: 1-4
		// Parameter: bool hasEndChar = false:	�����Ƿ�����ַ���������'\0'
		//************************************
		bool ReadUTF16Str(wchar_t* pDest, unsigned int prefixLen = 4, bool hasEndChar = false);

		//************************************
		// Method:    ��ȡUT8�ַ���
		// Parameter: wchar_t* pDest:			�ַ���ָ��
		// Parameter: int len:					��ȡ�ֽڳ���
		// Parameter: bool hasEndChar = false:	�����Ƿ�����ַ���������'\0'
		//************************************
		bool ReadUTF8Str(wchar_t* pDest, int len, bool hasEndChar = false);
	};
}