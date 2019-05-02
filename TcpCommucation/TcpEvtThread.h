#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	//tcp事件线程
	class CTcpEvtThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadExecute();

	public:
		CTcpEvtThread();
		~CTcpEvtThread();

		//************************************
		// Method:    开始运行线程
		//************************************
		void Run();
	};
}