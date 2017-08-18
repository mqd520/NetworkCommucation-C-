#pragma once
#include "TcpConnection.h"

namespace NetworkCommunication
{
	//服务端tcp连接对象
	class CServerTcpConnection : public CTcpConnection
	{
	private:
		SOCKET m_serverSocket;//服务端socket

	public:
		CServerTcpConnection(CTcpService* pTcpSrv, SOCKET sendrecv, SOCKET server);
		~CServerTcpConnection();

		//获取服务端socket
		SOCKET GetServerSocket();
	};
}