#pragma once
#include "ThreadEntry.h"

namespace tc
{
	// 生成时间数据线程
	class TimeThread1 : public CThreadEntry
	{
	public:
		TimeThread1();
		~TimeThread1();

	private:
		int nTime;	//间隔时间

	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		virtual void OnThreadExecute() override;
	};
}