#include "stdafx.h"
#include "TcpServer.h"

namespace NetworkCommunication
{
	//��ʼ���ܿͻ��������߳����
	DWORD WINAPI StartAccept(LPVOID lpParam);

	DWORD WINAPI StartSelect1(LPVOID lpParam);

	CTcpServer::CTcpServer() :
		m_nServerPort(0),
		m_bInited(false),
		m_bListening(false),
		m_tiAccept({ 0 }),
		m_nMaxConnectionCount(0),
		m_nConnectedCount(0)
	{
		memset(m_strServerIP, 0, 20 * sizeof(TCHAR));
		m_fdRead.fd_count = 0;
	}

	CTcpServer::~CTcpServer()
	{
		CleanThread();
	}

	void CTcpServer::Init(TCHAR* ip, int port, int maxConn)
	{
		if (!m_bInited)//ֻ��ʼ��һ��
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
			//m_socketMgr.SetNonBlock(m_serverSocket);//�����첽��ʽ
			m_tiAccept.hThread = ::CreateThread(NULL, 0, NetworkCommunication::StartAccept, this, NULL, &m_tiAccept.dwThreadID);
			m_tiSelect.hThread = ::CreateThread(NULL, 0, NetworkCommunication::StartSelect1, this, NULL, &m_tiSelect.dwThreadID);
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
			if (clientSocket == 0)//�����˴���
			{

			}
			else
			{
				if (m_nConnectedCount == m_nMaxConnectionCount)//�Ƿ��Ѵﵽ�������������
				{
					m_socketMgr.CloseSocket(clientSocket);//�����Ͽ��ͻ�������
				}
				else
				{

					TCHAR ip[20];
					int port = 100;
					m_socketMgr.GetIpAndPort(clientSocket, ip, &port);

					//���յ��¿ͻ�������֪ͨ
					_tprintf(_T("Recv a new client connection: %s:%d \n"), ip, port);

					CTcpSession session(m_serverSocket, clientSocket);
					m_sessionMgr.Push(session);
					m_nConnectedCount++;

					if (m_nConnectedCount > 0)
					{
						//m_tiSelect.hThread = ::CreateThread(NULL, 0, NetworkCommunication::StartSelect1, this, NULL, &m_tiSelect.dwThreadID);
						//PauseThread(&m_tiSelect, false);
						//::ResumeThread(m_tiSelect.hThread);
					}
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

	DWORD WINAPI StartSelect1(LPVOID lpParam)
	{
		CTcpServer* p = (CTcpServer*)lpParam;
		p->StartSelect();
		return 0;
	}

	void CTcpServer::StartSelect()
	{
		::Sleep(10 * 1000);

		timeval timeout = { 0 };

		while (true)
		{
			FD_ZERO(&m_fdRead);//������ռ���
			for (vector<CTcpSession>::iterator it = m_sessionMgr.m_vecSessionList.begin(); it < m_sessionMgr.m_vecSessionList.end(); it++)
			{
				FD_SET(it->GetClientSocket(), &m_fdRead);//������Ҫ��ѯ��socket������
			}
			int result = ::select(0, &m_fdRead, NULL, NULL, &timeout);
			if (result > 0)
			{
				//m_sessionMgr.OnSelectReturn();
				for (vector<CTcpSession>::iterator it = m_sessionMgr.m_vecSessionList.begin(); it < m_sessionMgr.m_vecSessionList.end(); it++)
				{
					if (FD_ISSET(it->GetClientSocket(), &m_fdRead))
					{
						it->StartRecvData();
					}
				}
			}
		}
	}
}