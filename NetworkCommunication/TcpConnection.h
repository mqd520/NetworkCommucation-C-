#pragma once
#include "SocketAPI.h"
#include "TcpService.h"

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
		// Method:    ���յ��Զ������¼�����
		// Parameter: �Զ�����
		//************************************
		void OnRecvPeerData(PeerData* data);

		//************************************
		// Method:    �Զ������ر�socket�¼�����
		// Parameter: �������ı���socket
		//************************************
		void OnPeerCloseSocket(SOCKET socket);

		//************************************
		// Method:    ��������(ͬ��)
		// Returns:   �Ƿ�ɹ�
		// Parameter: ������ָ��
		// Parameter: �������ֽڳ���
		// Parameter: ʵ�ʷ����ֽڳ���
		//************************************
		bool SendData(BYTE buf[], int len, int* actualLen = NULL);
	};
}