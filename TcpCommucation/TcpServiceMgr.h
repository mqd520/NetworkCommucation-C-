#pragma once
#include "TcpService.h"
#include <queue>
using namespace std;

namespace tc
{
	//tcp����������
	class CTcpServiceMgr
	{
	private:
		vector<TcpService*> m_vecTcpService;//tcp������󼯺�

	public:
		CTcpServiceMgr();
		~CTcpServiceMgr();

		//************************************
		// Method:    ����һ��tcp�������
		// Parameter: tcp�������
		//************************************
		void PushTcpService(TcpService* srv);

		//************************************
		// Method:    ��ȡָ��socket������tcp�������
		// Return:	  tcp�������
		// Parameter: socket
		//************************************
		TcpService* GetTcpSrvBySocket(SOCKET socket);
	};
}