#include "stdafx.h"
#include "NetCommuMgr.h"
#include "SocketAPI.h"

namespace NetworkCommunication
{
	CThreadMgr* CNetworkCommuMgr::m_threadMgr = NULL;
	CSelect* CNetworkCommuMgr::m_Select = NULL;
	CTcp* CNetworkCommuMgr::m_tcp = NULL;
	CServerSocketMgr* CNetworkCommuMgr::m_serverSocketMgr = NULL;
	CServerClientSocketMgr* CNetworkCommuMgr::m_serverCLientSocketMgr = NULL;
	CTcpConnectionMgr* CNetworkCommuMgr::m_tcpConnMgr = NULL;
	CTcpServiceMgr* CNetworkCommuMgr::m_tcpSrvMgr = NULL;

	void CNetworkCommuMgr::Init()
	{
		CSocketAPI::Init();
		GetSelect()->Run();//启动select线程
		GetTcp()->Run();//启动tcp线程
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

	CTcp* CNetworkCommuMgr::GetTcp()
	{
		if (m_tcp == NULL)
		{
			m_tcp = new CTcp();
		}
		return m_tcp;
	}

	CServerSocketMgr* CNetworkCommuMgr::GetServerSocketMgr()
	{
		if (m_serverSocketMgr == NULL)
		{
			m_serverSocketMgr = new CServerSocketMgr();
		}
		return m_serverSocketMgr;
	}

	CServerClientSocketMgr* CNetworkCommuMgr::GetServerClientSocketMgr()
	{
		if (m_serverCLientSocketMgr == NULL)
		{
			m_serverCLientSocketMgr = new CServerClientSocketMgr();
		}
		return m_serverCLientSocketMgr;
	}

	CTcpConnectionMgr* CNetworkCommuMgr::GetTcpConnectionMgr()
	{
		if (m_tcpConnMgr == NULL)
		{
			m_tcpConnMgr = new CTcpConnectionMgr();
		}
		return m_tcpConnMgr;
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