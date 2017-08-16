#include "stdafx.h"
#include "TcpConnectionMgr.h"
#include "NetCommuMgr.h"
#include "Common.h"
#include "PeerCloseAction.h"

namespace NetworkCommunication
{
	void OnRWThreadStart();

	CTcpConnectionMgr::CTcpConnectionMgr() :
		m_threadRW(NULL)
	{

	}

	CTcpConnectionMgr::~CTcpConnectionMgr()
	{

	}

	void CTcpConnectionMgr::PushTcpConn(CTcpConnection* session)
	{
		m_vecTcpConnection.push_back(session);
		SOCKET socket = session->GetPeerSocket();//获取tcp连接中对端的socket
		CNetworkCommuMgr::GetSelect()->AddSocket(socket, ESelectSocketType::Peer);//加入select队列
	}

	void CTcpConnectionMgr::OnSocketCanRead(SOCKET socket)
	{
		BYTE* buf = new BYTE[TCPBUFFERSIZE];
		int len = m_socketAPI.Recv(socket, buf, TCPBUFFERSIZE);
		if (len > 0)//指示读取数据成功
		{
			m_quSocketRecvData.push({ socket, buf, len });
		}
		else if (len == 0)//指示对端主动关闭了socket
		{
			RemoveTcpConnByPeerSocket(socket);//删除关联的tcp连接
			delete buf;
		}
		else
		{

		}
	}

	void OnRWThreadStart()
	{
		Printf1("Tcp connection thread started");
		CNetworkCommuMgr::GetTcpConnectionMgr()->ThreadEntry();
	}

	void CTcpConnectionMgr::ThreadEntry()
	{
		while (true)
		{
			if (m_quSocketRecvData.size() > 0)
			{
				SocketRecvData data = m_quSocketRecvData.front();
				m_quSocketRecvData.pop();

				for (int i = 0; i < (int)m_vecTcpConnection.size(); i++)
				{
					if (m_vecTcpConnection[i]->GetPeerSocket() == data.peer)//找到对应的tcp连接层
					{
						m_vecTcpConnection[i]->OnRecvData(data);//通知tcp连接层进行处理
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

	void CTcpConnectionMgr::RemoveByPeer(SOCKET peer)
	{
		for (int i = 0; i < (int)m_vecTcpConnection.size(); i++)
		{
			if (m_vecTcpConnection[i]->GetPeerSocket() == peer)
			{
				m_vecTcpConnection.erase(m_vecTcpConnection.begin() + i);
				break;
			}
		}
	}

	CTcpConnection* CTcpConnectionMgr::GetTcpConnByPeerSocket(SOCKET peer)
	{
		for (int i = 0; i < (int)m_vecTcpConnection.size(); i++)
		{
			if (m_vecTcpConnection[i]->GetPeerSocket() == peer)
			{
				return m_vecTcpConnection[i];
			}
		}
		return NULL;
	}

	void CTcpConnectionMgr::RemoveTcpConnByPeerSocket(SOCKET peer)
	{
		//删除tcp连接
		for (vector<CTcpConnection*>::iterator it = m_vecTcpConnection.begin(); it < m_vecTcpConnection.end(); it++)
		{
			if ((*it)->GetPeerSocket() == peer)
			{
				m_vecTcpConnection.erase(it);
				break;
			}
		}

		//删除select中相关socket
		CNetworkCommuMgr::GetSelect()->RemoveSocket(peer);
	
		//生成tcp动作: 对端主动关闭
		CPeerCloseAction* pAction = new CPeerCloseAction(peer);
		CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpAction(pAction);
	}
}