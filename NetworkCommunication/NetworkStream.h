#pragma once

namespace NetworkCommunication
{
	//网络流处理
	class CNetworkStream
	{
	public:
		CNetworkStream(BYTE* pBuf, int len, bool bigEndian = true);
		~CNetworkStream();

	private:
		bool m_bHostBigEndian;//主机是否采用大端字节序
		bool m_bNetBigEndian;//网络流是否采用大端字节序
		int m_nBufLen;//缓冲区长度
		BYTE* m_pBuf;//缓冲区
		bool m_bDelete;//是否需要主动释放缓冲区
		int m_nReadIndex;//数据读(写)开始索引
		int m_nWriteIndex;//数据读(写)结束索引

	private:
		bool ReadData(void* pDest, int len);

	public:
		//************************************
		// Method:    返回缓冲区长度
		//************************************
		int GetLen();

		//************************************
		// Method:    返回缓冲区指针
		//************************************
		BYTE* GetBuf();

		//************************************
		// Method:    返回可读的字节数
		//************************************
		int AvaliableRead();

		int AvaliableReadIndex();

		//************************************
		// Method:    读取一段缓冲区数据
		// Returns:	  实际读取长度
		// Parameter: 接收缓冲区
		// Parameter: 预计读取长度
		//************************************
		int ReadBuf(BYTE* buf, int len);

		//************************************
		// Method:    读取一个BYTE数据
		//************************************
		BYTE ReadByte();

		//************************************
		// Method:    读取一个USHORT数据
		//************************************
		USHORT ReadUShort();

		//************************************
		// Method:    读取一个UINT数据
		//************************************
		UINT ReadUInt();

		//************************************
		// Method:    读取一个UINT16数据
		//************************************
		UINT16 ReadUInt16();

		//************************************
		// Method:    读取一个UINT64数据
		//************************************
		UINT64 ReadUInt64();

		//************************************
		// Method:    读取一个short数据
		//************************************
		short ReadShort();

		//************************************
		// Method:    读取一个int数据
		//************************************
		int ReadInt();

		//************************************
		// Method:    读取一个INT16数据
		//************************************
		INT16 ReadInt16();

		//************************************
		// Method:    读取一个INT64数据
		//************************************
		INT64 ReadInt64();

		//************************************
		// Method:    读取一个float数据
		//************************************
		float ReadFloat();

		//************************************
		// Method:    读取一个double数据
		//************************************
		double ReadDouble();

		//************************************
		// Method:    读取多字节字符串
		// Parameter: 字符串指针
		// Parameter: 读取字节长度
		//************************************
		bool ReadMultiByteStr(char* dest, int len);

		//************************************
		// Method:    读取UTF16字符串
		// Parameter: 字符串指针
		// Parameter: 读取字节长度
		//************************************
		bool ReadUTF16Str(wchar_t* dest, int len);

		//************************************
		// Method:    读取UTF8字符串
		// Parameter: 字符串指针
		// Parameter: 读取字节长度
		//************************************
		bool ReadUTF8Str(wchar_t* dest, int len);

		//************************************
		// Method:    返回可写的字节数
		//************************************
		int AvaliableWrite();

		//************************************
		// Method:    写入一段缓冲区数据
		// Returns:	  实际写入长度
		// Parameter: 缓冲区
		// Parameter: 预计写入长度
		//************************************
		int WriteBuf(BYTE* buf, int len);

		//写入BYTE数据
		bool WriteByte(BYTE val);

		//写入32位int数据
		bool WriteInt32(int val);

		bool WriteSignInt32(int val);

		//写入64位int数据
		bool WriteInt64(INT64 val);

		//写入short数据
		bool WriteShort(short val);

		//写入缓冲区数据
		int Write(BYTE* buf, int len);

		//写入多字节字符串
		bool WriteMultiStr(char* str);

		//写入UTF-8字符串
		bool WriteUTF8Str(wchar_t* str);
	};
}