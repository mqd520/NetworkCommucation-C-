#include "stdafx.h"
#include "ClientTcpConnection.h"

namespace tc
{
	CClientTcpConnection::CClientTcpConnection(TcpService* pSrv, SOCKET sendrecv) :
		CTcpConnection(pSrv, sendrecv)
	{

	}

	CClientTcpConnection::~CClientTcpConnection()
	{

	}
}