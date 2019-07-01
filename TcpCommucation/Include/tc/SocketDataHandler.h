#pragma once
#include <queue>
#include "SocketEvt.h"

using namespace std;

namespace tc
{
	// socket数据处理类
	class SocketDataHandler
	{
	public:
		SocketDataHandler();
		virtual ~SocketDataHandler();

	protected:
		queue<SocketEvt*> quSocketEvts;	// socket事件集合

	protected:
		//************************************
		// Method:    socket事件处理
		//************************************
		virtual void OnSocketEvtProcess(SocketEvt* pEvt);

	public:
		//************************************
		// Method:    添加一个socket事件
		//************************************
		virtual void PushSocketEvt(SocketEvt* pEvt);

		//************************************
		// Method:    socket事件队列是否为空
		//************************************
		virtual bool IsEmpty();

		//************************************
		// Method:    清除socket事件队列
		//************************************
		virtual void Clear();

		//************************************
		// Method:    处理socket事件队列
		//************************************
		virtual void ProcessSocketEvt();
	};
}