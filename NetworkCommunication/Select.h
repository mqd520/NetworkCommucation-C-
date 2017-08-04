#pragma once
#include <queue>
#include "SocketMgr.h"
#include "Thread.h"

using namespace std;

namespace NetworkCommunication
{
	class CSelect
	{
	private:
		CSocketMgr m_socMgr;
		queue<SOCKET> m_quListenSocket;//�����socket����
		queue<SOCKET> m_quPeerSocket;//�Զ�socket����
		bool m_bExit;//ָʾ�߳��Ƿ�Ӧ�ý���
		CThread* m_threadSelect;
		bool m_bSleep;//select�߳��Ƿ���sleep

	private:
		//************************************
		// Method:    ��ʼ��ѯsocket״̬
		//************************************
		void StartSelect();

	public:
		CSelect();
		~CSelect();

		//************************************
		// Method:    ���һ������˼���socket
		// Parameter: socket
		//************************************
		void AddListenSocket(SOCKET socket);

		//************************************
		// Method:    ���һ���Զ�socket(���ڶ�д)
		// Parameter: socket
		//************************************
		void AddPeerSocket(SOCKET socket);

		//************************************
		// Method:    ����select�߳�
		//************************************
		void Run();

		//************************************
		// Method:    select�߳���ڵ�
		//************************************
		void ThreadEntry();
	};
}