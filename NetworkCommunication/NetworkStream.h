#pragma once

namespace NetworkCommunication
{
	//网络流对象(小字节序)
	class CNetworkStream
	{
	public:
		CNetworkStream(int bufsize = 128);
		~CNetworkStream();

	private:
		int m_nBufLen;//字节流总长度
		BYTE* m_pBuf;//网络字节序
		int m_nStartIndex;//数据读(写)开始索引
		int m_nEndIndex;//数据读(写)结束索引

	private:
		//重置到初始化状态
		void Reset();

	public:
		//可读字节数
		int AvaliableRead();

		//可写字节数
		int AvaliableWrite();

		//写入BYTE数据
		bool WriteByte(BYTE val);

		//写入32位int数据
		bool WriteInt32(int val);

		//写入short数据
		bool WriteShort(short val);

		//从流中读取缓冲区数据
		int ReadBuf(BYTE* buf, int len);

		//写入缓冲区数据
		int WriteBuf(BYTE* buf, int len);

		//读取BYTE数据
		BYTE ReadByte();

		//读取int32数据
		int ReadInt32();

		//读取short数据
		short ReadShort();

		//写入多字节字符串
		bool WriteMultiStr(char* str);

		//写入UTF-8字符串
		bool WriteUTF8Str(wchar_t* str);

		//从指定长度中读取多字节字符串
		char* ReadMultiStr(int len);

		//从指定长度中读取UTF8字符串
		wchar_t* ReadUTF8Str(int len);
	};

	class MyClass
	{
	public:
		MyClass();
		~MyClass();
	};
}