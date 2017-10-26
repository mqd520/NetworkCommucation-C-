#pragma once
#include "TcpConnection.h"
#include "TcpService.h"

namespace NetworkCommunication
{
	//客户端tcp连接
	class CClientTcpConnection : public CTcpConnection
	{
	public:
		CClientTcpConnection(CTcpService* pSrv, SOCKET sendrecv);
		~CClientTcpConnection();
	};
}