#include "stdafx.h"
#include "NetCommuMgr.h"
#include "SocketMgr.h"
#include "ThreadMgr.h"

namespace NetworkCommunication
{
	CThreadMgr* CNetworkCommuMgr::m_threadMgr = NULL;
	CSelect* CNetworkCommuMgr::m_Select = NULL;
	CAccept* CNetworkCommuMgr::m_accept = NULL;
	CServerSocketMgr* CNetworkCommuMgr::m_serverSockerMgr = NULL;
	CNetworkCommuMgr::EServiceType CNetworkCommuMgr::m_srvType = CNetworkCommuMgr::EServiceType::Server;
	CTcpConnectionMgr* CNetworkCommuMgr::m_tcpConnMgr = NULL;

	void CNetworkCommuMgr::Init(EServiceType type)
	{
		m_srvType = type;
		CSocketMgr::Init();
		if (type == EServiceType::Server || type == EServiceType::Both)
		{
			GetAccept()->Run();//开启accept线程
		}
		GetSelect()->Run();//开启select线程
		GetTcpConnectionMgr()->Run();//开启socket读写线程
	}

	void CNetworkCommuMgr::Exit()
	{
		CSocketMgr::Release();
		if (m_threadMgr)
		{
			delete m_threadMgr;
		}
		if (m_Select)
		{
			delete m_Select;
		}
	}

	CThreadMgr* CNetworkCommuMgr::GetThreadMgr()
	{
		if (m_threadMgr == NULL)
		{
			m_threadMgr = new CThreadMgr();
		}
		return m_threadMgr;
	}

	CSelect* CNetworkCommuMgr::GetSelect()
	{
		if (m_Select == NULL)
		{
			m_Select = new CSelect();
		}
		return m_Select;
	}

	CAccept* CNetworkCommuMgr::GetAccept()
	{
		if (m_accept == NULL)
		{
			m_accept = new CAccept();
		}
		return m_accept;
	}

	CServerSocketMgr* CNetworkCommuMgr::GetServerSocketMgr()
	{
		if (m_serverSockerMgr == NULL)
		{
			m_serverSockerMgr = new CServerSocketMgr();
		}
		return m_serverSockerMgr;
	}

	CNetworkCommuMgr::EServiceType CNetworkCommuMgr::GetSrvType()
	{
		return m_srvType;
	}

	CTcpConnectionMgr* CNetworkCommuMgr::GetTcpConnectionMgr()
	{
		if (m_tcpConnMgr == NULL)
		{
			m_tcpConnMgr = new CTcpConnectionMgr();
		}
		return m_tcpConnMgr;
	}
}