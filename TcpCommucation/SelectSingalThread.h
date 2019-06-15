#pragma once
#include "ThreadEntry.h"

namespace tc
{
	// select 信号处理线程
	class SelectSingalThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadExecute();

	public:
		SelectSingalThread();
		~SelectSingalThread();

		//************************************
		// Method:    开始运行线程
		//************************************
		void Run();
	};
}