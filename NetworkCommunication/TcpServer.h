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
		vector<char*> m_vecAllowIP;//����Ŀͻ���IP

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
		// Method:    ����һ������IP
		// Parameter: ip
		//************************************
		void AddAllowIP(char* ip);

		//************************************
		// Method:    �Ƴ�ָ��������IP
		// Parameter: ip
		//************************************
		void RemoveAllowIP(char* ip);

		//************************************
		// Method:    �����������IP,��ʾ��������IP
		//************************************
		void ClearAllowIP();

		//************************************
		// Method:    ָ��IP�Ƿ�����
		// Parameter: ip
		//************************************
		bool IsAllow(char* ip);

		//************************************
		// Method:    ��ʼ����
		// Returns:   �Ƿ�ɹ�
		//************************************
		bool Listen();

		//************************************
		// Method:    ��ȡ�����socket����
		//************************************
		ServerSocket GetServerSocketData();
	};
}