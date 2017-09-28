#pragma once

namespace NetworkCommunication
{
	class CThread;

	//线程入口类
	class CThreadEntry
	{
	protected:
		CThread* m_pThread;//线程对象

	protected:
		friend class CThread;
		//************************************
		// Method:    线程运行事件处理
		//************************************
		virtual void OnThreadRun();

	public:
		CThreadEntry();
		~CThreadEntry();

		//************************************
		// Method:    开始运行线程
		//************************************
		virtual void Run();
	};
}