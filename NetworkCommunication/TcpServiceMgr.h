#pragma once
#include "TcpService.h"
#include "Def.h"
#include "AcceptNewConnAction.h"
#include "PeerCloseAction.h"
#include "RecvPeerDataAction.h"

#include <queue>
using namespace std;

namespace NetworkCommunication
{
	//tcp����������
	class CTcpServiceMgr
	{
	private:
		CThread* m_thread;
		vector<CTcpService*> m_vecTcpService;//tcp������󼯺�
		queue<CTcpAction*> m_tcpAction;//tcp��������

	private:
		~CTcpServiceMgr();

		//����tcp��������
		void ProcessTcpAction();

		//************************************
		// Method:    ������յ��¿ͻ������Ӷ���
		// Parameter: tcp����
		//************************************
		void ProcessAcceptNewConnAction(CAcceptNewConnAction* pAction);

		//************************************
		// Method:    ����Զ������رն���
		// Parameter: tcp����
		//************************************
		void ProcessPeerCloseAction(CPeerCloseAction* pAction);

		//************************************
		// Method:    �����յ��Զ�socket���ݶ���
		// Parameter: tcp����
		//************************************
		void ProcessRecvPeerDataAction(CRecvPeerDataAction* pAction);

	public:
		CTcpServiceMgr();
		
		//����һ��tcp�������
		void PushTcpService(CTcpService* srv);

		//����tcp�����߳�
		void Run();

		//�߳����
		void ThreadEntry();

		//************************************
		// Method:    ����һ��tcp����
		// Parameter: tcp����
		//************************************
		void PushTcpAction(CTcpAction* pAction);

		//�Ƿ��������˶���
		bool IsHasServer();
	};
}