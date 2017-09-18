#pragma once
#include "SocketAPI.h"
#include "TcpService.h"
#include "SendPeerDataResultAction.h"
#include "RecvPeerDataAction.h"

using namespace std;

namespace NetworkCommunication
{
	//tcp����
	class CTcpConnection
	{
	protected:
		CSocketAPI m_socketAPI;//socket api
		CTcpService* m_pTcpSrv;//tcp�������
		SOCKET m_sendrecvSocket;//���ڷ���(����)���ݵ�socket

	public:
		//************************************
		// Method:    ���캯��
		// Parameter: tcp�������
		// Parameter: ���ڷ���(����)���ݵ�socket
		//************************************
		CTcpConnection(CTcpService* pSrv, SOCKET sendrecv);
		~CTcpConnection();

		//************************************
		// Method:    ��ȡ���ڷ���(����)���ݵ�socket
		// Returns:   socket
		//************************************
		SOCKET GetSendRecvSocket();

		//************************************
		// Method:    ��ȡ������tcp�������
		// Returns:   tcp�������
		//************************************
		CTcpService* GetTcpService();

		//************************************
		// Method:    ��������
		// Returns:   �Ƿ�ɹ�
		// Parameter: ������ָ��
		// Parameter: �������ֽڳ���
		// Parameter: ʵ�ʷ����ֽڳ���
		//************************************
		bool SendData(BYTE buf[], int len, int* actualLen = NULL);

		//************************************
		// Method:    �յ��Զ������¼�����
		// Parameter: tcp�¼�
		//************************************
		virtual void OnRecvPeerData(CRecvPeerDataAction* pAction);

		//************************************
		// Method:    tcp���ӶϿ��¼�����
		//************************************
		virtual void OnTcpDisconnect(int reason);

		//************************************
		// Method:    ���ͶԶ���������¼�����
		// Parameter: ���ͶԶ����ݽ��
		//************************************
		virtual void OnSendDataCompleted(SendPeerDataResult* pResult);

		//************************************
		// Method:    ��������¼�����
		//************************************
		virtual void OnNetError();
	};
}