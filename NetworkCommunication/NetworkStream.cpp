#include "stdafx.h"
#include "NetworkStream.h"
#include "MemoryTool.h"

namespace NetworkCommunication
{
	CNetworkStream::CNetworkStream(int bufsize) :
		m_nBufLen(bufsize),
		m_pBuf(new BYTE[bufsize]),
		m_nStartIndex(0),
		m_nEndIndex(-1)
	{
		memset(m_pBuf, 0, m_nBufLen);
	}

	CNetworkStream::~CNetworkStream()
	{
		if (m_pBuf)
		{
			delete m_pBuf;
		}
	}

	void CNetworkStream::Reset()
	{
		if (AvaliableRead() == 0)
		{
			m_nStartIndex = 0;
			m_nEndIndex = -1;
		}
	}

	int CNetworkStream::AvaliableRead()
	{
		return m_nEndIndex - m_nStartIndex + 1;
	}

	int CNetworkStream::AvaliableWrite()
	{
		return m_nBufLen - (m_nEndIndex + 1);
	}

	bool CNetworkStream::WriteByte(BYTE val)
	{
		if (sizeof(BYTE) <= AvaliableWrite())
		{
			m_pBuf[m_nEndIndex + 1] = val;
			m_nEndIndex += 1;
			return true;
		}
		return false;
	}

	bool CNetworkStream::WriteInt32(int val)
	{
		if (sizeof(int) <= AvaliableWrite())
		{
			m_pBuf[m_nEndIndex + 1] = (BYTE)((val << (3 * 8)) >> (3 * 8));
			m_pBuf[m_nEndIndex + 2] = (BYTE)((val << (2 * 8)) >> (3 * 8));
			m_pBuf[m_nEndIndex + 3] = (BYTE)((val << (1 * 8)) >> (3 * 8));
			m_pBuf[m_nEndIndex + 4] = (BYTE)((val << (0 * 8)) >> (3 * 8));
			m_nEndIndex += 4;
			return true;
		}
		return false;
	}

	bool CNetworkStream::WriteSignInt32(int val)
	{
		if (sizeof(int) <= AvaliableWrite())
		{
			m_pBuf[m_nEndIndex + 1] = (BYTE)((val << (3 * 8)) >> (3 * 8));
			m_pBuf[m_nEndIndex + 2] = (BYTE)((val << (2 * 8)) >> (3 * 8));
			m_pBuf[m_nEndIndex + 3] = (BYTE)((val << (1 * 8)) >> (3 * 8));
			m_pBuf[m_nEndIndex + 4] = (BYTE)((val << (0 * 8)) >> (3 * 8));
			m_nEndIndex += 4;
			return true;
		}
		return false;
	}

	bool CNetworkStream::WriteInt64(INT64 val)
	{
		if (sizeof(INT64) <= AvaliableWrite())
		{
			m_pBuf[m_nEndIndex + 1] = (BYTE)((val << (7 * 8)) >> (3 * 8));
			m_pBuf[m_nEndIndex + 2] = (BYTE)((val << (6 * 8)) >> (3 * 8));
			m_pBuf[m_nEndIndex + 3] = (BYTE)((val << (5 * 8)) >> (3 * 8));
			m_pBuf[m_nEndIndex + 4] = (BYTE)((val << (4 * 8)) >> (3 * 8));
			m_pBuf[m_nEndIndex + 5] = (BYTE)((val << (3 * 8)) >> (3 * 8));
			m_pBuf[m_nEndIndex + 6] = (BYTE)((val << (2 * 8)) >> (3 * 8));
			m_pBuf[m_nEndIndex + 7] = (BYTE)((val << (1 * 8)) >> (3 * 8));
			m_pBuf[m_nEndIndex + 8] = (BYTE)((val << (0 * 8)) >> (3 * 8));
			m_nEndIndex += 8;
			return true;
		}
		return false;
	}

	bool CNetworkStream::WriteShort(short val)
	{
		if (sizeof(short) <= AvaliableWrite())
		{
			m_pBuf[m_nEndIndex + 1] = (BYTE)((val << (1 * 8)) >> (1 * 8));
			m_pBuf[m_nEndIndex + 2] = (BYTE)((val << (0 * 8)) >> (1 * 8));
			m_nEndIndex += 2;
			return true;
		}
		return false;
	}

