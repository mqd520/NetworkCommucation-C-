#include "stdafx.h"
#include "Server3.h"
#include "Protocol3Handle.h"

void OnServer3RecvData(BYTE buf[], int len);
CServer3Mgr* pServer3Mgr;

CServer3Mgr::CServer3Mgr()
{
	m_stream = new CByteStream(1024);
	m_streamCatch = NULL;
	m_lpfn = NULL;
}

CServer3Mgr::~CServer3Mgr()
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

bool CServer3Mgr::Init(TCHAR* ip, int port, LPOnServer3RecvData lpfn)
{
	pServer3Mgr = this;
	m_lpfn = lpfn;
	CProtocol3Handle::Init();
	m_tcp.Init(ip, port, OnServer3RecvData);
	m_tcp.StartConnect();
	return true;
}

void CServer3Mgr::OnRecvData(BYTE buf[], int len)
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

void CServer3Mgr::Unpacket()
{
	int headlen = CProtocol3Handle::GetHeadLen();
	if (m_stream->GetDataLen() > headlen)
	{
		int len = 0;
		Package3Type type = CProtocol3Handle::GetPackageType(m_stream->GetBuf(), headlen);//获取包类型
		if (type != Package3Type::invalid)
		{
			int datalen = CProtocol3Handle::GetDataLen(m_stream->GetBuf(), headlen);//获取包体数据长度
			int packgetlen = datalen + headlen;//计算包总长度
			BYTE* buf = m_stream->Read(packgetlen);//从字节流对象中读取一个完整包数据
			if (buf != NULL)
			{
				void* data = CProtocol3Handle::Unpacket(buf, packgetlen);//解包
				delete buf;
				if (m_lpfn)
				{
					m_lpfn(type, data);
				}
			}
		}
	}
}

void OnServer3RecvData(BYTE buf[], int len)
{
	if (pServer3Mgr)
	{
		pServer3Mgr->OnRecvData(buf, len);
	}
}

void CServer3Mgr::ReleasePackage(Package3Type type, LPPackage3Base data)
{
	ParserInfo parser = CProtocol3Handle::GetPacketParser(type);
	if (parser.release)
	{
		parser.release(data);
	}
}

bool CServer3Mgr::Send(Package3Type type, LPPackage3Base data)
{
	int len = 0;
	BYTE* buf = CProtocol3Handle::Packet(type, data, &len);
	return m_tcp.SendData(buf, len);
}

void CServer3Mgr::SimulateServer3Data(Package3Type type, Package3Base* data)
{
	int len = 0;
	BYTE* buf = CProtocol3Handle::Packet(type, data, &len);
	m_tcp.OnRecvData(buf, len);
	delete buf;
}