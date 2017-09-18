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
		//************************************
		// Method:    ���캯��
		// Parameter: tcp�������
		// Parameter: �ͻ���socket
		// Parameter: �����socket
		//************************************
		CServerTcpConnection(CTcpService* pTcpSrv, SOCKET client, SOCKET server);
		~CServerTcpConnection();

		//��ȡ�����socket
		SOCKET GetServerSocket();

		//************************************
		// Method:    �յ��Զ������¼�����
		// Parameter: tcp�¼�
		//************************************
		void OnRecvPeerData(CRecvPeerDataAction* pAction);

		//************************************
		// Method:    tcp���ӶϿ��¼�����
		//************************************
		void OnTcpDisconnect(int reason);

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