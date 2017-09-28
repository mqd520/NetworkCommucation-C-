#pragma once
#include "TcpService.h"
#include <queue>
using namespace std;

namespace NetworkCommunication
{
	//tcp����������
	class CTcpServiceMgr
	{
	private:
		vector<CTcpService*> m_vecTcpService;//tcp������󼯺�

	public:
		CTcpServiceMgr();
		~CTcpServiceMgr();

		//************************************
		// Method:    ����һ��tcp�������
		// Parameter: tcp�������
		//************************************
		void PushTcpService(CTcpService* srv);

		//************************************
		// Method:    ��ȡָ��socket������tcp�������
		// Return:	  tcp�������
		// Parameter: socket
		//************************************
		CTcpService* GetTcpSrvBySocket(SOCKET socket);
	};
}