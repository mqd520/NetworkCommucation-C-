#include "stdafx.h"
#include "TcpConnectionMgr.h"
#include "NetCommuMgr.h"

namespace NetworkCommunication
{
	void OnRWThreadStart();

	CTcpConnectionMgr::CTcpConnectionMgr():
		m_threadRW(NULL)
	{

	}

	CTcpConnectionMgr::~CTcpConnectionMgr()
	{

	}

	void CTcpConnectionMgr::Push(CTcpConnection* session)
	{
		m_vecConnectionList.push_back(session);
		SOCKET socket = session->GetPeerSocket();//获取tcp连接中对端的socket
		CNetworkCommuMgr::GetSelect()->AddPeerSocket(socket);//加入对端socket队列
	}

	void CTcpConnectionMgr::OnSocketRead(SOCKET socket)
	{
		BYTE* p = new BYTE[1024];
		int result = m_socMgr.Recv(socket, p, 1024);
		if (result > 0)
		{
			_tprintf(_T("Recv data from %d, size: %d \n"), socket, result);
		}
		else
		{

		}
		delete p;
	}

	void OnRWThreadStart()
	{
		_tprintf(_T("Rw thread started \n"));
		CNetworkCommuMgr::GetTcpConnectionMgr()->ThreadEntry();
	}

	void CTcpConnectionMgr::ThreadEntry()
	{
		while (true)
		{
			if (m_quSocket.size() > 0)
			{
				SOCKET socket = m_quSocket.front();
				m_quSocket.pop();
				for (int i = 0; i < (int)m_vecConnectionList.size(); i++)
				{
					if (m_vecConnectionList[i]->GetPeerSocket() == socket)
					{
						m_vecConnectionList[i]->OnReadData();
						break;
					}
				}
			}
			else
			{
				Sleep(10);
			}
		}
	}

	void CTcpConnectionMgr::Run()
	{
		if (m_threadRW == NULL)
		{
			m_threadRW = new CThread();
			m_threadRW->SetCallback(OnRWThreadStart);
			m_threadRW->Start();
		}
	}
}