#pragma once
#include "TcpConnection.h"

namespace NetworkCommunication
{
	//�����tcp���Ӷ���
	class CServerTcpConnection : public CTcpConnection
	{
	private:
		SOCKET m_serverSocket;//�����socket

	public:
		CServerTcpConnection(CTcpService* pTcpSrv, SOCKET sendrecv, SOCKET server);
		~CServerTcpConnection();

		//��ȡ�����socket
		SOCKET GetServerSocket();
	};
}