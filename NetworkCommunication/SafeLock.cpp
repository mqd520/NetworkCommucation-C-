#include "stdafx.h"
#include "SafeLock.h"

namespace NetworkCommunication
{
	CSafeLock::CSafeLock(CThreadLock* pLock)
		: m_pLock(pLock)
	{
		if (m_pLock)
		{
			m_pLock->Lock();
		}
	}

	CSafeLock::~CSafeLock()
	{
		if (m_pLock)
		{
			m_pLock->Unlock();
		}
	}
}