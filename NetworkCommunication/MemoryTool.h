#pragma once

namespace NetworkCommunication
{
	//�ֽ�������:
	//�ӿ�ʼ����ȡ(��ȡ����������������ǰƽ��),�ӽ�β��д��
	class CByteStream
	{
	private:
		int m_streamLen;//�ֽ�������
		BYTE* m_buf;//������ָ��
		int m_nDataEndPos;//���ݽ�β����
		int m_dataLen;//���ݳ���

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
		// Parameter: BYTE buf
		// Parameter: int len
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
	};
}