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

bool NetworkStreamWrite::WriteGB2312Str(string str, int prefix /*= 4*/, bool hasEndChar /*= true*/, bool isPrefixContainEndChar /*= true*/)
{
	bool result = false;

	int len1 = 0;		// 前缀的值
	int len2 = 0;		// 字符串的字节长度, 不包含结束符的字节长度
	int len3 = 0;		// 字符串的字节长度, 包含结束符的字节长度(如果允许写入结束符), 不包含前缀的字节长度

	len2 = GB2312Str::GetByteCount(str);
	len3 = hasEndChar ? len2 + 1 : len2;

	if (hasEndChar && isPrefixContainEndChar)
	{
		len1 = len3;	// 允许写入结束符, 并且前缀需要包含结束符的字节长度
	}
	else
	{
		len1 = len2;	// 只表示字符串字节长度, 不包含结束符
	}

	if ((prefix + len3) <= AvaliableWrite())
	{
		WriteStrPrefix(prefix, len1);	// 写入前缀

		GB2312Str::ToBuf(str, pBuff + nWriteIndex, hasEndChar);
		nWriteIndex += len3;

		result = true;
	}

	return result;
}

bool NetworkStreamWrite::WriteUTF16Str(wstring str, int prefix /*= 4*/, bool hasEndChar /*= true*/, bool isPrefixContainEndChar /*= true*/)
{
	bool result = false;

	int len1 = 0;		// 前缀的值
	int len2 = 0;		// 字符串的字节长度, 不包含结束符的字节长度
	int len3 = 0;		// 字符串的字节长度, 包含结束符的字节长度(如果允许写入结束符), 不包含前缀的字节长度

	len2 = UTF16Str::GetByteCount(str);
	len3 = hasEndChar ? len2 + 2 : len2;

	if (hasEndChar && isPrefixContainEndChar)
	{
		len1 = len3;	// 允许写入结束符, 并且前缀需要包含结束符的字节长度
	}
	else
	{
		len1 = len2;	// 只表示字符串字节长度, 不包含结束符
	}

	if ((prefix + len3) <= AvaliableWrite())
	{
		WriteStrPrefix(prefix, len1);	// 写入前缀

		UTF16Str::ToBuf(str, pBuff + nWriteIndex, nsByteOrder, hasEndChar);
		nWriteIndex += len3;

		result = true;
	}

	return result;
}

bool NetworkStreamWrite::WriteUTF8Str(string str, int prefix /*= 4*/, bool hasEndChar /*= true*/, bool isPrefixContainEndChar /*= true*/)
{
	bool result = false;

	int len1 = 0;		// 前缀的值
	int len2 = 0;		// 字符串的字节长度, 不包含结束符的字节长度
	int len3 = 0;		// 字符串的字节长度, 包含结束符的字节长度(如果允许写入结束符), 不包含前缀的字节长度

	BYTE buf1[1024] = { 0 };
	len3 = GB2312Str::ToUTF8Buf(str, buf1, hasEndChar);
	len2 = hasEndChar ? len3 - 1 : len3;

	if (hasEndChar && isPrefixContainEndChar)
	{
		len1 = len3;	// 允许写入结束符, 并且前缀需要包含结束符的字节长度
	}
	else
	{
		len1 = len2;	// 只表示字符串字节长度, 不包含结束符
	}

	if ((prefix + len3) <= AvaliableWrite())
	{
		WriteStrPrefix(prefix, len1);	// 写入前缀

		memcpy(pBuff + nWriteIndex, buf1, len3);
		nWriteIndex += len3;

		result = true;
	}

	return result;
}
