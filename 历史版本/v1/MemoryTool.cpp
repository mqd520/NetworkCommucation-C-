#include "stdafx.h"
#include "MemoryTool.h"

namespace MemoryTool
{
	CByteStream::CByteStream(int len)
	{
		m_nPosition = -1;
		m_dataLen = 0;
		m_streamLen = len;
		m_buf = new BYTE[len];
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

	int CByteStream::GetPosition()
	{
		return m_nPosition;
	}

	void CByteStream::SetPosition(int pos)
	{
		if (pos > -1 && pos < m_streamLen)
		{
			m_nPosition = pos;
		}
	}

	int CByteStream::GetDataLen()
	{
		return m_dataLen;
	}

	BYTE* CByteStream::GetBuf()
	{
		return m_buf;
	}

	BYTE* CByteStream::Read(int start, int len, int* readLen)
	{
		if (start + len < m_nPosition + 2)
		{
			int nlen = len >(m_dataLen - start) ? (m_dataLen - start) : len;//获取实际读取长度
			BYTE* buf = new BYTE[nlen];
			memcpy(buf, m_buf + start, nlen);
			int behindLen = m_dataLen - nlen - start;//计算后面的数据长度
			if (behindLen > 0)
			{
				Left(start + nlen, behindLen, nlen);
			}
			else
			{
				m_dataLen -= nlen;//重新计算数据长度
				m_nPosition -= nlen;//重新计算结束位置
			}
			if (readLen != NULL)
			{
				*readLen = nlen;
			}
			return buf;
		}
		return NULL;
	}

	BYTE* CByteStream::Read(int len, int* readLen)
	{
		return Read(0, len, readLen);
	}

	BYTE* CByteStream::Read(int len)
	{
		if (len > m_dataLen)
		{
			return NULL;
		}
		else
		{
			return Read(0, len, NULL);
		}
	}

	int CByteStream::Write(BYTE buf[], int len)
	{
		int nlen = len > (m_streamLen - m_dataLen) ? (m_streamLen - m_dataLen) : len;//计算实际写入字节长度
		if (nlen > 0)
		{
			memcpy(m_buf + m_nPosition + 1, buf, nlen);
			m_dataLen += nlen;
			m_nPosition += nlen;
		}
		return nlen;
	}

	int CByteStream::Write(CByteStream* p)
	{
		int datalen = p->GetDataLen();//读取流对象的可用数据长度
		int remainlen = m_streamLen - m_dataLen;//当前流对象的剩余长度
		int nlen = 0;
		if (datalen > 0 && remainlen > 0)
		{
			nlen = datalen > remainlen ? remainlen : datalen;//计算实际读取(写入)长度
			memcpy(m_buf + m_nPosition + 1, p->GetBuf(), nlen);
			p->Left(0, nlen, nlen);
		}
		return nlen;
	}

	void CByteStream::Left(int start, int size, int len)
	{
		int nlen = size > (m_dataLen - start) ? (m_dataLen - start) : size;//计算实际平移的字节长度
		if (nlen > 0)
		{
			BYTE* buf = new BYTE[nlen];//需要平移的字节缓冲区
			memcpy(buf, m_buf + start, nlen);
			int nIndex = start - len;//计算平移后的开始位置
			if (nIndex < 0)
			{
				nIndex = 0;
				m_nPosition = m_nPosition - len + (len - start);//重新计算数据结束位置
			}
			else
			{
				m_nPosition -= len;//重新计算数据结束位置
			}
			memcpy(m_buf + nIndex, buf, nlen);
			m_dataLen = m_nPosition + 1;//重新计算数据长度
		}
	}
}