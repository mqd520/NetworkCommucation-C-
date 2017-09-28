#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	//select线程
	class CSelectThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadRun();

	public:
		CSelectThread();
		~CSelectThread();
	};
}