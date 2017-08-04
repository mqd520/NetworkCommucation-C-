#pragma once
#include "SocketMgr.h"
#include <queue>
#include "Thread.h"

using namespace std;

namespace NetworkCommunication
{
	//关联socket对数据
	typedef struct tagSocketPair
	{
		SOCKET local;//本地socket
		SOCKET peer;//对端socket
	}SocketPair;

	class CAccept
	{
	private:
		queue<SocketPair> m_quSocket;//接收到的新的socket连接队列
		CThread* m_threadAccept;//处理新socket连接的线程
		CSocketMgr m_socMgr;

	private:
		//************************************
		// Method:    处理接收socket队列
		//************************************
		void ProcessAcceptQueue();

	public:
		CAccept();
		~CAccept();

		//************************************
		// Method:    接收到新的socket
		// Parameter: 新的socket
		//************************************
		void OnRecvNewSocket(SOCKET socket);

		//************************************
		// Method:    运行处理新连接线程
		//************************************
		void Run();

		//************************************
		// Method:    accept线程入口点
		//************************************
		void ThreadEntry();
	};
}
