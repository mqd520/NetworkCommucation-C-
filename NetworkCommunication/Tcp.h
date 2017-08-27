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
#include "RefuseNewConnAction.h"

using namespace std;

namespace NetworkCommunication
{
	//����tcp����
	class CTcp
	{
	private:
		queue<CTcpAction*> m_quTcpAction;//tcp��������
		CThread* m_threadAccept;//������socket���ӵ��߳�
		CSocketAPI m_socketAPI;//socket api

	private:
		//************************************
		// Method:    ����tcp��������
		//************************************
		void ProcessQueue();

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
		// Method:    ����ܾ��¿ͻ������Ӷ���
		// Parameter: �ܾ��¿ͻ������Ӷ���
		//************************************
		void ProcessRefuseNewConn(CRefuseNewConnAction* pAction);

	public:
		CTcp();
		~CTcp();

		//************************************
		// Method:    ���д����������߳�
		//************************************
		void Run();

		//************************************
		// Method:    accept�߳���ڵ�
		//************************************
		void ThreadEntry();

		//************************************
		// Method:    ����һ��tcp����
		// Parameter: tcp����
		//************************************
		void PushTcpAction(CTcpAction* pAction);
	};
}
