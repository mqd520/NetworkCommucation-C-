#include "stdafx.h"
#include "ServerTcpConnection.h"
#include "RecvNewConnAction.h"
#include "NetCommuMgr.h"

namespace NetworkCommunication
{
	CServerTcpConnection::CServerTcpConnection(CTcpService* pTcpSrv, SOCKET sendrecv, SOCKET server) :
		CTcpConnection(pTcpSrv, sendrecv),
		m_serverSocket(server)
	{
		CServerClientSocketMgr::Create(server, sendrecv);//����������һ���Զ�socket����
	}

	CServerTcpConnection::~CServerTcpConnection()
	{

	}

	SOCKET CServerTcpConnection::GetServerSocket()
	{
		return m_serverSocket;
	}
}