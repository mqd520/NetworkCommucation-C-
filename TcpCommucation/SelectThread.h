#pragma once
#include "ThreadEntry.h"

namespace tc
{
	//select线程
	class SelectThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadExecute();

	public:
		SelectThread();
		~SelectThread();

		//************************************
		// Method:    开始运行线程
		//************************************
		void Run();
	};
}