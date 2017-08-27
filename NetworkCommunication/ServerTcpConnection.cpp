#include "stdafx.h"
#include "ServerTcpConnection.h"
#include "RecvNewConnAction.h"
#include "NetCommuMgr.h"
#include "Common.h"

namespace NetworkCommunication
{
	CServerTcpConnection::CServerTcpConnection(CTcpService* pTcpSrv, SOCKET scSocket, SOCKET server) :
		CTcpConnection(pTcpSrv, scSocket),
		m_serverSocket(server)
	{
		ServerClientSocket data = { 0 };
		data.scClient = scSocket;
		data.server = server;
		m_socketAPI.GetPeerIpAndPort(scSocket, data.ip, &data.port);
		CNetworkCommuMgr::GetServerClientSocketMgr()->PushSocketData(data);
	}

	CServerTcpConnection::~CServerTcpConnection()
	{

	}

	SOCKET CServerTcpConnection::GetServerSocket()
	{
		return m_serverSocket;
	}

	void CServerTcpConnection::OnRecvPeerData(PeerData* pData)
	{
		//获取服务端的客户端socket数据
		ServerClientSocket scData = CNetworkCommuMgr::GetServerClientSocketMgr()->GetDataByServerClientSocket(pData->socket);
		strcpy(pData->ip, scData.ip);
		pData->port = scData.port;
		PrintfDebug("[%s:%d][socket: %d] recved [%s:%d] data, size: %d, server client socket: %d",
			m_pTcpSrv->GetLocalIP(), m_pTcpSrv->GetLocalPort(), m_pTcpSrv->GetSocket(), scData.ip, scData.port, pData->len, scData.scClient);

		__super::OnRecvPeerData(pData);
	}

	void CServerTcpConnection::OnPeerCloseConn()
	{
		__super::OnPeerCloseConn();

		//获取服务客户端socket数据
		ServerClientSocket scData = CNetworkCommuMgr::GetServerClientSocketMgr()->GetDataByServerClientSocket(m_sendrecvSocket);
		PrintfDebug("client [%s:%d] closed the connection, server: [%s:%d][socket: %d], server client socket: %d",
			scData.ip, scData.port, m_pTcpSrv->GetLocalIP(), m_pTcpSrv->GetLocalPort(), m_pTcpSrv->GetSocket(), scData.scClient);

		m_pTcpSrv->OnPeerCloseConn(scData.ip, scData.port);
	}

	void CServerTcpConnection::OnSendDataCompleted(SendPeerDataResult* pResult)
	{
		__super::OnSendDataCompleted(pResult);

		//获取服务客户端socket数据
		ServerClientSocket scData = CNetworkCommuMgr::GetServerClientSocketMgr()->GetDataByServerClientSocket(m_sendrecvSocket);
		if (pResult->success)
		{
			PrintfDebug("[%s:%d][socket: %d] send data to [%s:%d] successed, size: %d, server client socket: %d",
				m_pTcpSrv->GetLocalIP(), m_pTcpSrv->GetLocalPort(), m_pTcpSrv->GetSocket(), scData.ip, scData.port, pResult->len, scData.scClient);
		}
		else
		{
			PrintfDebug("[%s:%d][socket: %d] send data to [%s:%d] failed, size: %d, actual size: %d",
				m_pTcpSrv->GetLocalIP(), m_pTcpSrv->GetLocalPort(), m_pTcpSrv->GetSocket(), scData.ip, scData.port, scData.scClient, pResult->len, pResult->actualLen);
		}

		strcpy(pResult->ip, scData.ip);
		pResult->port = scData.port;
		m_pTcpSrv->OnSendPeerDataCompleted(pResult);
	}

	void CServerTcpConnection::OnNetError()
	{
		__super::OnNetError();

		//获取服务客户端socket数据
		ServerClientSocket scData = CNetworkCommuMgr::GetServerClientSocketMgr()->GetDataByServerClientSocket(m_sendrecvSocket);
		PrintfDebug("Net error, server: %s:%d[socket: %d, server client socket: %d], client: %s:%d",
			m_pTcpSrv->GetLocalIP(), m_pTcpSrv->GetLocalPort(), m_pTcpSrv->GetSocket(), m_sendrecvSocket, scData.ip, scData.port);
		m_pTcpSrv->OnNetError(scData.ip, scData.port);
	}
}