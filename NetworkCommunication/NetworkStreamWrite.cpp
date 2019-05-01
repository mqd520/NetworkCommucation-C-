#include "stdafx.h"
#include "Include/nc/NetworkStreamWrite.h"
#include "Include/nc/GB2312Str.h"
#include "Include/nc/UTF16Str.h"

using namespace NetworkCommunication;

CNetworkStreamWrite::CNetworkStreamWrite(BYTE* pBuf, int len, EByteOrder bo /*= EByteOrder::big*/) :
m_pBuf(pBuf),
m_nBufLen(len),
m_bNSByteOrder(bo),
m_nWriteIndex(0)
{

}

CNetworkStreamWrite::~CNetworkStreamWrite()
{

}

bool CNetworkStreamWrite::WriteData(void* pDest, int len)
{
	bool result = false;

	if (len <= AvaliableWrite())
	{
		memcpy(m_pBuf + m_nWriteIndex, pDest, len);

		if (len > 1 && m_bNSByteOrder != NCTool::GetHostByteOrder())	// 多字节数据
		{
			NCTool::ReverseBuf(m_pBuf + m_nWriteIndex, len);
		}

		m_nWriteIndex += len;
		result = true;
	}

	return result;
}

bool CNetworkStreamWrite::WriteStrPrefix(int prefix, int val)
{
	bool result = true;

	switch (prefix)
	{
	case 1:
		result = WriteByte(val);
		break;
	case 2:
		result = WriteUShort(val);
		break;
	case 4:
		result = WriteUInt32(val);
		break;
	default:
		result = false;
		break;
	}

	return result;
}

int CNetworkStreamWrite::GetLen()
{
	return m_nBufLen;
}

BYTE* CNetworkStreamWrite::GetBuf()
{
	return m_pBuf;
}

int CNetworkStreamWrite::AvaliableWrite()
{
	return m_nBufLen - m_nWriteIndex;
}

int CNetworkStreamWrite::WritedCount()
{
	return m_nWriteIndex;
}

bool CNetworkStreamWrite::WriteBuf(BYTE* pBuf, int len)
{
	bool result = false;

	if (len <= AvaliableWrite())
	{
		memcpy(m_pBuf + m_nWriteIndex, pBuf, len);
		m_nWriteIndex += len;
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

