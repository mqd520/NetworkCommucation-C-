#pragma once

#define SLEEPTIME	5	// 线程默认休眠时间

namespace tc
{


	class CThread;

	//线程入口类
	class CThreadEntry
	{
	protected:
		CThread* m_pThread;//线程对象
		volatile bool m_bExist;//线程是否应该退出
		bool m_bRun;//线程是否已开启
		int m_nSleepMillSecond;//休眠时间

	protected:
		//************************************
		// Method:    设置休眠时间
		//************************************
		void SetSleepTime(int millsecond = SLEEPTIME);

	protected:
		friend class CThread;
		//************************************
		// Method:    线程执行事件处理
		// Returns:   是否应该退出
		// Qualifier:
		//************************************
		virtual void OnThreadExecute();

		//************************************
		// Method:    线程执行完毕事件处理
		//************************************
		virtual void OnThreadCmp();

		//************************************
		// Method:    线程是否可以退出
		//************************************
		bool IsCanExit();

		//************************************
		// Method:    执行一次业务代码后休眠
		//************************************
		virtual void Sleep();

	public:
		CThreadEntry();
		~CThreadEntry();

		//************************************
		// Method:    开始运行线程
		//************************************
		virtual void Run();

		//************************************
		// Method:    退出线程
		//************************************
		virtual void Exit();
	};
}