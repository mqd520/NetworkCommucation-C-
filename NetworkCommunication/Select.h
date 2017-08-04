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
		queue<SOCKET> m_quListenSocket;//服务端socket队列
		queue<SOCKET> m_quPeerSocket;//对端socket队列
		bool m_bExit;//指示线程是否应该结束
		CThread* m_threadSelect;
		bool m_bSleep;//select线程是否间隔sleep

	private:
		//************************************
		// Method:    开始查询socket状态
		//************************************
		void StartSelect();

	public:
		CSelect();
		~CSelect();

		//************************************
		// Method:    添加一个服务端监听socket
		// Parameter: socket
		//************************************
		void AddListenSocket(SOCKET socket);

		//************************************
		// Method:    添加一个对端socket(用于读写)
		// Parameter: socket
		//************************************
		void AddPeerSocket(SOCKET socket);

		//************************************
		// Method:    开启select线程
		//************************************
		void Run();

		//************************************
		// Method:    select线程入口点
		//************************************
		void ThreadEntry();
	};
}