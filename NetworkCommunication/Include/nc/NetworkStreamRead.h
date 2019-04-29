#pragma once

#include "NCTool.h"

namespace NetworkCommunication
{
	/************************************************************************/
	/* 网络流(只读)类
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
		// Parameter: BYTE * pBuf:	缓冲区指针
		// Parameter: int len:		缓冲区长度
		// Parameter: EByteOrder bo:网络流所使用的字节序 	
		//************************************
		CNetworkStreamRead(BYTE* pBuf, int len, EByteOrder bo = EByteOrder::big);
		~CNetworkStreamRead();

	private:
		EByteOrder m_bNSByteOrder;		// 当前网络流使用的字节序
		int m_nBufLen;					// 缓冲区长度
		BYTE* m_pBuf;					// 缓冲区
		int m_nReadIndex;				// 数据读(写)开始索引

	private:
		//************************************
		// Method:    反转缓冲区
		// Access:    private 
		// Returns:   bool
		// Parameter: BYTE * pBuf: 缓冲区指针
		// Parameter: int len:	   缓冲区长度
		//************************************
		void ReverseBuf(BYTE* pBuf, int len);

		//************************************
		// Method:    读取数据
		// Access:    private 
		// Returns:   bool
		// Parameter: void * pDest:	数据接收地址
		// Parameter: int len:		读取长度
		//************************************
		bool ReadData(void* pDest, int len);

		//************************************
		// Method:    读取字符串前缀
		// Returns:   int:	字符串字节长度
		// Parameter: 前缀所占的字节长度
		//************************************
		UINT32 ReadStrPrefix(int len);

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

		//************************************
		// Method:    返回已读字节数
		//************************************
		int ReadedCount();

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
		// Method:    读取一个SHORT数据
		//************************************
		SHORT ReadShort();

		//************************************
		// Method:    读取一个USHORT数据
		//************************************
		USHORT ReadUShort();

		//************************************
		// Method:    读取一个int16数据
		//************************************
		INT16 ReadInt16();

		//************************************
		// Method:    读取一个uint16数据
		//************************************
		UINT16 ReadUInt16();

		//************************************
		// Method:    读取一个INT32数据
		//************************************
		INT32 ReadInt32();

		//************************************
		// Method:    读取一个UINT32数据
		//************************************
		UINT32 ReadUInt32();

		//************************************
		// Method:    读取一个INT64数据
		//************************************
		INT64 ReadInt64();

		//************************************
		// Method:    读取一个UINT64数据
		//************************************
		UINT64 ReadUInt64();

		//************************************
		// Method:    读取一个float数据
		//************************************
		float ReadFloat();

		//************************************
		// Method:    读取一个double数据
		//************************************
		double ReadDouble();

		//************************************
		// Method:    读取GB2312字符串
		// Parameter: char* pDest:				字符串指针
		// Parameter: int len:					读取字节长度
		// Parameter: bool hasEndChar = false:	流中是否带有字符串结束符'\0'
		//************************************
		bool ReadGB2312Str(char* pDest, int len, bool hasEndChar = false);

		//************************************
		// Method:    读取GB2312字符串
		// Parameter: char* pDest:				字符串指针
		// Parameter: int prefixLen = 4:		说明字符串字节长度的前缀数据所占字节长度, 取值范围: 1-4
		// Parameter: bool hasEndChar = false:	流中是否带有字符串结束符'\0'
		//************************************
		bool ReadGB2312Str(char* pDest, unsigned int prefixLen = 4, bool hasEndChar = false);

		//************************************
		// Method:    读取UTF16字符串
		// Parameter: wchar_t* pDest:			字符串指针
		// Parameter: int len:					读取字节长度
		// Parameter: bool hasEndChar = false:	流中是否带有字符串结束符'\0'
		//************************************
		bool ReadUTF16Str(wchar_t* pDest, int len, bool hasEndChar = false);

		//************************************
		// Method:    读取UTF16字符串
		// Parameter: wchar_t* pDest:			字符串指针
		// Parameter: int prefixLen = 4:		说明字符串字节长度的前缀数据所占字节长度, 取值范围: 1-4
		// Parameter: bool hasEndChar = false:	流中是否带有字符串结束符'\0'
		//************************************
		bool ReadUTF16Str(wchar_t* pDest, unsigned int prefixLen = 4, bool hasEndChar = false);

		//************************************
		// Method:    读取UT8字符串
		// Parameter: wchar_t* pDest:			字符串指针
		// Parameter: int len:					读取字节长度
		// Parameter: bool hasEndChar = false:	流中是否带有字符串结束符'\0'
		//************************************
		bool ReadUTF8Str(wchar_t* pDest, int len, bool hasEndChar = false);
	};
}