	int CNetworkStream::Read(BYTE* buf, int len)
	{
		int nlen = len > AvaliableRead() ? AvaliableRead() : len;//实际读取长度
		if (nlen > 0)
		{
			memcpy(buf, m_pBuf + m_nStartIndex, nlen);
			m_nStartIndex += nlen;
			Reset();
		}
		return nlen;
	}

	int CNetworkStream::Write(BYTE* buf, int len)
	{
		int nlen = len > AvaliableWrite() ? AvaliableWrite() : len;//实际写入长度
		if (nlen > 0)
		{
			memcpy(m_pBuf + m_nEndIndex + 1, buf, nlen);
			m_nEndIndex += nlen;
		}
		return nlen;
	}

	BYTE CNetworkStream::ReadByte()
	{
		BYTE result = m_pBuf[m_nStartIndex];
		m_nStartIndex += 1;
		Reset();
		return result;
	}

	int CNetworkStream::ReadInt32()
	{
		int result = 0;
		result += ((int)m_pBuf[m_nStartIndex + 0]) << (0 * 8);
		result += ((int)m_pBuf[m_nStartIndex + 1]) << (1 * 8);
		result += ((int)m_pBuf[m_nStartIndex + 2]) << (2 * 8);
		result += ((int)m_pBuf[m_nStartIndex + 3]) << (3 * 8);
		m_nStartIndex += 4;
		Reset();
		return result;
	}

	int CNetworkStream::ReadInt64()
	{
		int result = 0;
		result += ((INT64)m_pBuf[m_nStartIndex + 0]) << (0 * 8);
		result += ((INT64)m_pBuf[m_nStartIndex + 1]) << (1 * 8);
		result += ((INT64)m_pBuf[m_nStartIndex + 2]) << (2 * 8);
		result += ((INT64)m_pBuf[m_nStartIndex + 3]) << (3 * 8);
		result += ((INT64)m_pBuf[m_nStartIndex + 4]) << (4 * 8);
		result += ((INT64)m_pBuf[m_nStartIndex + 5]) << (5 * 8);
		result += ((INT64)m_pBuf[m_nStartIndex + 6]) << (6 * 8);
		result += ((INT64)m_pBuf[m_nStartIndex + 7]) << (7 * 8);
		m_nStartIndex += 8;
		Reset();
		return result;
	}

	short CNetworkStream::ReadShort()
	{
		short result = 0;
		result += ((short)m_pBuf[m_nStartIndex + 0]) << (0 * 8);
		result += ((short)m_pBuf[m_nStartIndex + 1]) << (1 * 8);
		m_nStartIndex += 2;
		Reset();
		return result;
	}

	bool CNetworkStream::WriteMultiStr(char* str)
	{
		int len = GetAStrByteCount(str);
		if (len <= AvaliableWrite())
		{
			memcpy(m_pBuf + m_nEndIndex + 1, str, len);
			m_nEndIndex += len;
			return true;
		}
		return false;
	}

	bool CNetworkStream::WriteUTF8Str(wchar_t* str)
	{
		int len = GetWStrByteCount(str);
		if (len <= AvaliableWrite())
		{
			memcpy(m_pBuf + m_nEndIndex + 1, str, len);
			m_nEndIndex += len;
			return true;
		}
		return false;
	}

	char* CNetworkStream::ReadMultiStr(int len)
	{
		char* result = NULL;
		if (len <= AvaliableRead())
		{
			string str = ReadMultiByteStr(m_pBuf + m_nStartIndex, len);
			int strLen = strlen(str.c_str()) + 1;
			result = new char[strLen];
			memcpy(result, str.c_str(), len);
			m_nStartIndex += len;
			Reset();
		}
		return result;
	}

	wchar_t* CNetworkStream::ReadUTF8Str(int len)
	{
		wchar_t* result = NULL;
		if (len <= AvaliableRead())
		{
			wstring str = ReadUTF8ByteStr(m_pBuf + m_nStartIndex, len);
			int strLen = wcslen(str.c_str()) + 1;
			result = new wchar_t[strLen];
			memcpy(result, str.c_str(), len);
			m_nStartIndex += len;
			Reset();
		}
		return result;
	}
}