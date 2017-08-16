#include "stdafx.h"
#include "TcpServer.h"
#include "Common.h"
#include "TcpConnectionMgr.h"

namespace NetworkCommunication
{
	CTcpServer::CTcpServer() :
		CTcpService(ETcpServiceType::Server),
		m_nServerPort(0),
		m_bInited(false),
		m_bListening(false),
		m_socketData({ 0 })
	{
		memset(m_strServerIP, 0, 20 * sizeof(TCHAR));
	}

	CTcpServer::~CTcpServer()
	{

	}

	void CTcpServer::Init(char* ip, int port)
	{
		if (!m_bInited)//ֻ��ʼ��һ��
		{
			m_bInited = true;
			strcpy(m_strServerIP, ip);
			m_nServerPort = port;
		}
	}

	bool CTcpServer::Listen()
	{
		if (!m_bListening)
		{
			//��ʼ�������socket
			m_bListening = true;
			m_serverSocket = m_socketMgr.CreateTcpSocket();
			m_socketMgr.SetNonBlock(m_serverSocket);
			m_socketMgr.Bind(m_serverSocket, m_strServerIP, m_nServerPort);
			m_socketMgr.Listen(m_serverSocket);
			Printf1("Listen success: %s:%d", m_strServerIP, m_nServerPort);

			//����������һ�������socket����
			m_socketData = CServerSocketDataMgr::Create(m_strServerIP, m_nServerPort, m_serverSocket, this);

			//����select����
			CNetworkCommuMgr::GetSelect()->AddSocket(m_serverSocket, ESelectSocketType::Server);

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

	void CTcpServer::SendData(SOCKET client, BYTE buf[], int len)
	{
		CTcpConnection* conn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetTcpConnByPeerSocket(client);
		if (conn)
		{
			conn->SendData(buf, len);
		}
	}
}