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
		CSocketAPI m_socketAPI;//socket�������
		bool m_bListening;//�Ƿ����ڼ���
		ServerSocket m_socketData;//�����socket����

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
		ServerSocket GetServerSocketData();

		void OnRecvNewConnection(ServerSocket server, ServerClientSocket client);
	};
}