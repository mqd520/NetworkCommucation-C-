#include "stdafx.h"
#include "Include/nc/NetworkStreamRead.h"
#include "Include/nc/GB2312Str.h"
#include "Include/nc/UTF16Str.h"

using namespace NetworkCommunication;

CNetworkStreamRead::CNetworkStreamRead(BYTE* pBuf, int len, EByteOrder bo /* = EByteOrder::big */) :
pBuff(pBuf),
nBuffLen(len),
nsByteOrder(bo),
nReadIndex(0)
{

}

CNetworkStreamRead::~CNetworkStreamRead()
{

}

bool CNetworkStreamRead::ReadData(void* pData, int len)
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

UINT32 CNetworkStreamRead::ReadStrPrefix(int len)
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

int CNetworkStreamRead::GetLen()
{
	return nBuffLen;
}

BYTE* CNetworkStreamRead::GetBuf()
{
	return pBuff;
}

int CNetworkStreamRead::AvaliableRead()
{
	return nBuffLen - nReadIndex;
}

int CNetworkStreamRead::ReadedCount()
{
	return nReadIndex;
}

int CNetworkStreamRead::ReadBuf(BYTE* buf, int len)
{
	if (len <= AvaliableRead())
	{
		memcpy(buf, pBuff + nReadIndex, len);
		nReadIndex += len;

		return true;
	}

	return false;
}

BYTE CNetworkStreamRead::ReadByte()
{
	BYTE b = 0;
	ReadData(&b, sizeof(BYTE));
	return b;
}

SHORT CNetworkStreamRead::ReadShort()
{
	short s = 0;
	ReadData(&s, sizeof(short));
	return s;
}

USHORT CNetworkStreamRead::ReadUShort()
{
	USHORT us = 0;
	ReadData(&us, sizeof(USHORT));
	return us;
}

INT16 CNetworkStreamRead::ReadInt16()
{
	INT16 i = 0;
	ReadData(&i, sizeof(INT16));
	return i;
}

UINT16 CNetworkStreamRead::ReadUInt16()
{
	UINT16 i = 0;
	ReadData(&i, sizeof(UINT16));
	return i;
}

INT32 CNetworkStreamRead::ReadInt32()
{
	INT32 i = 0;
	ReadData(&i, sizeof(INT32));
	return i;
}

UINT32 CNetworkStreamRead::ReadUInt32()
{
	UINT32 ui = 0;
	ReadData(&ui, sizeof(UINT32));
	return ui;
}

INT64 CNetworkStreamRead::ReadInt64()
{
	INT64 i = 0;
	ReadData(&i, sizeof(INT64));
	return i;
}

UINT64 CNetworkStreamRead::ReadUInt64()
{
	UINT64 ui = 0;
	ReadData(&ui, sizeof(UINT64));
	return ui;
}

float CNetworkStreamRead::ReadFloat()
{
	float f = 0;
	ReadData(&f, sizeof(float));
	return f;
}

double CNetworkStreamRead::ReadDouble()
{
	double d = 0;
	ReadData(&d, sizeof(double));
	return d;
}

string CNetworkStreamRead::ReadGB2312Str(int len)
{
	string result = "";

	if (len <= AvaliableRead())
	{
		result = GB2312Str::FromBuf(pBuff + nReadIndex, len);
		nReadIndex += len;
	}

	return result;
}

string CNetworkStreamRead::ReadGB2312Str1(int prefixLen /*= 4*/)
{
	string result = "";

	int len = ReadStrPrefix(prefixLen);
	if (len > 0)
	{
		result = ReadGB2312Str(len);
	}

	return result;
}

wstring CNetworkStreamRead::ReadUTF16Str(int len)
{
	wstring result = L"";

	if (len <= AvaliableRead())
	{
		result = UTF16Str::FromBuf(pBuff + nReadIndex, len, nsByteOrder);
		nReadIndex += len;
	}

	return result;
}

wstring CNetworkStreamRead::ReadUTF16Str1(int prefixLen /*= 4*/)
{
	wstring result = L"";

	int len = ReadStrPrefix(prefixLen);
	if (len > 0)
	{
		return ReadUTF16Str(len);
	}

	return result;
}

string CNetworkStreamRead::ReadUTF8Str(int len)
{
	string str = "";

	if (len <= AvaliableRead())
	{
		str = GB2312Str::FromUTF8Buf(pBuff + nReadIndex, len);
		nReadIndex += len;
	}

	return str;
}

string CNetworkStreamRead::ReadUTF8Str1(int prefixLen /*= 4*/)
{
	string result = "";

	int len = ReadStrPrefix(prefixLen);
	if (len > 0)
	{
		result = ReadUTF8Str(len);
	}

	return result;
}