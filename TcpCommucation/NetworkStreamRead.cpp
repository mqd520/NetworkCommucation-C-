#include "stdafx.h"
#include "Include/tc/NetworkStreamRead.h"
#include "Include/tc/GB2312Str.h"
#include "Include/tc/UTF16Str.h"

using namespace tc;

NetworkStreamRead::NetworkStreamRead(BYTE* pBuf, int len, EByteOrder bo /* = EByteOrder::big */) :
pBuff(pBuf),
nBuffLen(len),
nsByteOrder(bo),
nReadIndex(0)
{

}

NetworkStreamRead::~NetworkStreamRead()
{

}

bool NetworkStreamRead::ReadData(void* pData, int len)
{
	bool result = false;
	if (len <= AvaliableRead())
	{
		memcpy(pData, pBuff + nReadIndex, len);

		if (len > 1 && nsByteOrder != NCTool::GetHostByteOrder())	// 多字节数据
		{
			NCTool::ReverseBuf(pBuff + nReadIndex, len);
		}

		nReadIndex += len;
		result = true;
	}
	return result;
}

UINT32 NetworkStreamRead::ReadStrPrefix(int len)
{
	UINT32 len1 = 0;	// 字符串字节长度

	switch (len)
	{
	case 1:
		len1 = (UINT32)ReadByte();
		break;
	case 2:
		len1 = (UINT32)ReadUShort();
		break;
	case 4:
		len1 = ReadUInt32();
		break;
	}

	return len1;
}

void NetworkStreamRead::SetByteOrder(EByteOrder bo)
{
	nsByteOrder = bo;
}

int NetworkStreamRead::GetLen()
{
	return nBuffLen;
}

BYTE* NetworkStreamRead::GetBuf()
{
	return pBuff;
}

int NetworkStreamRead::AvaliableRead()
{
	return nBuffLen - nReadIndex;
}

int NetworkStreamRead::ReadedCount()
{
	return nReadIndex;
}

int NetworkStreamRead::ReadBuf(BYTE* buf, int len)
{
	if (len <= AvaliableRead())
	{
		memcpy(buf, pBuff + nReadIndex, len);
		nReadIndex += len;

		return true;
	}

	return false;
}

BYTE NetworkStreamRead::ReadByte()
{
	BYTE b = 0;
	ReadData(&b, sizeof(BYTE));
	return b;
}

SHORT NetworkStreamRead::ReadShort()
{
	short s = 0;
	ReadData(&s, sizeof(short));
	return s;
}

USHORT NetworkStreamRead::ReadUShort()
{
	USHORT us = 0;
	ReadData(&us, sizeof(USHORT));
	return us;
}

INT16 NetworkStreamRead::ReadInt16()
{
	INT16 i = 0;
	ReadData(&i, sizeof(INT16));
	return i;
}

UINT16 NetworkStreamRead::ReadUInt16()
{
	UINT16 i = 0;
	ReadData(&i, sizeof(UINT16));
	return i;
}

INT32 NetworkStreamRead::ReadInt32()
{
	INT32 i = 0;
	ReadData(&i, sizeof(INT32));
	return i;
}

UINT32 NetworkStreamRead::ReadUInt32()
{
	UINT32 ui = 0;
	ReadData(&ui, sizeof(UINT32));
	return ui;
}

INT64 NetworkStreamRead::ReadInt64()
{
	INT64 i = 0;
	ReadData(&i, sizeof(INT64));
	return i;
}

UINT64 NetworkStreamRead::ReadUInt64()
{
	UINT64 ui = 0;
	ReadData(&ui, sizeof(UINT64));
	return ui;
}

float NetworkStreamRead::ReadFloat()
{
	float f = 0;
	ReadData(&f, sizeof(float));
	return f;
}

double NetworkStreamRead::ReadDouble()
{
	double d = 0;
	ReadData(&d, sizeof(double));
	return d;
}

string NetworkStreamRead::ReadGB2312Str(int len)
{
	string result = "";

	if (len <= AvaliableRead())
	{
		result = GB2312Str::FromBuf(pBuff + nReadIndex, len);
		nReadIndex += len;
	}

	return result;
}

string NetworkStreamRead::ReadGB2312Str1(int prefixLen /*= 4*/)
{
	string result = "";

	int len = ReadStrPrefix(prefixLen);
	if (len > 0)
	{
		result = ReadGB2312Str(len);
	}

	return result;
}

wstring NetworkStreamRead::ReadUTF16Str(int len)
{
	wstring result = L"";

	if (len <= AvaliableRead())
	{
		result = UTF16Str::FromBuf(pBuff + nReadIndex, len, nsByteOrder);
		nReadIndex += len;
	}

	return result;
}

wstring NetworkStreamRead::ReadUTF16Str1(int prefixLen /*= 4*/)
{
	wstring result = L"";

	int len = ReadStrPrefix(prefixLen);
	if (len > 0)
	{
		return ReadUTF16Str(len);
	}

	return result;
}

string NetworkStreamRead::ReadUTF8Str(int len)
{
	string str = "";

	if (len <= AvaliableRead())
	{
		str = GB2312Str::FromUTF8Buf(pBuff + nReadIndex, len);
		nReadIndex += len;
	}

	return str;
}

string NetworkStreamRead::ReadUTF8Str1(int prefixLen /*= 4*/)
{
	string result = "";

	int len = ReadStrPrefix(prefixLen);
	if (len > 0)
	{
		result = ReadUTF8Str(len);
	}

	return result;
}