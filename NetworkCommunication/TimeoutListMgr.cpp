#include "stdafx.h"
#include "TimeoutListMgr.h"

namespace NetworkCommunication
{
	CTimeoutListMgr::CTimeoutListMgr()
	{

	}

	CTimeoutListMgr::~CTimeoutListMgr()
	{

	}

	void CTimeoutListMgr::Add(CTimeout* pTimeout)
	{
		m_vecTimeout.push_back(pTimeout);
	}

	int CTimeoutListMgr::Count()
	{
		return m_vecTimeout.size();
	}

	void CTimeoutListMgr::OnTimeout(int millsecond)
	{
		for (int i = 0; i < (int)m_vecTimeout.size(); i++)
		{
			m_vecTimeout[i]->OnTimeout(millsecond);
		}
	}
}