#pragma once

namespace TCPCommunication
{
	class CByteStream
	{
	private:
		int m_streamLen;//�ֽ�������
		BYTE* m_buf;//������ָ��
		int m_nPosition;//���ݽ�βλ��,����,0��ʼ
		int m_dataLen;//���ݳ���

	public:
		CByteStream(int len);
		~CByteStream();

		//************************************
		// Method:    ��ȡ����ǰλ��
		// FullName:  MemoryTool::CByteStream::GetPosition
		// Access:    public 
		// Returns:   int
		// Qualifier:
		//************************************
		int GetPosition();

		//************************************
		// Method:    ��������ǰλ��
		// FullName:  MemoryTool::CByteStream::SetPosition
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: ��ǰλ��
		//************************************
		void SetPosition(int pos);

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
		// Method:    �ӵ�ǰ����ָ��λ�ö�ȡָ�����ȵ�����,ʵ�ʶ�ȡ���ȿ���С��Ԥ�ƶ�ȡ����
		// FullName:  MemoryTool::CByteStream::Read
		// Access:    public 
		// Returns:   ��ȡ���Ļ�����ָ��
		// Qualifier:
		// Parameter: ��ʼλ��(������,1��ʼ)
		// Parameter: Ԥ�ƶ�ȡ�����ݳ���
		// Parameter: ʵ�ʶ�ȡ�����ݳ���(���)
		//************************************
		BYTE* Read(int start, int len, int* readLen);

		//************************************
		// Method:    �ӵ�ǰ���п�ʼλ�ö�ȡָ�����ȵ�����,ʵ�ʶ�ȡ���ȿ���С��Ԥ�ƶ�ȡ����
		// FullName:  MemoryTool::CByteStream::Read
		// Access:    public 
		// Returns:   ��ȡ���Ļ�����ָ��
		// Qualifier:
		// Parameter: Ԥ�ƶ�ȡ�����ݳ���
		// Parameter: ʵ�ʶ�ȡ�����ݳ���(���)
		//************************************
		BYTE* Read(int len, int* readLen);

		//************************************
		// Method:    �ӵ�ǰ���п�ʼλ�ö�ȡָ�����ȵ�����,��������ݳ��Ȳ���,�����ж�ȡ����
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
		// Method:    ����ƽ��
		// FullName:  MemoryTool::CByteStreamTransform::Left
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: ��ʼλ��,������,1��ʼ
		// Parameter: ��Ҫƽ�Ƶ��ֽڳ���
		// Parameter: ƽ�Ƴ���
		//************************************
		void Left(int start, int size, int len);
	};
}