#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	//发送数据线程
	class CSendThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadExecute();

	public:
		CSendThread();
		~CSendThread();

		//************************************
		// Method:    开始运行线程
		//************************************
		void Run();
	};
}