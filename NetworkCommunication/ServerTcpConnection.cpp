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
#ifdef _DEBUG
		PrintfDebug(_T("[%s:%d][socket: %d] recved [%s:%d] data, size: %d, client socket: %d"),
			m_pTcpSrv->GetLocalIP(), m_pTcpSrv->GetLocalPort(), m_pTcpSrv->GetSocket(), pData->ip, pData->port, pData->len, m_sendrecvSocket);
#endif // _DEBUG

		__super::OnRecvPeerData(pData);
	}

	void CServerTcpConnection::OnPeerCloseConn()
	{
		__super::OnPeerCloseConn();

		TCHAR ip[20];
		int port = 0;
		m_socketAPI.GetPeerIpAndPort(m_sendrecvSocket, ip, &port);

#ifdef _DEBUG
		PrintfDebug(_T("client [%s:%d] closed the connection, server: [%s:%d][socket: %d], client socket: %d"),
			ip, port, m_pTcpSrv->GetLocalIP(), m_pTcpSrv->GetLocalPort(), m_pTcpSrv->GetSocket(), m_sendrecvSocket);
#endif // _DEBUG

		m_pTcpSrv->OnPeerCloseConn(ip, port);
	}

	void CServerTcpConnection::OnSendDataCompleted(SendPeerDataResult* pResult)
	{
		__super::OnSendDataCompleted(pResult);

		TCHAR ip[20];
		int port = 0;
		m_socketAPI.GetPeerIpAndPort(m_sendrecvSocket, ip, &port);

		_tcscpy(pResult->ip, ip);
		pResult->port = port;

#ifdef _DEBUG
		if (pResult->success)
		{
			PrintfDebug(_T("[%s:%d][socket: %d] send data to [%s:%d] successed, size: %d, client socket: %d"),
				m_pTcpSrv->GetLocalIP(), m_pTcpSrv->GetLocalPort(), m_pTcpSrv->GetSocket(), ip, port, pResult->len, m_sendrecvSocket);
		}
		else
		{
			PrintfDebug(_T("[%s:%d][socket: %d] send data to [%s:%d] failed, size: %d, actual size: %d"),
				m_pTcpSrv->GetLocalIP(), m_pTcpSrv->GetLocalPort(), m_pTcpSrv->GetSocket(), ip, port, m_sendrecvSocket, pResult->len, pResult->actualLen);
		}
#endif // _DEBUG

		m_pTcpSrv->OnSendPeerDataCompleted(pResult);
	}

	void CServerTcpConnection::OnNetError()
	{
		__super::OnNetError();

		TCHAR ip[20];
		int port = 0;
		m_socketAPI.GetPeerIpAndPort(m_sendrecvSocket, ip, &port);

#ifdef _DEBUG
		PrintfDebug(_T("Net error, server: %s:%d[socket: %d, server client socket: %d], client: %s:%d"),
			m_pTcpSrv->GetLocalIP(), m_pTcpSrv->GetLocalPort(), m_pTcpSrv->GetSocket(), m_sendrecvSocket, ip, port);
#endif // _DEBUG

		m_pTcpSrv->OnNetError(ip, port);
	}
}