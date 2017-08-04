#include "stdafx.h"
#include "TcpServer.h"
#include "Common.h"

namespace NetworkCommunication
{
	CTcpServer::CTcpServer() :
		m_nServerPort(0),
		m_bInited(false),
		m_bListening(false),
		m_nMaxConnectionCount(0),
		m_nConnectedCount(0)
	{
		memset(m_strServerIP, 0, 20 * sizeof(TCHAR));
		m_fdRead.fd_count = 0;
	}

	CTcpServer::~CTcpServer()
	{

	}

	void CTcpServer::Init(TCHAR* ip, int port, int maxConn)
	{
		if (!m_bInited)//只初始化一次
		{
			m_bInited = true;
#ifdef _UNICODE
			wcscpy((wchar_t*)m_strServerIP, ip);
#else
			strcpy((char*)m_strServerIP, ip);
#endif // _UNICODE
			m_nServerPort = port;
			m_nMaxConnectionCount = maxConn;
		}
	}

	bool CTcpServer::Listen()
	{
		if (!m_bListening)
		{
			m_bListening = true;
			m_serverSocket = m_socketMgr.CreateTcpSocket();
			m_socketMgr.SetNonBlock(m_serverSocket);
			m_socketMgr.Bind(m_serverSocket, m_strServerIP, m_nServerPort);
			m_socketMgr.Listen(m_serverSocket);
			_tprintf(_T("Listen success: %s:%d, socket: %d \n"), m_strServerIP, m_nServerPort, m_serverSocket);
			CNetworkCommuMgr::GetSelect()->AddListenSocket(m_serverSocket);

			ServerSocketData data = { 0 };
			data.socket = m_serverSocket;
			StrCopy(data.ip, m_strServerIP);
			data.port = m_nServerPort;
			data.addr = m_socketMgr.CreateSocketAddr(m_strServerIP, m_nServerPort);
			CNetworkCommuMgr::GetServerSocketMgr()->Push(data);

			return true;
		}
		return true;
	}
}