#pragma once
#include "ThreadEntry.h"

namespace NetworkCommunication
{
	//接收数据线程
	class CRecvThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadExecute();

	public:
		CRecvThread();
		~CRecvThread();

		//************************************
		// Method:    开始运行线程
		//************************************
		void Run();
	};
}