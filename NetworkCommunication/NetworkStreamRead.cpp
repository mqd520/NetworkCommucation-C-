#include "stdafx.h"
#include "Include/nc/NetworkStreamRead.h"
#include "Include/nc/StringTool.h"

using namespace NetworkCommunication;

CNetworkStreamRead::CNetworkStreamRead(BYTE* pBuf, int len, EByteOrder bo /* = EByteOrder::big */) :
m_pBuf(pBuf),
m_nBufLen(len),
m_bNSByteOrder(bo),
m_nReadIndex(0)
{

}

CNetworkStreamRead::~CNetworkStreamRead()
{

}

void CNetworkStreamRead::ReverseBuf(BYTE* pBuf, int len)
{
	for (int i = 0; i < len / 2; i++)
	{
		BYTE tmp = pBuf[i];
		pBuf[i] = pBuf[len - 1 - i];
		pBuf[len - 1 - i] = tmp;
	}
}

bool CNetworkStreamRead::ReadData(void* pDest, int len)
{
	bool result = false;
	if (len <= AvaliableRead())
	{
		result = true;
		if (len > 1)	// 多字节数据
		{
			memcpy(pDest, m_pBuf + m_nReadIndex, len);

			if (m_bNSByteOrder == EByteOrder::big)
			{
				ReverseBuf((BYTE*)pDest, len);
			}
		}
		else if (len == 1)	// 单字节数据
		{
			memcpy(pDest, m_pBuf + m_nReadIndex, 1);
		}

		m_nReadIndex += len;
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
	return m_nBufLen;
}

BYTE* CNetworkStreamRead::GetBuf()
{
	return m_pBuf;
}

int CNetworkStreamRead::AvaliableRead()
{
	return m_nBufLen - m_nReadIndex;
}

int CNetworkStreamRead::ReadedCount()
{
	return m_nReadIndex;
}

int CNetworkStreamRead::ReadBuf(BYTE* buf, int len)
{
	int nlen = len > AvaliableRead() ? AvaliableRead() : len;	// 实际读取长度
	if (nlen > 0)
	{
		memcpy(buf, m_pBuf + m_nReadIndex, nlen);
		m_nReadIndex += nlen;
	}
	return nlen;
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

bool CNetworkStreamRead::ReadGB2312Str(char* pDest, int len, bool hasEndChar /*= false*/)
{
	int len1 = len + (hasEndChar == true ? 1 : 0);
	if (len1 <= AvaliableRead())
	{
		memcpy(pDest, m_pBuf + m_nReadIndex, len);
		m_nReadIndex += len1;

		return true;
	}

	return false;
}

bool CNetworkStreamRead::ReadGB2312Str(char* pDest, unsigned int prefixLen /*= 4*/, bool hasEndChar /*= false*/)
{
	int len = ReadStrPrefix(prefixLen);

	if (len > 0)
	{
		return ReadGB2312Str(pDest, len, hasEndChar);
	}

	return false;
}

bool CNetworkStreamRead::ReadUTF16Str(wchar_t* pDest, int len, bool hasEndChar /*= false*/)
{
	int len1 = len + (hasEndChar == true ? 2 : 0);
	if (len1 <= AvaliableRead())
	{
		int size = sizeof(wchar_t);
		int n = 0;
		for (int i = 0; i < len; i += 2)
		{
			wchar_t ch = 0;
			ReadData(&ch, size);
			memcpy(pDest + n, &ch, size);
			n++;
		}

		return true;
	}

	return false;
}

bool CNetworkStreamRead::ReadUTF16Str(wchar_t* pDest, unsigned int prefixLen /*= 4*/, bool hasEndChar /*= false*/)
{
	int len = ReadStrPrefix(prefixLen);

	if (len > 0)
	{
		return ReadUTF16Str(pDest, len, hasEndChar);
	}

	return false;
}

bool CNetworkStreamRead::ReadUTF8Str(wchar_t* pDest, int len, bool hasEndChar /*= false*/)
{
	int len1 = len + (hasEndChar == true ? 2 : 0);
	if (len1 <= AvaliableRead())
	{
		

		return true;
	}

	return false;
}
