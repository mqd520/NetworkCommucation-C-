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

	void CTcpConnectionMgr::OnPeerSocketCanRead(SOCKET peer)
	{
		BYTE* buf = new BYTE[TCPBUFFERSIZE];
		int len = m_socketAPI.Recv(peer, buf, TCPBUFFERSIZE);
		if (len > 0)//指示读取数据成功
		{
			m_quSocketSendRecvData.push({ peer, buf, len, ESocketSendRecvType::Recv });
		}
		else if (len == 0)//指示对端主动关闭了socket
		{
			delete buf;

			//删除select中相关socket
			CNetworkCommuMgr::GetSelect()->RemoveSocket(peer);

			m_quSocketSendRecvData.push({ peer, NULL, 0, ESocketSendRecvType::Recv });
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
			if (m_quSocketSendRecvData.size() > 0)
			{
				SocketRecvData data = m_quSocketSendRecvData.front();
				m_quSocketSendRecvData.pop();

				//遍历tcp连接对象
				for (int i = 0; i < (int)m_vecTcpConnection.size(); i++)
				{
					if (data.type == ESocketSendRecvType::Recv)//接收数据
					{
						if (m_vecTcpConnection[i]->GetPeerSocket() == data.peer)//找到对应的tcp连接层
						{
							if (data.len > 0)
							{
								m_vecTcpConnection[i]->OnRecvPeerData(data);//通知tcp连接层进行处理
							}
							else
							{
								m_vecTcpConnection[i]->OnPeerClose(data.peer);//通知tcp连接层进行处理
							}
							break;
						}
					}
					else//发送数据
					{
						if (m_vecTcpConnection[i]->GetPeerSocket() == data.peer)
						{
							m_vecTcpConnection[i]->SendData(data.pBuf, data.len);
						}
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
		for (vector<CTcpConnection*>::iterator it = m_vecTcpConnection.begin(); it < m_vecTcpConnection.end(); it++)
		{
			if ((*it)->GetPeerSocket() == peer)
			{
				m_vecTcpConnection.erase(it);
				break;
			}
		}
	}

	void CTcpConnectionMgr::OnPeerClose(SOCKET peer)
	{
		RemoveTcpConnByPeerSocket(peer);
	}

	void CTcpConnectionMgr::UnAsyncSend(SOCKET socket, BYTE buf[], int len, int* actualLen)
	{
		m_quSocketSendRecvData.push({ socket, buf, len, ESocketSendRecvType::Send });
	}
}