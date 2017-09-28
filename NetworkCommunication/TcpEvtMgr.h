#pragma once
#include <queue>
#include "TcpEvt.h"

using namespace std;

namespace NetworkCommunication
{
	//tcp事件管理对象
	class CTcpEvtMgr
	{
	private:
		queue<CTcpEvt*> m_queueEvent;//tcp事件队列

	public:
		CTcpEvtMgr();
		~CTcpEvtMgr();

		//************************************
		// Method:    tcp事件队列是否为空
		//************************************
		bool IsEmpty();

		//************************************
		// Method:    追加一个tcp服务事件
		// Parameter: tcp服务事件
		//************************************
		void PushTcpEvent(CTcpEvt* pEvent);

		//************************************
		// Method:    处理tcp事件
		//************************************
		void ProcessTcpEvt();
	};
}