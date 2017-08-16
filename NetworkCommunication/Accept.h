#pragma once
#include "SocketAPI.h"
#include <queue>
#include "Thread.h"
#include "Def.h"

using namespace std;

namespace NetworkCommunication
{
	class CAccept
	{
	private:
		queue<SocketPair> m_quSocket;//���յ����µ�socket���Ӷ���
		CThread* m_threadAccept;//������socket���ӵ��߳�
		CSocketAPI m_socketAPI;

	private:
		//************************************
		// Method:    �������socket����
		//************************************
		void ProcessAcceptQueue();

		bool FilterClientSocket(SocketPair pair);

	public:
		CAccept();
		~CAccept();

		//************************************
		// Method:    ���µĿͻ��˿ɽ���
		// Parameter: �����socket
		//************************************
		void OnSocketCanRead(SOCKET server);

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
