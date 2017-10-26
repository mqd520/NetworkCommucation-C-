#include "stdafx.h"
#include "TimeoutMgr.h"

namespace NetworkCommunication
{
	CTimeoutListMgr CTimeoutMgr::m_timeoutListMgr;
	int CTimeoutMgr::m_nUnitMillSecond = 200;
	CTimeoutEvtProcess CTimeoutMgr::m_timeoutEvtProcess;
	CTimeoutEvtThread CTimeoutMgr::m_timeoutEvtThread;
	CTimeoutThread CTimeoutMgr::m_timeoutThread;

	CTimeoutMgr::CTimeoutMgr()
	{

	}

	CTimeoutMgr::~CTimeoutMgr()
	{

	}

	void CTimeoutMgr::Init()
	{
		m_timeoutThread.Run();
		m_timeoutEvtThread.Run();
	}

	void CTimeoutMgr::Exit()
	{
		m_timeoutThread.Exit();
		m_timeoutThread.Exit();
		::Sleep(m_nUnitMillSecond);
	}

	int CTimeoutMgr::GetUnitMillSecond()
	{
		return m_nUnitMillSecond;
	}

	void CTimeoutMgr::SetUnitMillSecond(int millsecond)
	{
		m_nUnitMillSecond = millsecond;
	}
}