#pragma once
#include "TcpService.h"
#include <queue>
using namespace std;

namespace tc
{
	// tcp������������
	class TcpServiceMgr
	{
	private:
		vector<TcpService*> vecTcpService;	// tcp������󼯺�

	public:
		TcpServiceMgr();
		~TcpServiceMgr();

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