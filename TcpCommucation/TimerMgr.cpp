#include "stdafx.h"
#include "TimerMgr.h"

namespace tc
{
	CTimerMgr::CTimerMgr()
	{

	}

	CTimerMgr::~CTimerMgr()
	{

	}

	void CTimerMgr::Add(CTimer* pTimeout)
	{
		m_vecTimeout.push_back(pTimeout);
	}

	int CTimerMgr::Count()
	{
		return m_vecTimeout.size();
	}

	void CTimerMgr::OnTimeout(int millsecond)
	{
		for (int i = 0; i < (int)m_vecTimeout.size(); i++)
		{
			m_vecTimeout[i]->OnTimeout(millsecond);
		}
	}
}