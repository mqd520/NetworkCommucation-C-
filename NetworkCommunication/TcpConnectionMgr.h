#pragma once

#include <vector>
#include "TcpConnection.h"
#include "Thread.h"
#include <queue>

using namespace std;

#ifndef MAXTCPSESSION
#define MAXTCPSESSION	65535
#endif // !MAXTCPSESSION

namespace NetworkCommunication
{
	class CTcpConnectionMgr
	{
	private:
		CSocketMgr m_socMgr;
		vector<CTcpConnection*> m_vecConnectionList;//tcp���Ӽ���
		CThread* m_threadRW;//��д�߳�
		queue<SOCKET> m_quSocket;//��дsocket����

	public:
		CTcpConnectionMgr();
		~CTcpConnectionMgr();

		void Push(CTcpConnection* session);

		//************************************
		// Method:    socket�����ݿɶ�
		// Parameter: SOCKET socket
		//************************************
		void OnSocketRead(SOCKET socket);

		void ThreadEntry();

		void Run();
	};
}