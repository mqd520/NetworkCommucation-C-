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
		queue<SocketPair> m_quSocket;//接收到的新的socket连接队列
		CThread* m_threadAccept;//处理新socket连接的线程
		CSocketAPI m_socketAPI;

	private:
		//************************************
		// Method:    处理接收socket队列
		//************************************
		void ProcessAcceptQueue();

		bool FilterClientSocket(SocketPair pair);

	public:
		CAccept();
		~CAccept();

		//************************************
		// Method:    有新的客户端可接收
		// Parameter: 服务端socket
		//************************************
		void OnSocketCanRead(SOCKET server);

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
