#pragma once
#include "ThreadEntry.h"

namespace tc
{
	// 处理超时数据线程
	class TimeThread2 : public CThreadEntry
	{
	public:
		TimeThread2();
		~TimeThread2();

	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		virtual void OnThreadExecute() override;
	};
}