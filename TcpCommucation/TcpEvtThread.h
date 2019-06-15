#pragma once
#include "ThreadEntry.h"

namespace tc
{
	//tcp事件线程
	class TcpEvtThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadExecute();

	public:
		TcpEvtThread();
		~TcpEvtThread();

		//************************************
		// Method:    开始运行线程
		//************************************
		void Run();
	};
}