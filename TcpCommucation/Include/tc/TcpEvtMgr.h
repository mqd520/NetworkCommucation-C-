#pragma once
#include <queue>
#include "TcpEvt.h"

using namespace std;

namespace tc
{
	// tcp事件管理类
	class TcpEvtMgr
	{
	public:
		TcpEvtMgr();
		~TcpEvtMgr();

	private:
		queue<TcpEvt*> queueEvent;	// tcp事件队列

	public:
		//************************************
		// Method:    tcp事件队列是否为空
		//************************************
		bool IsEmpty();

		//************************************
		// Method:    追加一个tcp服务事件
		// Parameter: tcp服务事件
		//************************************
		void PushTcpEvent(TcpEvt* pEvent);

		//************************************
		// Method:    清除tcp事件队列
		//************************************
		void Clear();

		//************************************
		// Method:    处理tcp事件
		//************************************
		void ProcessTcpEvt();
	};
}