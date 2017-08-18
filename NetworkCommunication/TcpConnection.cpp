#include "stdafx.h"
#include "TcpConnection.h"
#include "MemoryTool.h"
#include "Common.h"
#include "RecvPeerDataAction.h"
#include "NetCommuMgr.h"
#include "SendPeerDataResultAction.h"

namespace NetworkCommunication
{
	CTcpConnection::CTcpConnection(CTcpService* pSrv, SOCKET sendrecv) :
		m_pTcpSrv(pSrv),
		m_sendrecvSocket(sendrecv)
	{
		CNetworkCommuMgr::GetSelect()->AddSocket(sendrecv, ESelectSocketType::ReadWriteData);//加入select队列
	}

	CTcpConnection::~CTcpConnection()
	{

	}

	SOCKET CTcpConnection::GetSendRecvSocket()
	{
		return m_sendrecvSocket;
	}

	CTcpService* CTcpConnection::GetTcpService()
	{
		return m_pTcpSrv;
	}

	bool CTcpConnection::SendData(BYTE buf[], int len, int* actualLen)
	{
		bool result = m_socketAPI.Send(GetSendRecvSocket(), buf, len, actualLen);

		//创建发送数据结果动作
		SendPeerDataResult data;
		data.success = result;
		data.len = len;
		data.peer = m_sendrecvSocket;
		ServerClientSocket peerData = CNetworkCommuMgr::GetServerClientSocketMgr()->GetDataByServerClientSocket(m_sendrecvSocket);//获取对端socket数据
		strcpy(data.ip, peerData.ip);
		data.port = peerData.port;
		CSendPeerDataResultAction* pAction = new CSendPeerDataResultAction(data, m_sendrecvSocket);

		if (!result)//发送失败
		{
			if (m_pTcpSrv != NULL && m_pTcpSrv->GetSrvType() == ETcpServiceType::Server)//指示tcp服务端对象
			{
				CNetworkCommuMgr::GetSelect()->RemoveSocket(m_sendrecvSocket);//从select中移除对端socket
			}
			else
			{

			}
		}
		return result;
	}

	void CTcpConnection::OnRecvPeerData(PeerData* data)
	{
		if (m_pTcpSrv)
		{
			if (m_pTcpSrv->GetSrvType() == ETcpServiceType::Server)
			{
				ServerClientSocket scData = CNetworkCommuMgr::GetServerClientSocketMgr()->GetDataByServerClientSocket(data->socket);
				ServerSocket sData = CNetworkCommuMgr::GetServerSocketMgr()->GetDataBySocket(scData.server);
				PrintfDebug("[%s:%d] recv [%s:%d] data, size: %d, socket: %d,%d", sData.ip, sData.port, scData.ip, scData.port, sData.socket, scData.client);
			}

			m_pTcpSrv->OnRecvPeerData(data);
		}
	}

	void CTcpConnection::OnPeerCloseSocket(SOCKET peer)
	{
		////生成tcp动作: 对端主动关闭
		//CPeerCloseAction* pAction = new CPeerCloseAction(m_localSocket, peer);
		//CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpAction(pAction);

		//CNetworkCommuMgr::GetTcpConnectionMgr()->OnPeerClose(peer);//通知tcp连接管理,对端主动关闭
	}
}