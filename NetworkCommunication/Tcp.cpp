#include "stdafx.h"
#include "tcp.h"
#include "NetCommuMgr.h"
#include "TcpConnectionMgr.h"
#include "TcpConnection.h"
#include "RecvNewConnAction.h"
#include "Common.h"
#include "ServerTcpConnection.h"
#include "TcpServer.h"

namespace NetworkCommunication
{
	void OnAcceptThreadStart();

	CTcp::CTcp() :
		m_threadAccept(NULL)
	{

	}

	CTcp::~CTcp()
	{
		if (m_threadAccept)
		{
			delete m_threadAccept;
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

	void CTcp::PushTcpAction(CTcpAction* pAction)
	{
		m_quTcpAction.push(pAction);
	}

	void CTcp::ProcessQueue()
	{
		while ((int)m_quTcpAction.size() > 0)
		{
			CTcpAction* pAction = m_quTcpAction.front();
			m_quTcpAction.pop();

			switch (pAction->GetActionType())
			{
			case ETcpActionType::RecvNewConnection://�յ������Ӷ���
				ProcessRecvNewConnection((CRecvNewConnAction*)pAction);
				break;
			case ETcpActionType::RecvPeerData://�յ��Զ����ݶ���
				ProcessRecvPeerData((CRecvPeerDataAction*)pAction);
				break;
			case  ETcpActionType::PeerCloseConn://�Զ������رն���
				ProcessPeerCloseConn((CPeerCloseAction*)pAction);
				break;
			case  ETcpActionType::AsyncSendData://�첽�������ݶ���
				ProcessAsyncSendData((CAsyncSendDataAction*)pAction);
				break;
			case  ETcpActionType::SendDataResult://���ͶԶ����ݽ������
				ProcessSendPeerDataResult((CSendPeerDataResultAction*)pAction);
				break;
			case  ETcpActionType::NetError://���������
				ProcessNetError((CNetErrorAction*)pAction);
				break;
			case ETcpActionType::RefuseNewConn://�ܾ��ͻ������Ӷ���
				ProcessRefuseNewConn((CRefuseNewConnAction*)pAction);
				break;
			}
			delete pAction;
		}
	}

	void CTcp::ProcessRecvNewConnection(CRecvNewConnAction* pAction)
	{
		SOCKET serverSocket = pAction->GetAttachmentSocket();//��ȡ�����socket
		SOCKET sendrecvSocket = pAction->GetSendRecvSocket();//��ȡ����(����)���ݵ�socket

		//��ȡ�Զ���Ϣ
		char ip[20];
		int port = 0;
		m_socketAPI.GetPeerIpAndPort(sendrecvSocket, ip, &port);

		//��ȡ�����socket������tcp�������
		CTcpService* pTcpSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(serverSocket);
		if (pTcpSrv)
		{
			if (!((CTcpServer*)pTcpSrv)->IsAllow(ip))//�жϿͻ���IP�Ƿ񱻷��������
			{
				m_socketAPI.CloseSocket(sendrecvSocket);

				//�����ܾ��ͻ������Ӷ���
				CRefuseNewConnAction* pAction = new CRefuseNewConnAction(serverSocket, sendrecvSocket, ip, port);
				PushTcpAction(pAction);
				return;
			}

			//����tcp���Ӷ���
			CServerTcpConnection* conn = new CServerTcpConnection(pTcpSrv, sendrecvSocket, serverSocket);
			CNetworkCommuMgr::GetTcpConnectionMgr()->PushTcpConn(conn);//����tcp���Ӷ���

			PrintfDebug("[%s:%d][socket: %d] recv a new connection [%s:%d], server client socket: %d",
				pTcpSrv->GetLocalIP(), pTcpSrv->GetLocalPort(), pTcpSrv->GetSocket(), ip, port, sendrecvSocket);
			pTcpSrv->OnRecvNewConnection(ip, port, sendrecvSocket);//֪ͨtcp����˶�������
		}
	}

	void CTcp::ProcessRecvPeerData(CRecvPeerDataAction* pAction)
	{
		SOCKET recv = pAction->GetSendRecvSocket();//��ȡ�������ݵ�socket
		CTcpConnection* conn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(recv);//��ȡtcp���Ӷ���
		if (conn)
		{
			conn->OnRecvPeerData(pAction->GetPeerData());
		}
	}

	void CTcp::ProcessPeerCloseConn(CPeerCloseAction* pAction)
	{
		SOCKET recv = pAction->GetSendRecvSocket();//��ȡ�������ݵ�socket
		CTcpConnection* conn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(recv);//��ȡtcp���Ӷ���
		if (conn)
		{
			conn->OnPeerCloseConn();
		}
	}

	void CTcp::ProcessAsyncSendData(CAsyncSendDataAction* pAction)
	{
		SOCKET send = pAction->GetSendRecvSocket();//��ȡ�������ݵ�socket
		CTcpConnection* conn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(send);//��ȡtcp���Ӷ���
		if (conn)
		{
			AsyncSendPeerData* pData = pAction->GetSendData();//��ȡ��������
			conn->SendData(pData->pBuf, pData->len);
		}
	}

	void CTcp::ProcessSendPeerDataResult(CSendPeerDataResultAction* pAction)
	{
		SOCKET send = pAction->GetSendRecvSocket();//��ȡ�������ݵ�socket
		CTcpConnection* conn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(send);//��ȡtcp���Ӷ���
		if (conn)
		{
			conn->OnSendDataCompleted(pAction->GetResult());
		}
	}

	void CTcp::ProcessNetError(CNetErrorAction* pAction)
	{
		SOCKET socket = pAction->GetSendRecvSocket();//��ȡ����(����)���ݵ�socket
		CTcpConnection* conn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);//��ȡtcp���Ӷ���
		if (conn)
		{
			conn->OnNetError();
		}
	}

	void CTcp::ProcessRefuseNewConn(CRefuseNewConnAction* pAction)
	{
		SOCKET serverSocket = pAction->GetAttachmentSocket();//��ȡ�����socket
		SOCKET scSocket = pAction->GetSendRecvSocket();//��ȡ���ܾ��ķ���˵Ŀͻ���socket

		//��ȡ�����socket������tcp�������
		CTcpService* pTcpSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(serverSocket);
		if (pTcpSrv)
		{
			PrintfDebug("server [%s:%d][socket: %d] refuse the connection: %s:%d, server client socket: %d",
				pTcpSrv->GetLocalIP(), pTcpSrv->GetLocalPort(), pTcpSrv->GetSocket(), pAction->GetPeerIP(), pAction->GetPeerPort(), scSocket);

			pTcpSrv->OnRefuseNewConn(pAction->GetPeerIP(), pAction->GetPeerPort());
		}
	}
}