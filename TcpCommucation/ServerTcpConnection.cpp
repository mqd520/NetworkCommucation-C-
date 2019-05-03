#include "stdafx.h"
#include "ServerTcpConnection.h"
#include "NetCommuMgr.h"
#include "Common.h"
#include "Def.h"

namespace tc
{
	CServerTcpConnection::CServerTcpConnection(CTcpService* pTcpSrv, SOCKET client, SOCKET server) :
		CTcpConnection(pTcpSrv, client),
		m_serverSocket(server)
	{
		memset(m_localAddress.ip, 0, NETCOMM_MAXIPSTRELN);
		memset(m_peerAddress.ip, 0, NETCOMM_MAXIPSTRELN);
		m_socketAPI.GetPeerIpAndPort(client, m_peerAddress.ip, &m_peerAddress.port);
		if (pTcpSrv)
		{
			_tcscpy(m_localAddress.ip, pTcpSrv->GetServerIP());
			m_localAddress.port = pTcpSrv->GetServerPort();
		}
	}

	CServerTcpConnection::~CServerTcpConnection()
	{

	}

	SOCKET CServerTcpConnection::GetServerSocket()
	{
		return m_serverSocket;
	}

	void CServerTcpConnection::OnRecvPeerData()
	{
		__super::OnRecvPeerData();
	}

	void CServerTcpConnection::OnConnDisconnect()
	{
		__super::OnConnDisconnect();
	}

	void CServerTcpConnection::OnSendDataCompleted(SendPeerDataResult* pResult)
	{
		//__super::OnSendDataCompleted(pResult);

		TCHAR ip[NETCOMM_MAXIPSTRELN];
		int port = 0;
		m_socketAPI.GetPeerIpAndPort(m_sendrecvSocket, ip, &port);

		_tcscpy(pResult->ip, ip);
		pResult->port = port;

#ifdef _DEBUG
		if (pResult->success)
		{
			PrintfDebug(_T("[%s:%d][socket: %d] send data to [%s:%d] successed, size: %d, client socket: %d"),
				m_pTcpSrv->GetServerIP(), m_pTcpSrv->GetServerPort(), m_pTcpSrv->GetSocket(), ip, port, pResult->len, m_sendrecvSocket);
		}
		else
		{
			PrintfDebug(_T("[%s:%d][socket: %d] send data to [%s:%d] failed, size: %d, actual size: %d"),
				m_pTcpSrv->GetServerIP(), m_pTcpSrv->GetServerPort(), m_pTcpSrv->GetSocket(), ip, port, m_sendrecvSocket, pResult->len, pResult->actualLen);
		}
#endif // _DEBUG

		//m_pTcpSrv->OnSendPeerDataCompleted(pResult);
	}

	void CServerTcpConnection::OnNetError()
	{
		__super::OnNetError();

		TCHAR ip[NETCOMM_MAXIPSTRELN];
		int port = 0;
		m_socketAPI.GetPeerIpAndPort(m_sendrecvSocket, ip, &port);

#ifdef _DEBUG
		PrintfDebug(_T("Net error, server: %s:%d[socket: %d, server client socket: %d], client: %s:%d"),
			m_pTcpSrv->GetServerIP(), m_pTcpSrv->GetServerPort(), m_pTcpSrv->GetSocket(), m_sendrecvSocket, ip, port);
#endif // _DEBUG

		//m_pTcpSrv->OnNetError(ip, port);
	}
}