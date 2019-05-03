#pragma once

namespace tc
{
	class CTimer;

	typedef void(*LPTimeoutCallback)(CTimer* pTimeout, int count);

	class CTimerMgr;

	//定时器
	class CTimer
	{
	private:
		int m_nTimeout;//间隔时长(毫秒)
		int m_nCount;//运行次数,0:无限运行
		LPTimeoutCallback m_lpfn;//回调函数
		bool m_bRunning;//是否正在运行
		int m_nTimeouted;//已经间隔的时长
		int m_nCounted;//已经运行的次数

	private:
		friend class CTimerMgr;
		void OnTimeout(int millsecond);

	public:
		CTimer(int millsecond, LPTimeoutCallback lpfn, int count = 0);
		~CTimer();

		//************************************
		// Method:    开始运行定时器
		// Parameter: 是否清除已累计的超时时间
		//************************************
		void Run(bool clear = false);

		//************************************
		// Method:    暂停计时
		//************************************
		void Pause();

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