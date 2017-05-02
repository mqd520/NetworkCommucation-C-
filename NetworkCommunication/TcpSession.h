#pragma once
#include "SocketMgr.h"

namespace NetworkCommunication
{
	class CTcpSession
	{
	protected:
		SOCKET m_serverSocket;//�����socket
		SOCKET m_clientSocket;//�ͻ���socket

	public:
		CTcpSession(SOCKET serverSocket, SOCKET clientSocket);
		~CTcpSession();
	};
}