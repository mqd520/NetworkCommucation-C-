#include "stdafx.h"
#include "NetworkStream.h"
#include "MemoryTool.h"

namespace NetworkCommunication
{
	union var
	{
		int n = 1;
		char c;
	}u;

	EByteOrder CNetworkStream::m_bHostByeOrder = u.c == 1 ? EByteOrder::litte : EByteOrder::big;

	CNetworkStream::CNetworkStream(BYTE* pBuf, int len, EByteOrder bo/* = EByteOrder::big*/) :
		m_pBuf(pBuf),
		m_nBufLen(len),
		m_bNSByteOrder(bo)
	{
		//if (m_pBuf == NULL)
		//{
		//	m_pBuf = new BYTE[len];
		//	memset(m_pBuf, 0, len);
		//	m_bDelete = true;
		//}
		//else
		//{
		//	m_bDelete = false;
		//}

		m_nReadIndex = m_nWriteIndex = 0;
	}

	CNetworkStream::~CNetworkStream()
	{
		//if (m_bDelete)
		//{
		//	delete m_pBuf;
		//}
	}

	bool CNetworkStream::ReadData(void* pDest, int len)
	{
		bool result = false;
		if (len <= AvaliableRead())
		{
			result = true;
			if (len > 1)	// 多字节数据
			{
				if (m_bHostByeOrder == m_bNSByteOrder)	// 表示网络流和主机的字节序一致
				{
					memcpy(pDest, m_pBuf + m_nReadIndex, len);
				}
				else // 表示网络流和主机的字节序不一致, 需要反转
				{
					BYTE buf[8] = { 0 };
					memcpy(buf, m_pBuf + m_nReadIndex, len);
					for (int i = 0; i < len / 2; i++)
					{
						BYTE tmp = buf[i];
						buf[i] = buf[len - 1 - i];
						buf[len - 1 - i] = tmp;
					}
					memcpy(pDest, buf, len);
				}
			}
			else if (len == 1)//单字节数据
			{
				memcpy(pDest, m_pBuf + m_nReadIndex, 1);
			}
			m_nReadIndex += len;
		}
		return result;
	}

	int CNetworkStream::GetLen()
	{
		return m_nBufLen;
	}

	BYTE* CNetworkStream::GetBuf()
	{
		return m_pBuf;
	}

	int CNetworkStream::AvaliableRead()
	{
		return m_nBufLen - m_nReadIndex;
	}

	int CNetworkStream::AvaliableReadIndex()
	{
		return m_nReadIndex;
	}

	int CNetworkStream::ReadBuf(BYTE* buf, int len)
	{
		int nlen = len > AvaliableRead() ? AvaliableRead() : len;//实际读取长度
		if (nlen > 0)
		{
			memcpy(buf, m_pBuf + m_nReadIndex, nlen);
			m_nReadIndex += nlen;
		}
		return nlen;
	}

	BYTE CNetworkStream::ReadByte()
	{
		BYTE b;
		ReadData(&b, sizeof(BYTE));
		return b;
	}

	USHORT CNetworkStream::ReadUShort()
	{
		USHORT b;
		ReadData(&b, sizeof(USHORT));
		return b;
	}

	UINT16 CNetworkStream::ReadUInt16()
	{
		UINT16 b;
		ReadData(&b, sizeof(UINT16));
		return b;
	}

	UINT CNetworkStream::ReadUInt()
	{
		UINT b;
		ReadData(&b, sizeof(UINT));
		return b;
	}

	UINT64 CNetworkStream::ReadUInt64()
	{
		UINT64 b;
		ReadData(&b, sizeof(UINT64));
		return b;
	}

	short CNetworkStream::ReadShort()
	{
		short b;
		ReadData(&b, sizeof(short));
		return b;
	}

	int CNetworkStream::ReadInt()
	{
		int b;
		ReadData(&b, sizeof(int));
		return b;
	}

	INT16 CNetworkStream::ReadInt16()
	{
		INT16 b;
		ReadData(&b, sizeof(INT16));
		return b;
	}

	INT64 CNetworkStream::ReadInt64()
	{
		INT64 b;
		ReadData(&b, sizeof(INT64));
		return b;
	}

	float CNetworkStream::ReadFloat()
	{
		float b;
		ReadData(&b, sizeof(float));
		return b;
	}

	double CNetworkStream::ReadDouble()
	{
		double b;
		ReadData(&b, sizeof(double));
		return b;
	}

	bool CNetworkStream::ReadMultiByteStr(char* dest, int len)
	{
		bool result = false;
		if (len <= AvaliableRead())
		{
			memcpy(dest, m_pBuf + m_nReadIndex, len);
			m_nReadIndex += len;
			result = true;
		}
		return result;
	}

	bool CNetworkStream::ReadUTF16Str(wchar_t* dest, int len)
	{
		return ReadData(dest, len);
	}

