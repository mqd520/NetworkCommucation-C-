#pragma once
#include "ThreadEntry.h"

namespace tc
{
	//发送数据线程
	class SendThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadExecute();

	public:
		SendThread();
		~SendThread();

		//************************************
		// Method:    开始运行线程
		//************************************
		void Run();
	};
}