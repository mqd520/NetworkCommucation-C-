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
		int nlen = len > GetDataLen() ? GetDataLen() : len;//��ȡʵ�ʶ�ȡ����
		if (nlen > 0)
		{
			BYTE* buf = new BYTE[nlen];
			memcpy(buf, m_buf, nlen);
			int behindLen = GetDataLen() - nlen;//���㿪ʼ��nlen�����ݳ���
			if (behindLen > 0)//�����ʣ��ɶ�,����ƽ�Ʋ���
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
		int nlen = len > (m_streamLen - GetDataLen()) ? (m_streamLen - GetDataLen()) : len;//����ʵ��д���ֽڳ���
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
		int datalen = p->GetDataLen();//��ȡ������Ŀ������ݳ���
		int remainlen = m_streamLen - GetDataLen();//��ǰ�������ʣ�೤��
		int nlen = 0;//ʵ��д�볤��
		if (datalen > 0 && remainlen > 0)
		{
			nlen = datalen > remainlen ? remainlen : datalen;//����ʵ��д�볤��
			memcpy(m_buf + m_nDataEndPos + 1, p->GetBuf(), nlen);
			p->Detele(nlen);
		}
		return nlen;
	}

	void CByteStream::Left(int start, int len, int space)
	{
		BYTE* buf = new BYTE[len];
		memcpy(buf, m_buf + start, len);//������Ҫƽ�Ƶ��ֽڻ�������buf
		int nIndex = start - len;//����ƽ�ƺ�Ŀ�ʼλ��
		if (nIndex < 0)
		{
			nIndex = 0;
		}
		m_nDataEndPos -= len;//����ƽ�ƺ�����ݽ�������
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