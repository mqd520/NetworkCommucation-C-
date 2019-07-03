#include "stdafx.h"
#include "Include/tc/NetworkStreamWrite.h"
#include "Include/tc/GB2312Str.h"
#include "Include/tc/UTF16Str.h"

using namespace tc;

NetworkStreamWrite::NetworkStreamWrite(BYTE* pBuf, int len, EByteOrder bo /*= EByteOrder::big*/) :
pBuff(pBuf),
nBuffLen(len),
nsByteOrder(bo),
nWriteIndex(0)
{

}

NetworkStreamWrite::~NetworkStreamWrite()
{

}

bool NetworkStreamWrite::WriteData(void* pData, int len)
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

void NetworkStreamWrite::WriteStrPrefix(int prefix, int len)
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

int NetworkStreamWrite::GetLen()
{
	return nBuffLen;
}

BYTE* NetworkStreamWrite::GetBuf()
{
	return pBuff;
}

int NetworkStreamWrite::AvaliableWrite()
{
	return nBuffLen - nWriteIndex;
}

int NetworkStreamWrite::WritedCount()
{
	return nWriteIndex;
}

bool NetworkStreamWrite::WriteBuf(BYTE* pBuf, int len)
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

bool NetworkStreamWrite::WriteByte(BYTE val)
{
	return WriteData(&val, sizeof(BYTE));
}

bool NetworkStreamWrite::WriteShort(short val)
{
	return WriteData(&val, sizeof(short));
}

bool NetworkStreamWrite::WriteUShort(USHORT val)
{
	return WriteData(&val, sizeof(USHORT));
}

bool NetworkStreamWrite::WriteInt16(INT16 val)
{
	return WriteData(&val, sizeof(INT16));
}

bool NetworkStreamWrite::WriteUInt16(UINT16 val)
{
	return WriteData(&val, sizeof(UINT16));
}

bool NetworkStreamWrite::WriteInt32(INT32 val)
{
	return WriteData(&val, sizeof(INT32));
}

bool NetworkStreamWrite::WriteUInt32(UINT32 val)
{
	return WriteData(&val, sizeof(UINT32));
}

bool NetworkStreamWrite::WriteInt64(INT64 val)
{
	return WriteData(&val, sizeof(INT64));
}

bool NetworkStreamWrite::WriteUInt64(UINT64 val)
{
	return WriteData(&val, sizeof(UINT64));
}

bool NetworkStreamWrite::WriteFloat(float val)
{
	return WriteData(&val, sizeof(float));
}

bool NetworkStreamWrite::WriteDouble(double val)
{
	return WriteData(&val, sizeof(double));
}

bool NetworkStreamWrite::WriteGB2312Str(string str, int prefix /*= 4*/, bool hasEndChar /*= false*/)
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

bool NetworkStreamWrite::WriteUTF16Str(wstring str, int prefix /*= 4*/, bool hasEndChar /*= false*/)
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

bool NetworkStreamWrite::WriteUTF8Str(string str, int prefix /*= 4*/, bool hasEndChar /*= false*/)
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
