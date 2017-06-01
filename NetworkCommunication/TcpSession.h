#pragma once
#include "SocketMgr.h"

namespace NetworkCommunication
{
	class CTcpSession
	{
	protected:
		SOCKET m_serverSocket;//服务端socket
		SOCKET m_clientSocket;//客户端socket
		BYTE* m_pBuf;//
		int m_nBufLen;

	public:
		CTcpSession(SOCKET serverSocket, SOCKET clientSocket);
		~CTcpSession();

		SOCKET GetClientSocket();

		void StartRecvData();
	};
}