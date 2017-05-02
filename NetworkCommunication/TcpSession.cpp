#include "stdafx.h"
#include "TcpSession.h"

namespace NetworkCommunication
{
	CTcpSession::CTcpSession(SOCKET serverSocket, SOCKET clientSocket) :
		m_serverSocket(serverSocket),
		m_clientSocket(clientSocket)
	{

	}

	CTcpSession::~CTcpSession()
	{

	}
}