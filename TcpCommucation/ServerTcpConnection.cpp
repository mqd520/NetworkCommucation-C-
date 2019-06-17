#include "stdafx.h"
#include "ServerTcpConnection.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Common.h"
#include "Def.h"

namespace tc
{
	CServerTcpConnection::CServerTcpConnection(TcpServer* pTcpSrv, SOCKET client) :
		CTcpConnection(pTcpSrv, client)
	{
		m_localAddress.ip = "";
		m_peerAddress.ip = SocketTool::GetPeerIpAndPort(client, &m_peerAddress.port);
		if (pTcpSrv)
		{
			//_tcscpy(m_localAddress.ip, pTcpSrv->GetSelfIP());
			//m_localAddress.port = pTcpSrv->GetSelfPort();
		}
	}

	CServerTcpConnection::~CServerTcpConnection()
	{

	}

	SOCKET CServerTcpConnection::GetServerSocket()
	{
		return m_pTcpSrv->GetSocket();
	}

	void CServerTcpConnection::OnRecvPeerData()
	{
		__super::OnRecvPeerData();
	}

	void CServerTcpConnection::OnConnDisconnect()
	{
		__super::OnConnDisconnect(EDisconnReason::Peer);
	}

	void CServerTcpConnection::OnSendDataCompleted(SendPeerDataResult* pResult)
	{
		//__super::OnSendDataCompleted(pResult);

//		TCHAR ip[TC_MAXIPSTRELN];
//		int port = 0;
//		m_socketAPI.GetPeerIpAndPort(m_sendrecvSocket, ip, &port);
//
//		_tcscpy(pResult->ip, ip);
//		pResult->port = port;
//
//#ifdef _DEBUG
//		if (pResult->success)
//		{
//			PrintfDebug(_T("[%s:%d][socket: %d] send data to [%s:%d] successed, size: %d, client socket: %d"),
//				m_pTcpSrv->GetIP(), m_pTcpSrv->GetPort(), m_pTcpSrv->GetSocket(), ip, port, pResult->len, m_sendrecvSocket);
//		}
//		else
//		{
//			PrintfDebug(_T("[%s:%d][socket: %d] send data to [%s:%d] failed, size: %d, actual size: %d"),
//				m_pTcpSrv->GetIP(), m_pTcpSrv->GetPort(), m_pTcpSrv->GetSocket(), ip, port, m_sendrecvSocket, pResult->len, pResult->actualLen);
//		}
//#endif // _DEBUG
//
//		//m_pTcpSrv->OnSendPeerDataCompleted(pResult);
	}

	void CServerTcpConnection::OnNetError()
	{
//		__super::OnNetError();
//
//		TCHAR ip[TC_MAXIPSTRELN];
//		int port = 0;
//		m_socketAPI.GetPeerIpAndPort(m_sendrecvSocket, ip, &port);
//
//#ifdef _DEBUG
//		PrintfDebug(_T("Net error, server: %s:%d[socket: %d, server client socket: %d], client: %s:%d"),
//			m_pTcpSrv->GetIP(), m_pTcpSrv->GetPort(), m_pTcpSrv->GetSocket(), m_sendrecvSocket, ip, port);
//#endif // _DEBUG
//
//		//m_pTcpSrv->OnNetError(ip, port);
	}
}