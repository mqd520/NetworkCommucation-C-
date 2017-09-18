#pragma once
#include "TcpService.h"
#include "Def.h"
#include "TcpSrvEvt.h"

#include <queue>
using namespace std;

namespace NetworkCommunication
{
	//tcp����������
	class CTcpServiceMgr : public CThreadEntry
	{
	private:
		CThread* m_thread;//�̶߳���
		queue<CTcpSrvEvt*> m_queueEvent;//tcp�¼�����
		vector<CTcpService*> m_vecTcpService;//tcp������󼯺�

	private:
		//************************************
		// Method:    ������յ���tcp�¼�
		//************************************
		void ProcessTcpEvent();

	public:
		CTcpServiceMgr();
		~CTcpServiceMgr();

		//************************************
		// Method:    �����߳�
		//************************************
		void Run();

		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadRun();

		//����һ��tcp�������
		void PushTcpService(CTcpService* srv);

		//************************************
		// Method:    ׷��һ��tcp�����¼�
		// Parameter: tcp�����¼�
		//************************************
		void PushTcpEvent(CTcpSrvEvt* pEvent);

		//************************************
		// Method:    ��ȡָ��socket������tcp�������
		// Return:	  tcp�������
		// Parameter: socket
		//************************************
		CTcpService* GetTcpSrvBySocket(SOCKET socket);
	};
}