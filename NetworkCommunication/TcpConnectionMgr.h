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
		vector<CTcpConnection*> m_vecConnectionList;//tcp连接集合
		CThread* m_threadRW;//读写线程
		queue<SOCKET> m_quSocket;//读写socket队列

	public:
		CTcpConnectionMgr();
		~CTcpConnectionMgr();

		void Push(CTcpConnection* session);

		//************************************
		// Method:    socket有数据可读
		// Parameter: SOCKET socket
		//************************************
		void OnSocketRead(SOCKET socket);

		void ThreadEntry();

		void Run();
	};
}