#pragma once

namespace NetworkCommunication
{
	//�ֽ�������:
	//�ӿ�ʼ����ȡ(��ȡ����������������ǰƽ��),�ӽ�β��д��
	class CByteStream
	{
	protected:
		int m_nStreamLen;//�ֽ�������
		BYTE* m_buf;//������ָ��
		int m_nDataEndPos;//���ݽ�β����

	public:
		CByteStream(int len);

	protected:
		//************************************
		// Method:    ����ƽ��
		// FullName:  MemoryTool::CByteStreamTransform::Left
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: ��ʼ����
		// Parameter: ��Ҫƽ�Ƶ��ֽڳ���
		// Parameter: ƽ�ƾ���
		//************************************
		void Left(int start, int len, int space);

		//************************************
		// Method:    ����ʵ��д�볤��
		// FullName:  NetworkCommunication::CByteStream::CalcActualLen
		// Access:    protected 
		// Returns:   ʵ��д�볤��
		// Qualifier:
		// Parameter: Ԥ��д�볤��
		//************************************
		int CalcActualLen(int len);

	public:
		~CByteStream();

		//************************************
		// Method:    ��ȡ��ǰ�����ݳ���
		// FullName:  MemoryTool::CByteStream::GetDataLen
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		int GetDataLen();

		//************************************
		// Method:    ��ȡ�ֽ�����С
		// FullName:  NetworkCommunication::CByteStream::GetBufLen
		// Access:    public 
		// Returns:   int
		// Qualifier:
		//************************************
		int GetBufLen();

		//************************************
		// Method:    ��ȡ��ǰ�����󻺳���ָ��
		// FullName:  MemoryTool::CByteStream::GetBuf
		// Access:    public 
		// Returns:   BYTE*
		// Qualifier:
		//************************************
		BYTE* GetBuf();

		//************************************
		// Method:    �ӵ�ǰ���п�ʼλ�ö�ȡָ�����ȵ�����,ʵ�ʶ�ȡ���ȿ���С��Ԥ�ƶ�ȡ����
		// FullName:  MemoryTool::CByteStream::Read
		// Access:    public 
		// Returns:   ��ȡ���Ļ�����ָ��
		// Qualifier:
		// Parameter: Ԥ�ƶ�ȡ�����ݳ���
		// Parameter: ʵ�ʶ�ȡ�����ݳ���(���)
		//************************************
		BYTE* Read(int len, int* actualLen);

		//************************************
		// Method:    �ӵ�ǰ���п�ʼλ�ö�ȡָ�����ȵ�����,������ݳ��Ȳ���,�����ж�ȡ����
		// FullName:  MemoryTool::CByteStream::Read
		// Access:    public 
		// Returns:   ��ȡ���Ļ�����ָ��
		// Qualifier:
		// Parameter: ���ݳ���
		//************************************
		BYTE* Read(int len);

		//************************************
		// Method:    ����ĩβд������
		// FullName:  MemoryTool::CByteStream::Write
		// Access:    public 
		// Returns:   ʵ��д���ֽڳ���
		// Qualifier:
		// Parameter: ������
		// Parameter: ����������
		//************************************
		int Write(BYTE buf[], int len);

		//************************************
		// Method:    ��ָ���������ȡ����д�뵽��ǰ�������β
		// FullName:  MemoryTool::CByteStream::Write
		// Access:    public 
		// Returns:   ʵ��д���ֽڳ���
		// Qualifier:
		// Parameter: �ֽ�������
		//************************************
		int Write(CByteStream* p);

		//************************************
		// Method:    �����
		// FullName:  NetworkCommunication::CByteStream::Clean
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void Clean();

		//************************************
		// Method:    ɾ���ӿ�ʼλ��ָ�����ȵ��ֽ�����,���������Զ�ƽ��
		// FullName:  NetworkCommunication::CByteStream::Detele
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: ָ������
		//************************************
		void Detele(int len);

		//************************************
		// Method:    ���������Ƿ�����
		// FullName:  NetworkCommunication::CByteStream::IsFull
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		//************************************
		bool IsFull();

		//************************************
		// Method:    ��ȡ���п�д���ֽڳ���
		// FullName:  NetworkCommunication::CByteStream::GetWriteLen
		// Access:    public 
		// Returns:   int
		// Qualifier:
		//************************************
		int GetWriteLen();
	};
}