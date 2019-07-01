#pragma once
#include "TimeThread1.h"
#include "TimeThread2.h"
#include "TimeMgr.h"
#include "TimerMgr.h"

namespace tc
{
	// 定时器模块管理
	class TimerMoudleMgr
	{
	public:
		TimerMoudleMgr();
		~TimerMoudleMgr();

	private:
		static bool bInited;			// 是否已初始化
		static int nTimeUnit;			// 时间最小单位
		static TimeThread2 timeThread1;	// 处理超时线程
		static TimeThread1 timeThread2;	// 生成超时线程
		static TimeMgr timeMgr;			// 定时器管理
		static TimerMgr timerMgr;		// 超时管理

	public:
		//************************************
		// Method:    初始化
		//************************************
		static void Init();

		//************************************
		// Method:    退出
		//************************************
		static void Exit();

		//************************************
		// Method:    获取超时单位时间
		//************************************
		static int GetTimeUnit();

		//************************************
		// Method:    设置超时单位时间
		// Parameter: 超时时间
		//************************************
		static void SetTimeUnit(int millsecond);

		//************************************
		// Method:    获取定时器管理对象
		//************************************
		static TimerMgr* GetTimerMgr();

		//************************************
		// Method:    获取时间管理对象
		//************************************
		static TimeMgr* GetTimeMgr();
	};
}