#include "stdafx.h"
#include "ClientTcpConnection.h"

namespace NetworkCommunication
{
	CClientTcpConnection::CClientTcpConnection(CTcpService* pSrv, SOCKET sendrecv) :
		CTcpConnection(pSrv, sendrecv)
	{

	}

	CClientTcpConnection::~CClientTcpConnection()
	{

	}
}