	bool CNetworkStream::ReadUTF8Str(wchar_t* dest, int len)
	{
		bool result = false;
		if (len <= AvaliableRead())
		{
			//BYTE* pBuf = new BYTE[len];
			//int count = UTF8ByteToUTF16Byte(m_pBuf + m_nReadIndex, len, pBuf, m_bHostBigEndian);
			//memcpy(dest, pBuf, count);
			//m_nReadIndex += len;
			//result = true;
		}
		return result;
	}

	int CNetworkStream::AvaliableWrite()
	{
		return m_nBufLen - m_nWriteIndex;
	}

	int CNetworkStream::WriteBuf(BYTE* buf, int len)
	{
		int nlen = len > AvaliableWrite() ? AvaliableWrite() : len;//实际写入长度
		if (nlen > 0)
		{
			memcpy(m_pBuf + m_nWriteIndex, buf, nlen);
			m_nWriteIndex += nlen;
		}
		return nlen;
	}

	bool CNetworkStream::WriteByte(BYTE val)
	{
		if (sizeof(BYTE) <= AvaliableWrite())
		{
			m_pBuf[m_nWriteIndex + 1] = val;
			m_nWriteIndex += 1;
			return true;
		}
		return false;
	}

	bool CNetworkStream::WriteInt32(int val)
	{
		if (sizeof(int) <= AvaliableWrite())
		{
			m_pBuf[m_nWriteIndex + 1] = (BYTE)((val << (3 * 8)) >> (3 * 8));
			m_pBuf[m_nWriteIndex + 2] = (BYTE)((val << (2 * 8)) >> (3 * 8));
			m_pBuf[m_nWriteIndex + 3] = (BYTE)((val << (1 * 8)) >> (3 * 8));
			m_pBuf[m_nWriteIndex + 4] = (BYTE)((val << (0 * 8)) >> (3 * 8));
			m_nWriteIndex += 4;
			return true;
		}
		return false;
	}

	bool CNetworkStream::WriteSignInt32(int val)
	{
		if (sizeof(int) <= AvaliableWrite())
		{
			m_pBuf[m_nWriteIndex + 1] = (BYTE)((val << (3 * 8)) >> (3 * 8));
			m_pBuf[m_nWriteIndex + 2] = (BYTE)((val << (2 * 8)) >> (3 * 8));
			m_pBuf[m_nWriteIndex + 3] = (BYTE)((val << (1 * 8)) >> (3 * 8));
			m_pBuf[m_nWriteIndex + 4] = (BYTE)((val << (0 * 8)) >> (3 * 8));
			m_nWriteIndex += 4;
			return true;
		}
		return false;
	}

	bool CNetworkStream::WriteInt64(INT64 val)
	{
		if (sizeof(INT64) <= AvaliableWrite())
		{
			m_pBuf[m_nWriteIndex + 1] = (BYTE)((val << (7 * 8)) >> (3 * 8));
			m_pBuf[m_nWriteIndex + 2] = (BYTE)((val << (6 * 8)) >> (3 * 8));
			m_pBuf[m_nWriteIndex + 3] = (BYTE)((val << (5 * 8)) >> (3 * 8));
			m_pBuf[m_nWriteIndex + 4] = (BYTE)((val << (4 * 8)) >> (3 * 8));
			m_pBuf[m_nWriteIndex + 5] = (BYTE)((val << (3 * 8)) >> (3 * 8));
			m_pBuf[m_nWriteIndex + 6] = (BYTE)((val << (2 * 8)) >> (3 * 8));
			m_pBuf[m_nWriteIndex + 7] = (BYTE)((val << (1 * 8)) >> (3 * 8));
			m_pBuf[m_nWriteIndex + 8] = (BYTE)((val << (0 * 8)) >> (3 * 8));
			m_nWriteIndex += 8;
			return true;
		}
		return false;
	}

	bool CNetworkStream::WriteShort(short val)
	{
		if (sizeof(short) <= AvaliableWrite())
		{
			m_pBuf[m_nWriteIndex + 1] = (BYTE)((val << (1 * 8)) >> (1 * 8));
			m_pBuf[m_nWriteIndex + 2] = (BYTE)((val << (0 * 8)) >> (1 * 8));
			m_nWriteIndex += 2;
			return true;
		}
		return false;
	}

	int CNetworkStream::Write(BYTE* buf, int len)
	{
		int nlen = len > AvaliableWrite() ? AvaliableWrite() : len;//实际写入长度
		if (nlen > 0)
		{
			memcpy(m_pBuf + m_nWriteIndex + 1, buf, nlen);
			m_nWriteIndex += nlen;
		}
		return nlen;
	}

	bool CNetworkStream::WriteMultiStr(char* str)
	{
		int len = GetAStrByteCount(str);
		if (len <= AvaliableWrite())
		{
			memcpy(m_pBuf + m_nWriteIndex + 1, str, len);
			m_nWriteIndex += len;
			return true;
		}
		return false;
	}

	bool CNetworkStream::WriteUTF8Str(wchar_t* str)
	{
		int len = GetWStrByteCount(str);
		if (len <= AvaliableWrite())
		{
			memcpy(m_pBuf + m_nWriteIndex + 1, str, len);
			m_nWriteIndex += len;
			return true;
		}
		return false;
	}
}