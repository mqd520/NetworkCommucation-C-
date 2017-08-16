#pragma once

#include "SocketAPI.h"
#include "TcpConnectionMgr.h"
#include "Thread.h"
#include "NetCommuMgr.h"
#include "Def.h"
#include "TcpServer.h"

namespace NetworkCommunication
{
	//tcp�����
	class CTcpServer : public CTcpService
	{
	protected:
		CSocketAPI m_socketMgr;//socket�������
		char m_strServerIP[20];//�����IP
		int m_nServerPort;//����˶˿�
		bool m_bInited;//�Ƿ��ѳ�ʼ��
		SOCKET m_serverSocket;
		bool m_bListening;//�Ƿ����ڼ���
		ServerSocketData m_socketData;//�����socket����

	public:
		CTcpServer();
		~CTcpServer();

		//************************************
		// Method:    ��ʼ��
		// Parameter: ip
		// Parameter: �˿�
		//************************************
		void Init(char* ip, int port);

		//************************************
		// Method:    ��ʼ����
		// Returns:   �Ƿ�ɹ�
		//************************************
		bool Listen();

		//************************************
		// Method:    ��ȡ�����socket����
		//************************************
		ServerSocketData GetServerSocketData();

		void OnRecvNewConnection(ServerSocketData server, PeerSocketData client);

		void SendData(SOCKET client, BYTE buf[], int len);
	};
}