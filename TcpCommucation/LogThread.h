#pragma once
#include "ThreadEntry.h"

namespace tc
{
	// 日志线程类
	class LogThread : public CThreadEntry
	{
	public:
		LogThread();
		~LogThread();

	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadExecute();

	public:
		void Run();
	};
}