#pragma once
#include "SocketMgr.h"

namespace NetworkCommunication
{
	class CTcpSession
	{
	protected:
		SOCKET m_serverSocket;//服务端socket
		SOCKET m_clientSocket;//客户端socket

	public:
		CTcpSession(SOCKET serverSocket, SOCKET clientSocket);
		~CTcpSession();
	};
}