#include "stdafx.h"
#include "Service3Mgr.h"
#include "ProtocolMgr.h"

void OnServer3RecvData(BYTE buf[], int len);
CService3Mgr* pServer3Mgr;

CService3Mgr::CService3Mgr()
{
	m_stream = new CByteStream(1024);
	m_streamCatch = NULL;
	m_lpfn = NULL;
}

CService3Mgr::~CService3Mgr()
{
	if (m_stream)
	{
		delete m_stream;
		m_stream = NULL;
	}
	if (m_streamCatch)
	{
		delete m_streamCatch;
		m_streamCatch = NULL;
	}
	m_tcp.Dispose();
}

bool CService3Mgr::Init(TCHAR* ip, int port, LPOnServer3RecvData lpfn)
{
	pServer3Mgr = this;
	m_lpfn = lpfn;
	m_protocol.Init();
	m_tcp.Init(ip, port, OnServer3RecvData);
	m_tcp.StartConnect();
	return true;
}

void CService3Mgr::OnRecvData(BYTE buf[], int len)
{
	if (m_streamCatch)
	{
		m_stream->Write(m_streamCatch);//�ӻ����ж�ȡ����д�뵽��ǰ������
		if (m_streamCatch->GetDataLen() == 0)//������������ʹ��
		{
			delete m_streamCatch;
			m_streamCatch = NULL;
		}
		else
		{
			if (len > 0)
			{
				m_streamCatch->Write(buf, len);//buf��Դ�ڷ����,��buf�洢�ڻ�������
			}
			Unpacket();
			OnRecvData(NULL, 0);//�����ӻ������ж�ȡ����
		}
	}
	if (len > 0)//buf��Դ�ڷ����
	{
		int len1 = m_stream->Write(buf, len);//ʵ��д��ĳ���
		Unpacket();
		if (len1 < len)
		{
			m_streamCatch = new CByteStream(len - len1);//������δ��ȫ���洢����,��Ҫ����������洢����
			m_streamCatch->Write(buf + len1, len - len1);
			OnRecvData(NULL, 0);//�����ӻ������ж�ȡ����
		}
	}
	else
	{
		Unpacket();
	}
}

void CService3Mgr::Unpacket()
{
	int headlen = m_protocol.GetHeadLen();
	if (m_stream->GetDataLen() > headlen)
	{
		int len = 0;
		Package3Type type = m_protocol.GetPackageType(m_stream->GetBuf(), headlen);//��ȡ������
		if (type != Package3Type::invalid)
		{
			int datalen = m_protocol.GetDataLen(m_stream->GetBuf(), headlen);//��ȡ�������ݳ���
			int packgetlen = datalen + headlen;//������ܳ���
			BYTE* buf = m_stream->Read(packgetlen);//���ֽ��������ж�ȡһ������������
			if (buf != NULL)
			{
				void* data = m_protocol.Unpacket(buf, packgetlen);//���
				delete buf;
				if (AnalyticsPackage(type, (LPPackage3Base)data) && m_lpfn)
				{
					m_lpfn(type, data);
				}
				else
				{
					ReleasePackage(type, (LPPackage3Base)data);
				}
			}
		}
	}
}

bool CService3Mgr::AnalyticsPackage(Package3Type type, LPPackage3Base data)
{
	if (type == Package3Type::type4)//������
	{
		LPKeepAlivePackage pack = (LPKeepAlivePackage)data;
		return pack->n == 0 ? true : false;
	}
	return true;
}

void OnServer3RecvData(BYTE buf[], int len)
{
	if (pServer3Mgr)
	{
		pServer3Mgr->OnRecvData(buf, len);
	}
}

void CService3Mgr::ReleasePackage(Package3Type type, LPPackage3Base data)
{
	ParserInfo parser = m_protocol.GetPacketParser(type);
	if (parser.release)
	{
		parser.release(data);
	}
}

bool CService3Mgr::Send(Package3Type type, LPPackage3Base data)
{
	int len = 0;
	BYTE* buf = m_protocol.Packet(type, data, &len);
	return m_tcp.SendData(buf, len);
}

void CService3Mgr::SimulateServer3Data(Package3Type type, Package3Base* data)
{
	int len = 0;
	BYTE* buf = m_protocol.Packet(type, data, &len);
	m_tcp.OnRecvData(buf, len);
	delete buf;
}