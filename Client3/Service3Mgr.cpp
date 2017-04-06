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
		m_stream->Write(m_streamCatch);//从缓存中读取数据写入到当前流对象
		if (m_streamCatch->GetDataLen() == 0)//缓存流对象不再使用
		{
			delete m_streamCatch;
			m_streamCatch = NULL;
		}
		else
		{
			if (len > 0)
			{
				m_streamCatch->Write(buf, len);//buf来源于服务端,将buf存储于缓存流中
			}
			Unpacket();
			OnRecvData(NULL, 0);//继续从缓存流中读取数据
		}
	}
	if (len > 0)//buf来源于服务端
	{
		int len1 = m_stream->Write(buf, len);//实际写入的长度
		Unpacket();
		if (len1 < len)
		{
			m_streamCatch = new CByteStream(len - len1);//流对象未能全部存储数据,需要缓存流对象存储数据
			m_streamCatch->Write(buf + len1, len - len1);
			OnRecvData(NULL, 0);//继续从缓存流中读取数据
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
		Package3Type type = m_protocol.GetPackageType(m_stream->GetBuf(), headlen);//获取包类型
		if (type != Package3Type::invalid)
		{
			int datalen = m_protocol.GetDataLen(m_stream->GetBuf(), headlen);//获取包体数据长度
			int packgetlen = datalen + headlen;//计算包总长度
			BYTE* buf = m_stream->Read(packgetlen);//从字节流对象中读取一个完整包数据
			if (buf != NULL)
			{
				void* data = m_protocol.Unpacket(buf, packgetlen);//解包
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
	if (type == Package3Type::type4)//心跳包
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