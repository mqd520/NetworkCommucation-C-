#include "stdafx.h"
#include "ByteStream.h"
#include "MemoryTool.h"

namespace NetworkCommunication
{
	CByteStream::CByteStream(int len) :
		m_nStreamLen(len),
		m_buf(new BYTE[len]),
		m_nDataEndPos(-1)
	{
		memset(m_buf, 0, len);
	}

	CByteStream::~CByteStream()
	{
		if (m_buf)
		{
			delete m_buf;
			m_buf = NULL;
		}
	}

	int CByteStream::GetDataLen()
	{
		return m_nDataEndPos + 1;
	}

	BYTE* CByteStream::GetBuf()
	{
		return m_buf;
	}

	BYTE* CByteStream::Read(int len, int* actualLen)
	{
		int nlen = len > GetDataLen() ? GetDataLen() : len;//获取实际读取长度
		if (nlen > 0)
		{
			BYTE* buf = new BYTE[nlen];
			memcpy(buf, m_buf, nlen);
			int behindLen = GetDataLen() - nlen;//计算开始出nlen后数据长度
			if (behindLen > 0)//如果有剩余成都,进行平移操作
			{
				Left(nlen, behindLen, nlen);
			}
			else
			{
				m_nDataEndPos = -1;
			}
			if (actualLen != NULL)
			{
				*actualLen = nlen;
			}
			return buf;
		}
		return NULL;
	}

	BYTE* CByteStream::Read(int len)
	{
		if (len > GetDataLen())
		{
			return NULL;
		}
		else
		{
			return Read(len, NULL);
		}
	}

	int CByteStream::Write(BYTE buf[], int len)
	{
		int nlen = CalcActualLen(len);
		if (nlen > 0)
		{
			memcpy(m_buf + m_nDataEndPos + 1, buf, nlen);
			m_nDataEndPos += nlen;
		}
		return nlen;
	}

	int CByteStream::Write(CByteStream* p)
	{
		int datalen = p->GetDataLen();//读取流对象的可用数据长度
		int remainlen = m_nStreamLen - GetDataLen();//当前流对象的剩余长度
		int nlen = 0;//实际写入长度
		if (datalen > 0 && remainlen > 0)
		{
			nlen = datalen > remainlen ? remainlen : datalen;//计算实际写入长度
			memcpy(m_buf + m_nDataEndPos + 1, p->GetBuf(), nlen);
			p->Detele(nlen);
		}
		return nlen;
	}

	void CByteStream::Left(int start, int len, int space)
	{
		BYTE* buf = new BYTE[len];
		memcpy(buf, m_buf + start, len);//拷贝需要平移的字节缓冲区到buf
		int nIndex = start - len;//计算平移后的开始位置
		if (nIndex < 0)
		{
			nIndex = 0;
		}
		m_nDataEndPos -= space;//计算平移后的数据结束索引
		memcpy(m_buf + nIndex, buf, len);
		delete buf;
	}

	int CByteStream::CalcActualLen(int len)
	{
		return len > (m_nStreamLen - GetDataLen()) ? (m_nStreamLen - GetDataLen()) : len;//计算实际写入字节长度
	}

	void CByteStream::Clean()
	{
		m_nDataEndPos = -1;
	}

	void CByteStream::Detele(int len)
	{
		if (len < GetDataLen())
		{
			Left(len, GetDataLen() - len, len);
		}
		else
		{
			m_nDataEndPos = -1;
		}
	}

	int CByteStream::GetBufLen()
	{
		return m_nStreamLen;
	}

	bool CByteStream::IsFull()
	{
		return GetDataLen() == m_nStreamLen ? true : false;
	}

	int CByteStream::GetWriteLen()
	{
		return m_nStreamLen - GetDataLen();
	}

	int CByteStream::WriteByte(BYTE val)
	{
		int nlen = CalcActualLen(sizeof(BYTE));
		if (nlen > 0)
		{
			m_nDataEndPos += sizeof(BYTE);
			m_buf[m_nDataEndPos] = val;
		}
		return nlen;
	}

	int CByteStream::WriteInt(int val, bool bLittleEndian)
	{
		int nlen = CalcActualLen(sizeof(int));
		if (nlen > 0)
		{
			BYTE* buf = WriteIntToBuf(val, bLittleEndian);
			memcpy(m_buf + m_nDataEndPos + 1, buf, nlen);
			m_nDataEndPos += nlen;
			delete buf;
		}
		return nlen;
	}

	int CByteStream::WriteShort(short val, bool bLittleEndian)
	{
		int nlen = CalcActualLen(sizeof(short));
		if (nlen > 0)
		{
			BYTE* buf = WriteShortToBuf(val, bLittleEndian);
			memcpy(m_buf + m_nDataEndPos + 1, buf, nlen);
			m_nDataEndPos += nlen;
			delete buf;
		}
		return nlen;
	}
}