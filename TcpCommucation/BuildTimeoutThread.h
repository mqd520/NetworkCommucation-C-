#pragma once
#include "ThreadEntry.h"

namespace tc
{
	//生成超时数据线程
	class CBuildTimeoutThread : public CThreadEntry
	{
	private:
		int m_nTimespan;//间隔时间

	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadExecute();

	public:
		CBuildTimeoutThread();
		~CBuildTimeoutThread();
	};
}