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
		void OnThreadRun();

	public:
		CSendThread();
		~CSendThread();
	};
}