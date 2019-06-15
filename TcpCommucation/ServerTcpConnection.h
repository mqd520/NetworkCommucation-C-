#pragma once
#include "TcpConnection.h"
#include "Include/tc/TcpServer.h"

namespace tc
{
	// �����tcp���Ӷ���
	class CServerTcpConnection : public CTcpConnection
	{
	public:
		//************************************
		// Method:    ���캯��
		// Parameter: tcp�������
		// Parameter: �շ����ݹ�����socket
		//************************************
		CServerTcpConnection(TcpServer* pTcpSrv, SOCKET sendrecv);
		~CServerTcpConnection();

	public:
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