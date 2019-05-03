#include "stdafx.h"
#include "ClientTcpConnection.h"

namespace tc
{
	CClientTcpConnection::CClientTcpConnection(CTcpService* pSrv, SOCKET sendrecv) :
		CTcpConnection(pSrv, sendrecv)
	{

	}

	CClientTcpConnection::~CClientTcpConnection()
	{

	}
}