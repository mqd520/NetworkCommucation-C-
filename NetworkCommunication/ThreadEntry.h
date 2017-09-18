#pragma once

namespace NetworkCommunication
{
	//线程入口类
	class CThreadEntry
	{
	public:
		CThreadEntry();
		~CThreadEntry();

		//************************************
		// Method:    线程运行事件处理
		//************************************
		virtual void OnThreadRun();
	};
}