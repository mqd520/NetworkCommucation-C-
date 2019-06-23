#pragma once
#include <queue>
#include "SocketEvt.h"

using namespace std;

namespace tc
{
	// 收数据处理器类
	class RecvDataHandler
	{
	public:
		RecvDataHandler();
		~RecvDataHandler();

	private:
		queue<SocketEvt*> quSocketEvts;	// socket事件集合

	private:
		//************************************
		// Method:    收到新连接事件处理
		//************************************
		void OnRecvNewConn(SocketEvt* pEvt);

		//************************************
		// Method:    收到对端数据事件处理
		//************************************
		void OnRecvPeerData(SocketEvt* pEvt);

		//************************************
		// Method:    连接断开事件处理
		//************************************
		void OnConnDisconnect(SocketEvt* pEvt);

	public:
		void PushSocketEvt(SocketEvt* pEvt);

		//************************************
		// Method:    socket事件队列是否为空
		//************************************
		bool IsEmpty();

		//************************************
		// Method:    清除socket事件队列
		//************************************
		void Clear();

		//************************************
		// Method:    处理socket事件队列
		//************************************
		void ProcessSocketEvt();
	};
}