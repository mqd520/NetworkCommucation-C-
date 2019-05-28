#pragma once
#include "TcpConnection.h"

namespace tc
{
	//�����tcp���Ӷ���
	class CServerTcpConnection : public CTcpConnection
	{
	private:
		SOCKET m_serverSocket;//�����socket

	public:
		//************************************
		// Method:    ���캯��
		// Parameter: tcp�������
		// Parameter: �ͻ���socket
		// Parameter: �����socket
		//************************************
		CServerTcpConnection(TcpService* pTcpSrv, SOCKET client, SOCKET server);
		~CServerTcpConnection();

		//��ȡ�����socket
		SOCKET GetServerSocket();

		//************************************
		// Method:    �յ��Զ������¼�����
		//************************************
		void OnRecvPeerData();

		//************************************
		// Method:    ���ӶϿ��¼�����
		//************************************
		void OnConnDisconnect();

		//************************************
		// Method:    ���ͶԶ���������¼�����
		// Parameter: ���ͶԶ����ݽ��
		//************************************
		void OnSendDataCompleted(SendPeerDataResult* pResult);

		//************************************
		// Method:    ��������¼�����
		//************************************
		void OnNetError();
	};
}