#pragma once
#include "BuildTimeoutThread.h"
#include "ProcessTimeoutThread.h"
#include "TimeoutMgr.h"
#include "TimerMgr.h"

namespace NetworkCommunication
{
	//定时器应用管理
	class CTimerAppMgr
	{
	private:
		static bool m_bExit;//是否需要退出
		static int m_nTimeoutUnit;//超时单位
		static CProcessTimeoutThread m_processTimeoutThread;//处理超时线程
		static CBuildTimeoutThread m_buildTimeoutThread;//生成超时线程
		static CTimerMgr m_timerMgr;//定时器管理
		static CTimeoutMgr m_timeoutMgr;//超时管理

	public:
		CTimerAppMgr();
		~CTimerAppMgr();

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
		static int GetTimeoutUnit();

		//************************************
		// Method:    设置超时单位时间
		// Parameter: 超时时间
		//************************************
		static void SetTimeoutUnit(int millsecond);

		//************************************
		// Method:    获取用户是否指示需要退出
		//************************************
		static bool CanExit();

		//************************************
		// Method:    获取定时器管理
		//************************************
		static CTimerMgr* GetTimerMgr();

		//************************************
		// Method:    获取超时管理
		//************************************
		static CTimeoutMgr* GetTimeoutMgr();
	};
}