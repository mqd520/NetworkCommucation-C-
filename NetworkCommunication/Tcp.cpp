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
		if (m_queueTcpAction.size() > 0)//队列不为空
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
			case ETcpActionType::RecvNewConnection://收到新连接动作
				ProcessRecvNewConnection((CRecvNewConnAction*)pAction);
				break;
			case ETcpActionType::RecvPeerData://收到对端数据动作
				ProcessRecvPeerData((CRecvPeerDataAction*)pAction);
				break;
			case  ETcpActionType::PeerCloseConn://对端主动关闭动作
				ProcessPeerCloseConn((CPeerCloseAction*)pAction);
				break;
			case  ETcpActionType::AsyncSendData://异步发送数据动作
				ProcessAsyncSendData((CAsyncSendDataAction*)pAction);
				break;
			case  ETcpActionType::SendDataResult://发送对端数据结果动作
				ProcessSendPeerDataResult((CSendPeerDataResultAction*)pAction);
				break;
			case  ETcpActionType::NetError://网络错误动作
				ProcessNetError((CNetErrorAction*)pAction);
				break;
			case ETcpActionType::SocketExcept://socket异常动作
				ProcessSocketExcept((CSocketExcept*)pAction);
				break;
			}

			delete pAction;
		}
	}

	void CTcp::ProcessRecvNewConnection(CRecvNewConnAction* pAction)
	{
		SOCKET serverSocket = pAction->GetAttachmentSocket();//获取服务端socket
		SOCKET clientSocket = pAction->GetSendRecvSocket();//获取客户端socket

		//获取客户端信息
		TCHAR ip[MAXIPSTRELN];
		int port = 0;
		m_socketAPI.GetPeerIpAndPort(clientSocket, ip, &port);

		//获取服务端socket关联的tcp服务对象
		CTcpService* pTcpSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(serverSocket);
		if (pTcpSrv)
		{
			if (!((CTcpServer*)pTcpSrv)->IsAllow(ip))//判断客户端IP是否被服务端允许
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
		SOCKET recv = pAction->GetSendRecvSocket();//获取接收数据的socket

		CTcpService* pTcpSrv = NULL;//tcp服务对象
		CTcpConnection* pConn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(recv);//获取tcp连接对象
		if (pConn)
		{
			pTcpSrv = pConn->GetTcpService();//获取tcp服务对象
			pConn->OnRecvPeerData(pAction);
		}
		else
		{
			delete pAction->GetBuf();
		}
	}

	void CTcp::ProcessPeerCloseConn(CPeerCloseAction* pAction)
	{
		SOCKET sendrecvSocket = pAction->GetSendRecvSocket();//获取发送(接收)数据的socket

		CTcpService* pTcpSrv = NULL;//tcp服务对象
		CTcpConnection* pConn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(sendrecvSocket);//获取tcp连接对象
		if (pConn)
		{
			pTcpSrv = pConn->GetTcpService();//获取tcp服务对象
			pConn->OnTcpDisconnect(ETcpDisconnectReason::Peer);
		}
	}

	void CTcp::ProcessAsyncSendData(CAsyncSendDataAction* pAction)
	{
		SOCKET send = pAction->GetSendRecvSocket();//获取发送数据的socket
		CTcpConnection* conn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(send);//获取tcp连接对象
		if (conn)
		{
			AsyncSendPeerData* pData = pAction->GetSendData();//获取发送数据
			conn->SendData(pData->pBuf, pData->len);
		}
	}

	void CTcp::ProcessSendPeerDataResult(CSendPeerDataResultAction* pAction)
	{
		SOCKET send = pAction->GetSendRecvSocket();//获取发送数据的socket
		CTcpConnection* conn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(send);//获取tcp连接对象
		if (conn)
		{
			conn->OnSendDataCompleted(pAction->GetResult());

			//CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpEvent(pAction);
		}
	}

	void CTcp::ProcessNetError(CNetErrorAction* pAction)
	{
		SOCKET socket = pAction->GetSendRecvSocket();//获取发送(接收)数据的socket
		CTcpConnection* conn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(socket);//获取tcp连接对象
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
			CTcpConnection* pConn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(pAction->GetAttachmentSocket());//获取tcp连接对象
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