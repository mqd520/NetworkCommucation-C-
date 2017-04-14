#include "stdafx.h"
#include "MemoryTool.h"

namespace NetworkCommunication
{
	CByteStream::CByteStream(int len) :
		m_streamLen(len),
		m_buf(new BYTE[len]{0}),
		m_nDataEndPos(-1)
	{

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
		int nlen = len > (m_streamLen - GetDataLen()) ? (m_streamLen - GetDataLen()) : len;//计算实际写入字节长度
		if (nlen > 0)
		{
			memcpy(m_buf + m_nDataEndPos + 1, buf, nlen);
			m_dataLen += nlen;
			m_nDataEndPos += nlen;
		}
		return nlen;
	}

	int CByteStream::Write(CByteStream* p)
	{
		int datalen = p->GetDataLen();//读取流对象的可用数据长度
		int remainlen = m_streamLen - GetDataLen();//当前流对象的剩余长度
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
		m_nDataEndPos -= len;//计算平移后的数据结束索引
		memcpy(m_buf + nIndex, buf, len);
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
}