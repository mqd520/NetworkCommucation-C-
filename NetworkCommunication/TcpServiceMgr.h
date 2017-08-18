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
		// Method:    ��ȡָ������socket��tcp�������
		// Return:	  tcp���Ӷ���
		// Parameter: ����socket
		//************************************
		CTcpService* GetTcpSrvByLocalSocket(SOCKET local);

		//************************************
		// Method:    �յ��������¼�����
		// Parameter: tcp����
		//************************************
		void OnRecvNewConnection(CRecvNewConnAction* pAction);

		//************************************
		// Method:    �յ��Զ������¼�����
		// Parameter: tcp����
		//************************************
		//void OnRecvPeerData(CRecvPeerDataAction* pAction);

		//************************************
		// Method:    �Զ������ر��¼�����
		// Parameter: tcp����
		//************************************
		void OnPeerClose(CPeerCloseAction* pAction);

		//************************************
		// Method:    ��Զ˷�����������¼�����
		// Parameter: tcp����
		//************************************
		void OnSendPeerDataCompleted(CSendPeerDataResultAction* pAction);
	};
}