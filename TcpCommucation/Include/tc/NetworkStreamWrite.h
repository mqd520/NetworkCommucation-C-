#pragma once

#include <vector>
#include "NCTool.h"

using namespace std;

namespace tc
{
	/************************************************************************/
	/* 网络流(只写)类
	/************************************************************************/
	class NetworkStreamWrite
	{
	public:
		//************************************
		// Parameter: BYTE * pBuf:		缓冲区指针
		// Parameter: int len:			缓冲区长度
		// Parameter: EByteOrder bo:	网络流所使用的字节序 	
		//************************************
		NetworkStreamWrite(BYTE* pBuf, int len, EByteOrder bo = EByteOrder::big);
		~NetworkStreamWrite();

	private:
		EByteOrder nsByteOrder;		// 当前网络流使用的字节序
		int nBuffLen;				// 缓冲区长度
		BYTE* pBuff;				// 缓冲区
		int nWriteIndex;			// 数据写索引

	private:
		//************************************
		// Method:    写入数据
		// Returns:   是否写入成功
		// Parameter: void* pDest:	数据地址
		// Parameter: int len:		数据字节长度
		//************************************
		bool WriteData(void* pData, int len);

		//************************************
		// Method:    写入字符串前缀
		// Returns:   是否写入成功
		// Parameter: int prefix：	前缀所占的字节长度
		// Parameter: int len：		字符串字节长度
		//************************************
		void WriteStrPrefix(int prefix, int len);

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
		// Returns:	  是否写入成功
		//************************************
		bool WriteByte(BYTE val);

		//************************************
		// Method:    写入一个 short 数据
		// Returns:	  是否写入成功
		//************************************
		bool WriteShort(short val);

		//************************************
		// Method:    写入一个 USHORT 数据
		// Returns:	  是否写入成功
		//************************************
		bool WriteUShort(USHORT val);

		//************************************
		// Method:    写入一个 INT16 数据
		// Returns:	  是否写入成功
		//************************************
		bool WriteInt16(INT16 val);

		//************************************
		// Method:    写入一个 UINT16 数据
		// Returns:	  是否写入成功
		//************************************
		bool WriteUInt16(UINT16 val);

		//************************************
		// Method:    写入一个 INT32 数据
		// Returns:	  是否写入成功
		//************************************
		bool WriteInt32(INT32 val);

		//************************************
		// Method:    写入一个 UINT32 数据
		// Returns:	  是否写入成功
		//************************************
		bool WriteUInt32(UINT32 val);

		//************************************
		// Method:    写入一个 INT64 数据
		// Returns:	  是否写入成功
		//************************************
		bool WriteInt64(INT64 val);

		//************************************
		// Method:    写入一个 UINT64 数据
		// Returns:	  是否写入成功
		//************************************
		bool WriteUInt64(UINT64 val);

		//************************************
		// Method:    写入一个 float 数据
		// Returns:	  是否写入成功
		//************************************
		bool WriteFloat(float val);

		//************************************
		// Method:    写入一个 double 数据
		// Returns:	  是否写入成功
		//************************************
		bool WriteDouble(double val);

		//************************************
		// Method:    写入 GB2312 字符串
		// Returns:	  是否写入成功
		// Parameter: string str:		GB2312 字符串
		// Parameter: int prefix:		字符串字节长度前缀所占字节, 范围: 1, 2, 4, 0: 不使用前缀
		// Parameter: bool hasEndChar:	是否将结束符写入
		// Parameter: bool isPrefixContainEndChar:	前缀的值是否包含结束符
		//************************************
		bool WriteGB2312Str(string str, int prefix = 4, bool hasEndChar = true, bool isPrefixContainEndChar = true);

		//************************************
		// Method:    写入 UTF16 字符串
		// Returns:	  是否写入成功
		// Parameter: string str:		UTF16 字符串
		// Parameter: int prefix:		字符串字节长度前缀所占字节, 范围: 1, 2, 4, 0: 不使用前缀
		// Parameter: bool hasEndChar:	是否将结束符写入
		// Parameter: bool isPrefixContainEndChar:	前缀的值是否包含结束符
		//************************************
		bool WriteUTF16Str(wstring str, int prefix = 4, bool hasEndChar = true, bool isPrefixContainEndChar = true);

		//************************************
		// Method:    写入 UTF8 字符串
		// Returns:	  是否写入成功
		// Parameter: string str:		UTF8 字符串
		// Parameter: int prefix:		字符串字节长度前缀所占字节, 范围: 1, 2, 4, 0: 不使用前缀
		// Parameter: bool hasEndChar:	是否将结束符写入
		// Parameter: bool isPrefixContainEndChar:	是否将结束符写入
		//************************************
		bool WriteUTF8Str(string str, int prefix = 4, bool hasEndChar = true, bool isPrefixContainEndChar = true);
	};
}