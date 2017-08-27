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
			if (m_quTcpAction.size() > 0)//队列不为空
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
			case ETcpActionType::RefuseNewConn://拒绝客户端连接动作
				ProcessRefuseNewConn((CRefuseNewConnAction*)pAction);
				break;
			}
			delete pAction;
		}
	}

	void CTcp::ProcessRecvNewConnection(CRecvNewConnAction* pAction)
	{
		SOCKET serverSocket = pAction->GetAttachmentSocket();//获取服务端socket
		SOCKET sendrecvSocket = pAction->GetSendRecvSocket();//获取发送(接收)数据的socket

		//获取对端信息
		char ip[20];
		int port = 0;
		m_socketAPI.GetPeerIpAndPort(sendrecvSocket, ip, &port);

		//获取服务端socket关联的tcp服务对象
		CTcpService* pTcpSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(serverSocket);
		if (pTcpSrv)
		{
			if (!((CTcpServer*)pTcpSrv)->IsAllow(ip))//判断客户端IP是否被服务端允许
			{
				m_socketAPI.CloseSocket(sendrecvSocket);

				//创建拒绝客户端连接动作
				CRefuseNewConnAction* pAction = new CRefuseNewConnAction(serverSocket, sendrecvSocket, ip, port);
				PushTcpAction(pAction);
				return;
			}

			//创建tcp连接对象
			CServerTcpConnection* conn = new CServerTcpConnection(pTcpSrv, sendrecvSocket, serverSocket);
			CNetworkCommuMgr::GetTcpConnectionMgr()->PushTcpConn(conn);//加入tcp连接对象

			PrintfDebug("[%s:%d][socket: %d] recv a new connection [%s:%d], server client socket: %d",
				pTcpSrv->GetLocalIP(), pTcpSrv->GetLocalPort(), pTcpSrv->GetSocket(), ip, port, sendrecvSocket);
			pTcpSrv->OnRecvNewConnection(ip, port, sendrecvSocket);//通知tcp服务端对象处理动作
		}
	}

	void CTcp::ProcessRecvPeerData(CRecvPeerDataAction* pAction)
	{
		SOCKET recv = pAction->GetSendRecvSocket();//获取接收数据的socket
		CTcpConnection* conn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(recv);//获取tcp连接对象
		if (conn)
		{
			conn->OnRecvPeerData(pAction->GetPeerData());
		}
	}

	void CTcp::ProcessPeerCloseConn(CPeerCloseAction* pAction)
	{
		SOCKET recv = pAction->GetSendRecvSocket();//获取接收数据的socket
		CTcpConnection* conn = CNetworkCommuMgr::GetTcpConnectionMgr()->GetBySendRecvSocket(recv);//获取tcp连接对象
		if (conn)
		{
			conn->OnPeerCloseConn();
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

	void CTcp::ProcessRefuseNewConn(CRefuseNewConnAction* pAction)
	{
		SOCKET serverSocket = pAction->GetAttachmentSocket();//获取服务端socket
		SOCKET scSocket = pAction->GetSendRecvSocket();//获取被拒绝的服务端的客户端socket

		//获取服务端socket关联的tcp服务对象
		CTcpService* pTcpSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvBySocket(serverSocket);
		if (pTcpSrv)
		{
			PrintfDebug("server [%s:%d][socket: %d] refuse the connection: %s:%d, server client socket: %d",
				pTcpSrv->GetLocalIP(), pTcpSrv->GetLocalPort(), pTcpSrv->GetSocket(), pAction->GetPeerIP(), pAction->GetPeerPort(), scSocket);

			pTcpSrv->OnRefuseNewConn(pAction->GetPeerIP(), pAction->GetPeerPort());
		}
	}
}