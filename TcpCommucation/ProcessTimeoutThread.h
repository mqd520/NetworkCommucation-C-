#pragma once
#include "ThreadEntry.h"

namespace tc
{
	//处理超时数据线程
	class CProcessTimeoutThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadExecute();

	public:
		CProcessTimeoutThread();
		~CProcessTimeoutThread();
	};
}