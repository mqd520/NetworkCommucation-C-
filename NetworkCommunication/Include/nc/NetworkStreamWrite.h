#pragma once

#include <vector>
#include "NCTool.h"

using namespace std;

namespace NetworkCommunication
{
	/************************************************************************/
	/* 网络流(只写)类
	/************************************************************************/
	class CNetworkStreamWrite
	{
	public:
		//************************************
		// Parameter: BYTE * pBuf:	缓冲区指针
		// Parameter: int len:		缓冲区长度
		// Parameter: EByteOrder bo:网络流所使用的字节序 	
		//************************************
		CNetworkStreamWrite(BYTE* pBuf, int len, EByteOrder bo = EByteOrder::big);
		~CNetworkStreamWrite();

	private:
		EByteOrder m_bNSByteOrder;		// 当前网络流使用的字节序
		int m_nBufLen;					// 缓冲区长度
		BYTE* m_pBuf;					// 缓冲区
		int m_nWriteIndex;				// 数据写索引

	private:
		//************************************
		// Method:    写入数据
		// Parameter: void * pDest:	数据接收地址
		// Parameter: int len:		读取长度
		//************************************
		bool WriteData(void* pDest, int len);

		//************************************
		// Method:    写入字符串前缀
		// Returns:   是否写入成功
		// Parameter: int prefix：	前缀所占的字节长度
		// Parameter: int val：		前缀数据
		//************************************
		bool WriteStrPrefix(int prefix, int val);

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
		// Method:    返回可写的字节数
		//************************************
		int AvaliableWrite();

		//************************************
		// Method:    返回已写字节数
		//************************************
		int WritedCount();

		//************************************
		// Method:    写入一段缓冲区数据
		// Returns:	  是否写入成功
		// Parameter: BYTE* pBuf:	数据缓冲区
		// Parameter: int len:		数据缓冲区长度
		//************************************
		bool WriteBuf(BYTE* pBuf, int len);

		//************************************
		// Method:    写入一个 BYTE 数据
		//************************************
		bool WriteByte(BYTE val);

		//************************************
		// Method:    写入一个 short 数据
		//************************************
		bool WriteShort(short val);

		//************************************
		// Method:    写入一个 USHORT 数据
		//************************************
		bool WriteUShort(USHORT val);

		//************************************
		// Method:    写入一个 INT16 数据
		//************************************
		bool WriteInt16(INT16 val);

		//************************************
		// Method:    写入一个 UINT16 数据
		//************************************
		bool WriteUInt16(UINT16 val);

		//************************************
		// Method:    写入一个 INT32 数据
		//************************************
		bool WriteInt32(INT32 val);

		//************************************
		// Method:    写入一个 UINT32 数据
		//************************************
		bool WriteUInt32(UINT32 val);

		//************************************
		// Method:    写入一个 INT64 数据
		//************************************
		bool WriteInt64(INT64 val);

		//************************************
		// Method:    写入一个 UINT64 数据
		//************************************
		bool WriteUInt64(UINT64 val);

		//************************************
		// Method:    写入一个 float 数据
		//************************************
		bool WriteFloat(float val);

		//************************************
		// Method:    写入一个 double 数据
		//************************************
		bool WriteDouble(double val);

		//************************************
		// Method:    读取 GB2312 字符串
		// Parameter: int len:					读取字节长度
		//************************************
		string WriteGB2312Str(int len);

		//************************************
		// Method:    读取 GB2312 字符串
		// Parameter: int prefixLen = 4:		说明字符串字节长度的前缀数据所占字节长度, 取值范围: 1-4
		//************************************
		string WriteGB2312Str1(int prefixLen = 4);

		//************************************
		// Method:    读取 UTF16 字符串
		// Parameter: int len:					读取字节长度
		//************************************
		wstring WriteUTF16Str(int len);

		//************************************
		// Method:    读取 UTF16 字符串
		// Parameter: int prefixLen = 4:		说明字符串字节长度的前缀数据所占字节长度, 取值范围: 1-4
		//************************************
		wstring WriteUTF16Str1(int prefixLen = 4);

		//************************************
		// Method:    读取 UT8 字符串, 自动转换成 GB2312 字符串 
		// Parameter: int len:					读取字节长度
		//************************************
		string WriteUTF8Str(int len);

		//************************************
		// Method:    读取 UTF16 字符串
		// Parameter: int prefixLen = 4:		说明字符串字节长度的前缀数据所占字节长度, 取值范围: 1-4
		//************************************
		string WriteUTF8Str1(int prefixLen = 4);
	};
}