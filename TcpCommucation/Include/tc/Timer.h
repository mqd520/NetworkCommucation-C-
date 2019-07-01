#pragma once
#include <functional>
using namespace std;
using namespace std::placeholders;

namespace tc
{
	class Timer;
	class TimerMgr;

	// 定时器回调函数指针
	typedef std::function<void(Timer*, int, void*, void*)> Fun3;

	// 定时器
	class Timer
	{
	public:
		Timer(int timeout = 1000, int count = 0);
		~Timer();

	private:
		int nTimeout;			// 间隔时长(毫秒)
		int nCount;				// 运行次数,0:无限运行
		Fun3 fun;				// 定时器回调函数指针
		void* pParam1;			// 回调函数附加参数1
		void* pParam2;			// 回调函数附加参数2
		bool bRunning;			// 是否正在运行
		int nTimeouted;			// 已经间隔的时长
		int nCounted;			// 已经运行的次数
		bool bInited;			// 是否已初始化

	private:
		friend class TimerMgr;
		void OnTimer(int millsecond);

		void Init();

	public:
		//************************************
		// Method:    设置间隔时间(ms)
		//************************************
		void SetTimeout(int millsecond);

		//************************************
		// Method:    设置回调函数
		//************************************
		void SetCallback(Fun3 fun, void* pParam1 = NULL, void* pParam2 = NULL);

		//************************************
		// Method:    开始运行定时器
		//************************************
		void Run();

		//************************************
		// Method:    停止计时(清除所有数据)
		//************************************
		void Stop();

		//************************************
		// Method:    暂停计时
		//************************************
		void Pause();

		//************************************
		// Method:    恢复计时
		//************************************
		void Resume();

		//************************************
		// Method:    重置时间
		//************************************
		void Reset();

		//************************************
		// Method:    是否在运行
		//************************************
		bool IsRun();

		//************************************
		// Method:    获取运行次数
		//************************************
		int Count();
	};
}