#pragma once
#include "ThreadEntry.h"

namespace tc
{
	//select线程
	class CSelectThread : public CThreadEntry
	{
	protected:
		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadExecute();

	public:
		CSelectThread();
		~CSelectThread();

		//************************************
		// Method:    开始运行线程
		//************************************
		void Run();
	};
}