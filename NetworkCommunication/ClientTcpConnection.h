#pragma once
#include "TcpConnection.h"
#include "TcpService.h"

namespace NetworkCommunication
{
	//�ͻ���tcp����
	class CClientTcpConnection : public CTcpConnection
	{
	public:
		CClientTcpConnection(CTcpService* pSrv, SOCKET sendrecv);
		~CClientTcpConnection();
	};
}