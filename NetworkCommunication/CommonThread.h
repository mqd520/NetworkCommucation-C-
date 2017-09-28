#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	//通用信号处理线程
	class CCommonThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadRun();

	public:
		CCommonThread();
		~CCommonThread();
	};
}