#include "stdafx.h"
#include "Include/tc/NetworkStreamWrite.h"
#include "Include/tc/GB2312Str.h"
#include "Include/tc/UTF16Str.h"

using namespace tc;

CNetworkStreamWrite::CNetworkStreamWrite(BYTE* pBuf, int len, EByteOrder bo /*= EByteOrder::big*/) :
pBuff(pBuf),
nBuffLen(len),
nsByteOrder(bo),
nWriteIndex(0)
{

}

CNetworkStreamWrite::~CNetworkStreamWrite()
{

}

bool CNetworkStreamWrite::WriteData(void* pData, int len)
{
	bool result = false;

	if (len <= AvaliableWrite())
	{
		memcpy(pBuff + nWriteIndex, pData, len);

		if (len > 1 && nsByteOrder != NCTool::GetHostByteOrder())	// 多字节数据
		{
			NCTool::ReverseBuf(pBuff + nWriteIndex, len);
		}

		nWriteIndex += len;
		result = true;
	}

	return result;
}

void CNetworkStreamWrite::WriteStrPrefix(int prefix, int len)
{
	switch (prefix)
	{
	case 1:
		WriteByte(len);
		break;
	case 2:
		WriteUShort(len);
		break;
	case 4:
		WriteUInt32(len);
		break;
	}
}

int CNetworkStreamWrite::GetLen()
{
	return nBuffLen;
}

BYTE* CNetworkStreamWrite::GetBuf()
{
	return pBuff;
}

int CNetworkStreamWrite::AvaliableWrite()
{
	return nBuffLen - nWriteIndex;
}

int CNetworkStreamWrite::WritedCount()
{
	return nWriteIndex;
}

bool CNetworkStreamWrite::WriteBuf(BYTE* pBuf, int len)
{
	bool result = false;

	if (len <= AvaliableWrite())
	{
		memcpy(pBuff + nWriteIndex, pBuf, len);
		nWriteIndex += len;
		result = true;
	}

	return result;
}

bool CNetworkStreamWrite::WriteByte(BYTE val)
{
	return WriteData(&val, sizeof(BYTE));
}

bool CNetworkStreamWrite::WriteShort(short val)
{
	return WriteData(&val, sizeof(short));
}

bool CNetworkStreamWrite::WriteUShort(USHORT val)
{
	return WriteData(&val, sizeof(USHORT));
}

bool CNetworkStreamWrite::WriteInt16(INT16 val)
{
	return WriteData(&val, sizeof(INT16));
}

bool CNetworkStreamWrite::WriteUInt16(UINT16 val)
{
	return WriteData(&val, sizeof(UINT16));
}

bool CNetworkStreamWrite::WriteInt32(INT32 val)
{
	return WriteData(&val, sizeof(INT32));
}

bool CNetworkStreamWrite::WriteUInt32(UINT32 val)
{
	return WriteData(&val, sizeof(UINT32));
}

bool CNetworkStreamWrite::WriteInt64(INT64 val)
{
	return WriteData(&val, sizeof(INT64));
}

bool CNetworkStreamWrite::WriteUInt64(UINT64 val)
{
	return WriteData(&val, sizeof(UINT64));
}

bool CNetworkStreamWrite::WriteFloat(float val)
{
	return WriteData(&val, sizeof(float));
}

bool CNetworkStreamWrite::WriteDouble(double val)
{
	return WriteData(&val, sizeof(double));
}

bool CNetworkStreamWrite::WriteGB2312Str(string str, int prefix /*= 4*/, bool hasEndChar /*= false*/)
{
	bool result = false;

	int len = GB2312Str::GetByteCount(str);	// 获取字符串字节长度(不含结束符)
	int count = nWriteIndex;
	WriteStrPrefix(prefix, len);			// 写入前缀
	int len1 = hasEndChar == true ? len + 1 : len;
	if (len1 <= AvaliableWrite())
	{
		GB2312Str::ToBuf(str, pBuff + nWriteIndex, hasEndChar);
		nWriteIndex += len1;
	}
	else
	{
		nWriteIndex = count;
	}

	return result;
}

bool CNetworkStreamWrite::WriteUTF16Str(wstring str, int prefix /*= 4*/, bool hasEndChar /*= false*/)
{
	bool result = false;

	int len = UTF16Str::GetByteCount(str);	// 获取字符串字节长度(不含结束符)
	int count = nWriteIndex;
	WriteStrPrefix(prefix, len);			// 写入前缀
	int len1 = hasEndChar == true ? len + 2 : len;
	if (len1 <= AvaliableWrite())
	{
		UTF16Str::ToBuf(str, pBuff + nWriteIndex, nsByteOrder, hasEndChar);
		nWriteIndex += len1;
	}
	else
	{
		nWriteIndex = count;
	}

	return result;
}

bool CNetworkStreamWrite::WriteUTF8Str(string str, int prefix /*= 4*/, bool hasEndChar /*= false*/)
{
	bool result = false;

	BYTE buf1[1028] = { 0 };
	int len = GB2312Str::ToUTF8Buf(str, buf1, hasEndChar);	// GB2312字符串转换成 UTF8 缓冲区
	int count = nWriteIndex;
	WriteStrPrefix(prefix, len);			// 写入前缀
	if (len <= AvaliableWrite())
	{
		memcpy(pBuff + nWriteIndex, buf1, len);
		nWriteIndex += len;
	}
	else
	{
		nWriteIndex = count;
	}

	return result;
}
