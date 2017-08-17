#include "stdafx.h"
#include "TcpConnection.h"
#include "MemoryTool.h"
#include "Common.h"
#include "RecvPeerDataAction.h"
#include "NetCommuMgr.h"
#include "SendPeerDataResultAction.h"

namespace NetworkCommunication
{
	CTcpConnection::CTcpConnection(SOCKET localSocket, SOCKET peerSocket/* = NULL*/, CTcpService* pSrv/* = NULL*/) :
		m_peerSocket(peerSocket),
		m_localSocket(localSocket),
		m_pTcpSrv(pSrv)
	{

	}

	CTcpConnection::~CTcpConnection()
	{

	}

	SOCKET CTcpConnection::GetSendSocket()
	{
		if (m_peerSocket == NULL)//表示当前连接属于tcp客户端连接
		{
			return m_localSocket;
		}
		else//表示当前连接属于tcp服务端连接
		{
			return m_peerSocket;
		}
	}

	bool CTcpConnection::SendData(BYTE buf[], int len, int* actualLen)
	{
		bool result = m_socketAPI.Send(GetSendSocket(), buf, len, actualLen);

		//创建发送数据结果动作
		SendPeerDataResult data;
		data.success = result;
		data.len = len;
		data.peer = m_peerSocket;
		if (m_peerSocket == NULL)//表示当前连接属于tcp客户端连接
		{

		}
		else
		{
			PeerSocketData peerData = CNetworkCommuMgr::GetPeerSocketDataMgr()->GetDataByPeer(m_peerSocket);//获取对端socket数据
			strcpy(data.ip, peerData.ip);
			data.port = peerData.port;
		}
		CSendPeerDataResultAction* pAction = new CSendPeerDataResultAction(data, m_localSocket);
		CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpAction(pAction);

		if (!result)//发送失败
		{
			if (m_pTcpSrv != NULL && m_pTcpSrv->GetSrvType() == ETcpServiceType::Server)//指示tcp服务端对象
			{
				CNetworkCommuMgr::GetSelect()->RemoveSocket(m_peerSocket);//从select中移除对端socket
			}
			else
			{

			}
		}
		return result;
	}

	void CTcpConnection::OnRecvPeerData(SocketRecvData data)
	{
		//创建
		CRecvPeerDataAction* pAction = new CRecvPeerDataAction(data, m_localSocket);
		CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpAction(pAction);
	}

	void CTcpConnection::OnPeerClose(SOCKET peer)
	{
		//生成tcp动作: 对端主动关闭
		CPeerCloseAction* pAction = new CPeerCloseAction(m_localSocket, peer);
		CNetworkCommuMgr::GetTcpServiceMgr()->PushTcpAction(pAction);

		CNetworkCommuMgr::GetTcpConnectionMgr()->OnPeerClose(peer);//通知tcp连接管理,对端主动关闭
	}

	SOCKET CTcpConnection::GetLocalSocket()
	{
		return m_localSocket;
	}

	SOCKET CTcpConnection::GetPeerSocket()
	{
		return m_peerSocket;
	}
}