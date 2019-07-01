#pragma once
#include "ThreadEntry.h"

namespace tc
{
	//接收数据线程
	class RecvThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadExecute();

	public:
		RecvThread();
		~RecvThread();

		//************************************
		// Method:    开始运行线程
		//************************************
		void Run();
	};
}