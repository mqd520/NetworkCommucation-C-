#include "stdafx.h"
#include "NetCommuMgr.h"
#include "SocketAPI.h"
#include "ThreadMgr.h"

namespace NetworkCommunication
{
	CThreadMgr* CNetworkCommuMgr::m_threadMgr = NULL;
	CSelect* CNetworkCommuMgr::m_Select = NULL;
	CAccept* CNetworkCommuMgr::m_accept = NULL;
	CServerSocketDataMgr* CNetworkCommuMgr::m_serverSocketDataMgr = NULL;
	CPeerSocketDataMgr* CNetworkCommuMgr::m_peerSocketDataMgr = NULL;
	int CNetworkCommuMgr::m_srvType = ETcpServiceType::Server;
	CTcpConnectionMgr* CNetworkCommuMgr::m_tcpConnMgr = NULL;
	CTcp* CNetworkCommuMgr::m_tcp = NULL;
	CTcpServiceMgr* CNetworkCommuMgr::m_tcpSrvMgr = NULL;

	void CNetworkCommuMgr::Init()
	{
		CSocketAPI::Init();
		//Accept线程在TcpServiceMgr类中启动
		GetSelect()->Run();//运行select线程
		GetTcpConnectionMgr()->Run();//运行tcp连接线程
		GetTcpServiceMgr()->Run();//运行tcp动作线程
	}

	void CNetworkCommuMgr::Exit()
	{
		CSocketAPI::Release();
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

	CServerSocketDataMgr* CNetworkCommuMgr::GetServerSocketMgr()
	{
		if (m_serverSocketDataMgr == NULL)
		{
			m_serverSocketDataMgr = new CServerSocketDataMgr();
		}
		return m_serverSocketDataMgr;
	}

	CPeerSocketDataMgr* CNetworkCommuMgr::GetPeerSocketDataMgr()
	{
		if (m_peerSocketDataMgr == NULL)
		{
			m_peerSocketDataMgr = new CPeerSocketDataMgr();
		}
		return m_peerSocketDataMgr;
	}

	int CNetworkCommuMgr::GetSrvType()
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

	CTcp* CNetworkCommuMgr::GetTcp()
	{
		if (m_tcp == NULL)
		{
			m_tcp = new CTcp();
		}
		return m_tcp;
	}

	CTcpServiceMgr* CNetworkCommuMgr::GetTcpServiceMgr()
	{
		if (m_tcpSrvMgr == NULL)
		{
			m_tcpSrvMgr = new CTcpServiceMgr();
		}
		return m_tcpSrvMgr;
	}
}