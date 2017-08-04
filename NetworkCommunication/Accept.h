#pragma once
#include "SocketMgr.h"
#include <queue>
#include "Thread.h"

using namespace std;

namespace NetworkCommunication
{
	//����socket������
	typedef struct tagSocketPair
	{
		SOCKET local;//����socket
		SOCKET peer;//�Զ�socket
	}SocketPair;

	class CAccept
	{
	private:
		queue<SocketPair> m_quSocket;//���յ����µ�socket���Ӷ���
		CThread* m_threadAccept;//������socket���ӵ��߳�
		CSocketMgr m_socMgr;

	private:
		//************************************
		// Method:    �������socket����
		//************************************
		void ProcessAcceptQueue();

	public:
		CAccept();
		~CAccept();

		//************************************
		// Method:    ���յ��µ�socket
		// Parameter: �µ�socket
		//************************************
		void OnRecvNewSocket(SOCKET socket);

		//************************************
		// Method:    ���д����������߳�
		//************************************
		void Run();

		//************************************
		// Method:    accept�߳���ڵ�
		//************************************
		void ThreadEntry();
	};
}
