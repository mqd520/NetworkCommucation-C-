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
		// Parameter: ����˵Ŀͻ���socket
		// Parameter: �����socket
		//************************************
		CServerTcpConnection(CTcpService* pTcpSrv, SOCKET scSocket, SOCKET server);
		~CServerTcpConnection();

		//��ȡ�����socket
		SOCKET GetServerSocket();

		//************************************
		// Method:    �յ��Զ������¼�����
		// Parameter: �Զ�����
		//************************************
		void OnRecvPeerData(PeerData* pData);

		//************************************
		// Method:    �Զ������ر�socket�¼�����
		//************************************
		void OnPeerCloseConn();

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