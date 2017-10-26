#pragma once

namespace NetworkCommunication
{
	class CTimeout;

	typedef void(*LPTimeoutCallback)(CTimeout* pTimeout, int count);

	class CTimeoutListMgr;

	//超时器
	class CTimeout
	{
	private:
		int m_nTimeout;//间隔时长(毫秒)
		int m_nCount;//运行次数,0:无限运行
		LPTimeoutCallback m_lpfn;//回调函数
		bool m_bRunning;//是否正在运行
		int m_nTimeouted;//已经间隔的时长
		int m_nCounted;//已经运行的次数

	private:
		friend class CTimeoutListMgr;
		void OnTimeout(int millsecond);

	public:
		CTimeout(int millsecond, LPTimeoutCallback lpfn, int count = 0);
		~CTimeout();

		void Run(bool clear = false);

		void Pause();

		bool IsRun();

		int Count();
	};
}