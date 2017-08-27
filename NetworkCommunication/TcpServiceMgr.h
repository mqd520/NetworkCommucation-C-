#pragma once
#include "TcpService.h"
#include "Def.h"
#include "RecvNewConnAction.h"
#include "PeerCloseAction.h"
#include "RecvPeerDataAction.h"
#include "SendPeerDataResultAction.h"

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

		//����һ��tcp�������
		void PushTcpService(CTcpService* srv);

		//************************************
		// Method:    ��ȡָ��socket������tcp�������
		// Return:	  tcp�������
		// Parameter: socket
		//************************************
		CTcpService* GetTcpSrvBySocket(SOCKET socket);
	};
}