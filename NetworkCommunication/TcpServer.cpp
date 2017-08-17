#include "stdafx.h"
#include "TcpServer.h"
#include "Common.h"
#include "TcpConnectionMgr.h"

namespace NetworkCommunication
{
	CTcpServer::CTcpServer() :
		CTcpService(ETcpServiceType::Server),
		m_bListening(false),
		m_socketData({ 0 })
	{

	}

	CTcpServer::~CTcpServer()
	{

	}

	void CTcpServer::Init(char* ip, int port)
	{
		strcpy(m_strLocalIP, ip);
		m_nLocalPort = port;
	}

	bool CTcpServer::Listen()
	{
		if (!m_bListening)
		{
			//初始化服务端socket
			m_bListening = true;
			m_localSocket = m_socketAPI.CreateTcpSocket();
			m_socketAPI.SetNonBlock(m_localSocket);
			m_socketAPI.Bind(m_localSocket, m_strLocalIP, m_nLocalPort);
			m_socketAPI.Listen(m_localSocket);
			Printf1("Listen success: %s:%d", m_strLocalIP, m_nLocalPort);

			//创建并增加一个服务端socket数据
			m_socketData = CServerSocketDataMgr::Create(m_strLocalIP, m_nLocalPort, m_localSocket, this);

			//加入select队列
			CNetworkCommuMgr::GetSelect()->AddSocket(m_localSocket, ESelectSocketType::Server);

			return true;
		}
		return true;
	}

	ServerSocketData CTcpServer::GetServerSocketData()
	{
		return m_socketData;
	}

	void CTcpServer::OnRecvNewConnection(ServerSocketData server, PeerSocketData client)
	{
		__super::OnRecvNewConnection(server, client);
	}
}