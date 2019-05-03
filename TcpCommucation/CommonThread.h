#pragma once
#include "ThreadEntry.h"

namespace tc
{
	//通用信号处理线程
	class CCommonThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadExecute();

	public:
		CCommonThread();
		~CCommonThread();

		//************************************
		// Method:    开始运行线程
		//************************************
		void Run();
	};
}