#include "stdafx.h"
#include "tcp.h"
#include "NetCommuMgr.h"
#include "TcpConnectionMgr.h"
#include "TcpConnection.h"
#include "RecvNewConnAction.h"
#include "Common.h"
#include "ServerTcpConnection.h"

namespace NetworkCommunication
{
	void OnAcceptThreadStart();

	CTcp::CTcp() :
		m_threadAccept(NULL),
		m_nBufLen(TCPRECVBUFFERSIZE)
	{
		m_pBuf = new BYTE[m_nBufLen];
	}

	CTcp::~CTcp()
	{
		if (m_threadAccept)
		{
			delete m_threadAccept;
		}
		if (m_pBuf)
		{
			delete m_pBuf;
		}
	}

	void OnAcceptThreadStart()
	{
		PrintfInfo("tcp thread started");
		CNetworkCommuMgr::GetTcp()->ThreadEntry();
	}

	void CTcp::Run()
	{
		if (m_threadAccept == NULL)
		{
			m_threadAccept = new CThread();
			m_threadAccept->SetCallback(OnAcceptThreadStart);
			m_threadAccept->Start();
		}
	}

	void CTcp::ThreadEntry()
	{
		while (true)
		{
			if (m_quTcpAction.size() > 0)//���в�Ϊ��
			{
				ProcessQueue();
			}
			else
			{
				Sleep(10);
			}
		}
	}

	void CTcp::ProcessQueue()
	{
		for (int i = 0; i < (int)m_quTcpAction.size(); i++)
		{
			CTcpAction* pAction = m_quTcpAction.front();
			m_quTcpAction.pop();

			switch (pAction->GetActionType())
			{
			case ETcpActionType::AcceptNewConnection://���������Ӷ���
				ProcessAcceptNewConnection((CRecvNewConnAction*)pAction);
				break;
			case ETcpActionType::RecvPeerData://�յ��Զ����ݶ���
				ProcessRecvPeerData((CRecvPeerDataAction*)pAction);
				break;
			}
			delete pAction;
		}
	}

	void CTcp::ProcessAcceptNewConnection(CRecvNewConnAction* pAction)
	{
		//����tcp���Ӷ���
		{
			//��ȡ����socket������tcp�������
			CTcpService* pTcpSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvByLocalSocket(pAction->GetServerSocket());

			//���������tcp���Ӷ���
			CServerTcpConnection* conn = new CServerTcpConnection(pTcpSrv, pAction->GetServerSocket(), pAction->GetServerClientSocket());

			CNetworkCommuMgr::GetTcpConnectionMgr()->PushTcpConn(conn);//����tcp���Ӷ���
		}

		CNetworkCommuMgr::GetTcpServiceMgr()->OnRecvNewConnection(pAction);
	}

	void CTcp::ProcessRecvPeerData(CRecvPeerDataAction* pAction)
	{
		CNetworkCommuMgr::GetTcpConnectionMgr()->OnRecvPeerData(pAction->GetPeerData());
	}

	bool CTcp::FilterClientSocket(SOCKET server, SOCKET client)
	{
		return true;
	}

	void CTcp::OnServerSocketCanRead(SOCKET server)
	{
		ServerSocket data = CNetworkCommuMgr::GetServerSocketMgr()->GetDataBySocket(server);//��ȡ�����socket����
		SOCKET client = m_socketAPI.Accept(server, data.addr);
		if (client > 0)
		{
			CRecvNewConnAction* pAction = new CRecvNewConnAction(server, client);//����tcp����
			m_quTcpAction.push(pAction);
		}
	}

	void CTcp::OnReadWriteSocketCanRead(SOCKET socket)
	{
		int len = m_socketAPI.Recv(socket, m_pBuf, m_nBufLen);
		if (len > 0)//ָʾ�������ݳɹ�
		{
			//�������յ��Զ����ݶ���
			PeerData* pData = new PeerData();
			pData->len = len;
			BYTE* pBuf = new BYTE[len];
			memcpy(pBuf, m_pBuf, len);
			pData->socket = socket;
			CRecvPeerDataAction* pAction = new CRecvPeerDataAction(pData);
			m_quTcpAction.push(pAction);
		}
		else if (len == 0)//ָʾ�Զ������ر���socket
		{
			//ɾ��select�����socket
			CNetworkCommuMgr::GetSelect()->RemoveSocket(socket);
		}
		else//ָʾ�������������
		{

		}
	}
}