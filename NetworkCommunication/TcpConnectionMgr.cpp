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
		SOCKET socket = session->GetPeerSocket();//��ȡtcp�����жԶ˵�socket
		CNetworkCommuMgr::GetSelect()->AddSocket(socket, ESelectSocketType::Peer);//����select����
	}

	void CTcpConnectionMgr::OnSocketCanRead(SOCKET socket)
	{
		BYTE* buf = new BYTE[TCPBUFFERSIZE];
		int len = m_socketAPI.Recv(socket, buf, TCPBUFFERSIZE);
		if (len > 0)//ָʾ��ȡ���ݳɹ�
		{
			m_quSocketRecvData.push({ socket, buf, len });
		}
		else if (len == 0)//ָʾ�Զ������ر���socket
		{
			RemoveTcpConnByPeerSocket(socket);//ɾ��������tcp����
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
					if (m_vecTcpConnection[i]->GetPeerSocket() == data.peer)//�ҵ���Ӧ��tcp���Ӳ�
					{
						m_vecTcpConnection[i]->OnRecvData(data);//֪ͨtcp���Ӳ���д���
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
		//ɾ��tcp����
		for (vector<CTcpConnection*>::iterator it = m_vecTcpConnection.begin(); it < m_vecTcpConnection.end(); it++)
		{
			if ((*it)->GetPeerSocket() == peer)
			{
				m_vecTcpConnection.erase(it);
				break;
			}
		}

		//ɾ��select�����socket
		CNetworkCommuMgr::GetSelect()->RemoveSocket(peer);
	
		//����tcp����: �Զ������ر�
		CPeerCloseAction* pAction = new CPeerCloseAction(peer);
		CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpAction(pAction);
	}
}