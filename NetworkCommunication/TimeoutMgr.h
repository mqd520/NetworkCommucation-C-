#pragma once
#include "TimeoutListMgr.h"
#include "TimeoutEvtProcess.h"
#include "TimeoutEvtThread.h"
#include "TimeoutThread.h"

namespace NetworkCommunication
{
	//��ʱ������
	class CTimeoutMgr
	{
	private:
		static int m_nUnitMillSecond;//��ʱ��λ
		static CTimeoutEvtThread m_timeoutEvtThread;
		static CTimeoutThread m_timeoutThread;

	public:
		static CTimeoutListMgr m_timeoutListMgr;
		static CTimeoutEvtProcess m_timeoutEvtProcess;

	public:
		CTimeoutMgr();
		~CTimeoutMgr();

		static void Init();

		static void Exit();

		static int GetUnitMillSecond();

		static void SetUnitMillSecond(int millsecond);
	};
}