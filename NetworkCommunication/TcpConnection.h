#pragma once
#include "SocketAPI.h"
#include "TcpService.h"

using namespace std;

namespace NetworkCommunication
{
	//tcp�Ự
	class CTcpConnection
	{
	private:
		CSocketAPI m_socketAPI;
		SOCKET m_peerSocket;//�Զ�socket
		SOCKET m_localSocket;//����socket
		CTcpService* m_pTcpSrv;//tcp�������

	private:
		//��ȡ���Է������ݵ�socket
		SOCKET GetSendSocket();

	public:
		CTcpConnection(SOCKET localSocket, SOCKET peerSocket = NULL, CTcpService* pSrv = NULL);
		~CTcpConnection();

		// ��������socket
		SOCKET GetLocalSocket();

		//��ȡ�Զ�socket
		SOCKET GetPeerSocket();

		//************************************
		// Method:    ��������(ͬ��)
		// Returns:   �Ƿ�ɹ�
		// Parameter: ������ָ��
		// Parameter: �������ֽڳ���
		// Parameter: ʵ�ʷ��ͳ���
		//************************************
		bool SendData(BYTE buf[], int len, int* actualLen = NULL);

		//************************************
		// Method:    ���յ��Զ������¼�����
		// Parameter: socket��������
		//************************************
		void OnRecvPeerData(SocketRecvData data);

		//************************************
		// Method:    �Զ˹ر��¼�����
		// Parameter: �Զ�socket
		//************************************
		void OnPeerClose(SOCKET peer);
	};
}