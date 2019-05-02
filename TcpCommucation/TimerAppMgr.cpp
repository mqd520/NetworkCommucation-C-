#include "stdafx.h"
#include "TimerAppMgr.h"

namespace NetworkCommunication
{
	bool CTimerAppMgr::m_bExit = false;
	
	int CTimerAppMgr::m_nTimeoutUnit = 200;
	CProcessTimeoutThread CTimerAppMgr::m_processTimeoutThread;
	CBuildTimeoutThread CTimerAppMgr::m_buildTimeoutThread;
	CTimerMgr CTimerAppMgr::m_timerMgr;
	CTimeoutMgr CTimerAppMgr::m_timeoutMgr;

	CTimerAppMgr::CTimerAppMgr()
	{

	}

	CTimerAppMgr::~CTimerAppMgr()
	{

	}

	void CTimerAppMgr::Init()
	{
		m_buildTimeoutThread.Run();
		m_processTimeoutThread.Run();
	}

	void CTimerAppMgr::Exit()
	{
		m_buildTimeoutThread.Exit();
		m_processTimeoutThread.Exit();
#if RELEASE
		::Sleep(m_nTimeoutUnit);
#endif
	}

	int CTimerAppMgr::GetTimeoutUnit()
	{
		return m_nTimeoutUnit;
	}

	void CTimerAppMgr::SetTimeoutUnit(int millsecond)
	{
		m_nTimeoutUnit = millsecond;
	}

	bool CTimerAppMgr::CanExit()
	{
		return m_bExit;
	}

	CTimerMgr* CTimerAppMgr::GetTimerMgr()
	{
		return &m_timerMgr;
	}

	CTimeoutMgr* CTimerAppMgr::GetTimeoutMgr()
	{
		return &m_timeoutMgr;
	}
}