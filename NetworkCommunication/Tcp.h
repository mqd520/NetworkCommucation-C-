#pragma once
#include "SocketAPI.h"
#include <queue>
#include "Thread.h"
#include "Def.h"
#include "TcpAction.h"
#include "RecvNewConnAction.h"
#include "RecvPeerDataAction.h"
#include "PeerCloseAction.h"
#include "SendPeerDataResultAction.h"
#include "NetErrorAction.h"
#include "AsyncSendDataAction.h"
#include "SocketExceptAction.h"

using namespace std;

namespace NetworkCommunication
{
	//tcp��,����tcp�����¼�
	class CTcp : public CThreadEntry
	{
	private:
		queue<CTcpAction*> m_queueTcpAction;//tcp��������
		CThread* m_thread;//�̶߳���
		CSocketAPI m_socketAPI;//socket api

	private:
		//************************************
		// Method:    ����tcp����
		//************************************
		void ProcessTcpAction();

		//************************************
		// Method:    �����յ������Ӷ���
		// Parameter: �յ������Ӷ���
		//************************************
		void ProcessRecvNewConnection(CRecvNewConnAction* pAction);

		//************************************
		// Method:    �����յ��Զ����ݶ���
		// Parameter: �յ��Զ����ݶ���
		//************************************
		void ProcessRecvPeerData(CRecvPeerDataAction* pAction);

		//************************************
		// Method:    ����Զ������ر����Ӷ���
		// Parameter: �Զ������ر����Ӷ���
		//************************************
		void ProcessPeerCloseConn(CPeerCloseAction* pAction);

		//************************************
		// Method:    �����첽�������ݶ���
		// Parameter: �첽�������ݶ���
		//************************************
		void ProcessAsyncSendData(CAsyncSendDataAction* pAction);

		//************************************
		// Method:    �����ͶԶ����ݽ������
		// Parameter: ���ͶԶ����ݽ������
		//************************************
		void ProcessSendPeerDataResult(CSendPeerDataResultAction* pAction);

		//************************************
		// Method:    �����������
		// Parameter: ���������
		//************************************
		void ProcessNetError(CNetErrorAction* pAction);

		//************************************
		// Method:    ����socket�쳣
		// Parameter: socket�쳣����
		//************************************
		void ProcessSocketExcept(CSocketExcept* pAction);

	public:
		CTcp();
		~CTcp();

		//************************************
		// Method:    �����߳�
		//************************************
		void Run();

		//************************************
		// Method:    �߳������¼�����
		//************************************
		void OnThreadRun();

		//************************************
		// Method:    ����һ��tcp����
		// Parameter: tcp����
		//************************************
		void PushTcpAction(CTcpAction* pAction);
	};
}
