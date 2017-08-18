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

	void CTcp::ProcessQueue()
	{
		for (int i = 0; i < (int)m_quTcpAction.size(); i++)
		{
			CTcpAction* pAction = m_quTcpAction.front();
			m_quTcpAction.pop();

			switch (pAction->GetActionType())
			{
			case ETcpActionType::AcceptNewConnection://接收新连接动作
				ProcessAcceptNewConnection((CRecvNewConnAction*)pAction);
				break;
			case ETcpActionType::RecvPeerData://收到对端数据动作
				ProcessRecvPeerData((CRecvPeerDataAction*)pAction);
				break;
			}
			delete pAction;
		}
	}

	void CTcp::ProcessAcceptNewConnection(CRecvNewConnAction* pAction)
	{
		//创建tcp连接对象
		{
			//获取本地socket关联的tcp服务对象
			CTcpService* pTcpSrv = CNetworkCommuMgr::GetTcpServiceMgr()->GetTcpSrvByLocalSocket(pAction->GetServerSocket());

			//创建服务端tcp连接对象
			CServerTcpConnection* conn = new CServerTcpConnection(pTcpSrv, pAction->GetServerSocket(), pAction->GetServerClientSocket());

			CNetworkCommuMgr::GetTcpConnectionMgr()->PushTcpConn(conn);//加入tcp连接对象
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
		ServerSocket data = CNetworkCommuMgr::GetServerSocketMgr()->GetDataBySocket(server);//获取服务端socket数据
		SOCKET client = m_socketAPI.Accept(server, data.addr);
		if (client > 0)
		{
			CRecvNewConnAction* pAction = new CRecvNewConnAction(server, client);//创建tcp动作
			m_quTcpAction.push(pAction);
		}
	}

	void CTcp::OnReadWriteSocketCanRead(SOCKET socket)
	{
		int len = m_socketAPI.Recv(socket, m_pBuf, m_nBufLen);
		if (len > 0)//指示接收数据成功
		{
			//创建接收到对端数据动作
			PeerData* pData = new PeerData();
			pData->len = len;
			BYTE* pBuf = new BYTE[len];
			memcpy(pBuf, m_pBuf, len);
			pData->socket = socket;
			CRecvPeerDataAction* pAction = new CRecvPeerDataAction(pData);
			m_quTcpAction.push(pAction);
		}
		else if (len == 0)//指示对端主动关闭了socket
		{
			//删除select中相关socket
			CNetworkCommuMgr::GetSelect()->RemoveSocket(socket);
		}
		else//指示发送了网络错误
		{

		}
	}
}