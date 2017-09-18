#include "stdafx.h"
#include "Common.h"
#include "NetCommuMgr.h"
#include "tcp.h"
#include "TcpConnectionMgr.h"
#include "TcpConnection.h"
#include "ServerTcpConnection.h"
#include "TcpService.h"
#include "TcpServer.h"
#include "RecvNewConnEvt.h"
#include "RefuseNewConnEvt.h"

namespace NetworkCommunication
{
	CTcp::CTcp()
	{
		m_thread = new CThread(this);
	}

	CTcp::~CTcp()
	{
		if (m_thread)
		{
			delete m_thread;
		}
	}

	void CTcp::Run()
	{
		if (true)
		{
			m_thread->Run();
			PrintfInfo(_T("Tcp thread started"));
		}
	}

	void CTcp::OnThreadRun()
	{
		if (m_queueTcpAction.size() > 0)//���в�Ϊ��
		{
			ProcessTcpAction();
		}
		else
		{
			m_thread->Wait(5);
		}
	}

	void CTcp::PushTcpAction(CTcpAction* pAction)
	{
		m_queueTcpAction.push(pAction);
	}

	void CTcp::ProcessTcpAction()
	{
		while ((int)m_queueTcpAction.size() > 0)
		{
			CTcpAction* pAction = m_queueTcpAction.front();
			m_queueTcpAction.pop();

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
			case ETcpActionType::SocketExcept://socket�쳣����
				ProcessSocketExcept((CSocketExcept*)pAction);
				break;
			}

			delete pAction;
		}
	}

	void CTcp::ProcessRecvNewConnection(CRecvNewConnAction* pAction)
	{
		SOCKET serverSocket = pAction->GetAttachmentSocket();//��ȡ�����socket
		SOCKET clientSocket = pAction->GetSendRecvSocket();//��ȡ�ͻ���socket

		//��ȡ�ͻ�����Ϣ
		TCHAR ip[MAXIPSTRELN];
		int port = 0;
		m_socketAPI.GetPeerIpAndPort(clientSocket, ip, &port);

		//��ȡ�����socket������tcp�������
		CTcpService* pTcpSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(serverSocket);
		if (pTcpSrv)
		{
			if (!((CTcpServer*)pTcpSrv)->IsAllow(ip))//�жϿͻ���IP�Ƿ񱻷��������
			{
				m_socketAPI.CloseSocket(clientSocket);

				PrintfInfo(_T("[%s:%d][socket: %d] refuse a new connection [%s:%d][socket: %d]"),
					pTcpSrv->GetLocalIP(), pTcpSrv->GetLocalPort(), pTcpSrv->GetSocket(), ip, port, clientSocket);
				CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpEvent(new CRefuseNewConnEvt(pTcpSrv, clientSocket, ip, port));
			}
			else
			{
				PrintfInfo(_T("[%s:%d][socket: %d] recv a new connection [%s:%d][socket: %d]"),
					pTcpSrv->GetLocalIP(), pTcpSrv->GetLocalPort(), pTcpSrv->GetSocket(), ip, port, clientSocket);
				CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpEvent(new CRecvNewConnEvt(pTcpSrv, clientSocket));
			}
		}
	}

	void CTcp::ProcessRecvPeerData(CRecvPeerDataAction* pAction)
	{
		SOCKET recv = pAction->GetSendRecvSocket();//��ȡ�������ݵ�socket

		CTcpService* pTcpSrv = NULL;//tcp�������
		CTcpConnection* pConn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(recv);//��ȡtcp���Ӷ���
		if (pConn)
		{
			pTcpSrv = pConn->GetTcpService();//��ȡtcp�������
			pConn->OnRecvPeerData(pAction);
		}
		else
		{
			delete pAction->GetBuf();
		}
	}

	void CTcp::ProcessPeerCloseConn(CPeerCloseAction* pAction)
	{
		SOCKET sendrecvSocket = pAction->GetSendRecvSocket();//��ȡ����(����)���ݵ�socket

		CTcpService* pTcpSrv = NULL;//tcp�������
		CTcpConnection* pConn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(sendrecvSocket);//��ȡtcp���Ӷ���
		if (pConn)
		{
			pTcpSrv = pConn->GetTcpService();//��ȡtcp�������
			pConn->OnTcpDisconnect(ETcpDisconnectReason::Peer);
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

			//CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpEvent(pAction);
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

	void CTcp::ProcessSocketExcept(CSocketExcept* pAction)
	{
		PrintfError(_T("socket except: %d"), pAction->GetAttachmentSocket());
		CNetworkCommuMgr::GetSelect()->RemoveSocket(pAction->GetAttachmentSocket());

		if (pAction->GetSendRecvSocket() == ESelectSocketType::ReadWriteData)
		{
			CTcpConnection* pConn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(pAction->GetAttachmentSocket());//��ȡtcp���Ӷ���
			if (pConn)
			{
				pConn->OnTcpDisconnect(ETcpDisconnectReason::Except);
			}
		}
		else if (pAction->GetSendRecvSocket() == ESelectSocketType::RecvConn)
		{

		}
	}
}