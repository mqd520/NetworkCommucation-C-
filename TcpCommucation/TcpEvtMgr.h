#pragma once
#include <queue>
#include "Include/tc/TcpEvt.h"

using namespace std;

namespace tc
{
	// tcp事件管理类
	class TcpEvtMgr
	{
	private:
		queue<TcpEvt*> queueEvent;	// tcp事件队列

	public:
		TcpEvtMgr();
		~TcpEvtMgr();

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
		// Method:    处理tcp事件
		//************************************
		void ProcessTcpEvt();
	};
}