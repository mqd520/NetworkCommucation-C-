#include "stdafx.h"
#include "Accept.h"
#include "NetCommuMgr.h"
#include "TcpConnectionMgr.h"
#include "TcpConnection.h"

namespace NetworkCommunication
{
	void OnAcceptThreadStart();

	CAccept::CAccept() :
		m_threadAccept(NULL)
	{

	}

	CAccept::~CAccept()
	{
		if (m_threadAccept)
		{
			delete m_threadAccept;
		}
	}

	void CAccept::OnRecvNewSocket(SOCKET socket)
	{
		ServerSocketData data = CNetworkCommuMgr::GetServerSocketMgr()->GetDataBySocket(socket);//获取服务端socket关联数据
		if (data.socket != NULL)
		{
			SOCKET client = m_socMgr.Accept(socket, data.addr);//接收新连接
			m_quSocket.push({ socket, client });
			_tprintf(_T("Accept a new connection from %s:%d, client: %d \n"), data.ip, data.port, client);
		}
	}

	void OnAcceptThreadStart()
	{
		_tprintf(_T("Accept thread started \n"));
		CNetworkCommuMgr::GetAccept()->ThreadEntry();
	}

	void CAccept::Run()
	{
		if (m_threadAccept == NULL)
		{
			m_threadAccept = new CThread();
			m_threadAccept->SetCallback(OnAcceptThreadStart);
			m_threadAccept->Start();
		}
	}

	void CAccept::ThreadEntry()
	{
		while (true)
		{
			if (m_quSocket.size() > 0)//队列不为空
			{
				ProcessAcceptQueue();
			}
			else
			{
				Sleep(10);
			}
		}
	}

	void CAccept::ProcessAcceptQueue()
	{
		for (int i = 0; i < (int)m_quSocket.size(); i++)
		{
			SocketPair data = m_quSocket.front();
			m_quSocket.pop();
			CTcpConnection* conn = new CTcpConnection(data.local, data.peer);
			CNetworkCommuMgr::GetTcpConnectionMgr()->Push(conn);
		}
	}
}