#include "stdafx.h"
#include "TcpServer.h"

namespace NetworkCommunication
{
	//开始接受客户端连接线程入口
	DWORD WINAPI StartAccept(LPVOID lpParam);

	CTcpServer::CTcpServer() :
		m_nServerPort(0),
		m_bInited(false),
		m_bListening(false),
		m_tiAccept({ 0 }),
		m_nMaxConnectionCount(0),
		m_nConnectedCount(0)
	{
		memset(m_strServerIP, 0, 20 * sizeof(TCHAR));
	}

	CTcpServer::~CTcpServer()
	{
		CleanThread();
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
			m_socketMgr.Init();
		}
	}

	void CTcpServer::Listen()
	{
		if (!m_bListening)
		{
			m_bListening = true;
			m_serverSocket = m_socketMgr.CreateTcpSocket();
			m_socketMgr.Bind(m_serverSocket, m_strServerIP, m_nServerPort);
			m_socketMgr.Listen(m_serverSocket);
			m_socketMgr.SetNonBlock(m_serverSocket);//设置异步方式
			m_tiAccept.hThread = ::CreateThread(NULL, 0, NetworkCommunication::StartAccept, this, NULL, &m_tiAccept.dwThreadID);
		}
	}

	DWORD WINAPI StartAccept(LPVOID lpParam)
	{
		CTcpServer* p = (CTcpServer*)lpParam;
		p->StartAccept();
		return 0;
	}

	void CTcpServer::StartAccept()
	{
		while (true)
		{
			SOCKET clientSocket = m_socketMgr.Accept(m_serverSocket, m_strServerIP, m_nServerPort);
			if (clientSocket == 0)//发生了错误
			{

			}
			else
			{
				if (m_nConnectedCount == m_nMaxConnectionCount)//是否已达到允许最大连接数
				{
					::closesocket(clientSocket);//主动断开客户端连接
					
				}
				else
				{
					TCHAR ip[20];
					int port = 100;
					m_socketMgr.GetIpAndPort(clientSocket, ip, &port);
					 
					//接收到新客户端连接通知
					_tprintf(_T("Recv a new client connection: %s:%d \n"), ip, port);

					CTcpSession session(m_serverSocket, clientSocket);
					m_sessionMgr.Push(session);
					m_nConnectedCount++;
				}
			}
		}
	}

	void CTcpServer::CleanThread()
	{
		if (m_tiAccept.hThread)
		{
			::TerminateThread(m_tiAccept.hThread, 0);
			::CloseHandle(m_tiAccept.hThread);
		}
	}
}