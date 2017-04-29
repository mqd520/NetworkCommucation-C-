#pragma once

namespace NetworkCommunication
{
	//字节流对象:
	//从开始出读取(读取后后面的数据依次向前平移),从结尾处写入
	class CByteStream
	{
	protected:
		int m_nStreamLen;//字节流长度
		BYTE* m_buf;//缓冲区指针
		int m_nDataEndPos;//数据结尾索引

	public:
		CByteStream(int len);

	protected:
		//************************************
		// Method:    向左平移
		// FullName:  MemoryTool::CByteStreamTransform::Left
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: 开始索引
		// Parameter: 需要平移的字节长度
		// Parameter: 平移距离
		//************************************
		void Left(int start, int len, int space);

		//************************************
		// Method:    计算实际写入长度
		// FullName:  NetworkCommunication::CByteStream::CalcActualLen
		// Access:    protected 
		// Returns:   实际写入长度
		// Qualifier:
		// Parameter: 预计写入长度
		//************************************
		int CalcActualLen(int len);

	public:
		~CByteStream();

		//************************************
		// Method:    获取当前流数据长度
		// FullName:  MemoryTool::CByteStream::GetDataLen
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		int GetDataLen();

		//************************************
		// Method:    获取字节流大小
		// FullName:  NetworkCommunication::CByteStream::GetBufLen
		// Access:    public 
		// Returns:   int
		// Qualifier:
		//************************************
		int GetBufLen();

		//************************************
		// Method:    获取当前流对象缓冲区指针
		// FullName:  MemoryTool::CByteStream::GetBuf
		// Access:    public 
		// Returns:   BYTE*
		// Qualifier:
		//************************************
		BYTE* GetBuf();

		//************************************
		// Method:    从当前流中开始位置读取指定长度的数据,实际读取长度可能小于预计读取长度
		// FullName:  MemoryTool::CByteStream::Read
		// Access:    public 
		// Returns:   读取到的缓冲区指针
		// Qualifier:
		// Parameter: 预计读取的数据长度
		// Parameter: 实际读取的数据长度(输出)
		//************************************
		BYTE* Read(int len, int* actualLen);

		//************************************
		// Method:    从当前流中开始位置读取指定长度的数据,如果数据长度不够,不进行读取动作
		// FullName:  MemoryTool::CByteStream::Read
		// Access:    public 
		// Returns:   读取到的缓冲区指针
		// Qualifier:
		// Parameter: 数据长度
		//************************************
		BYTE* Read(int len);

		//************************************
		// Method:    向流末尾写入数据
		// FullName:  MemoryTool::CByteStream::Write
		// Access:    public 
		// Returns:   实际写入字节长度
		// Qualifier:
		// Parameter: 缓冲区
		// Parameter: 缓冲区长度
		//************************************
		int Write(BYTE buf[], int len);

		//************************************
		// Method:    从指定流对象读取数据写入到当前流对象结尾
		// FullName:  MemoryTool::CByteStream::Write
		// Access:    public 
		// Returns:   实际写入字节长度
		// Qualifier:
		// Parameter: 字节流对象
		//************************************
		int Write(CByteStream* p);

		//************************************
		// Method:    清空流
		// FullName:  NetworkCommunication::CByteStream::Clean
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void Clean();

		//************************************
		// Method:    删除从开始位置指定长度的字节数据,后面数据自动平移
		// FullName:  NetworkCommunication::CByteStream::Detele
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: 指定长度
		//************************************
		void Detele(int len);

		//************************************
		// Method:    流中数据是否已满
		// FullName:  NetworkCommunication::CByteStream::IsFull
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		//************************************
		bool IsFull();

		//************************************
		// Method:    获取流中可写入字节长度
		// FullName:  NetworkCommunication::CByteStream::GetWriteLen
		// Access:    public 
		// Returns:   int
		// Qualifier:
		//************************************
		int GetWriteLen();
	};
}