#include "stdafx.h"
#include "Include/tc/SafeLock.h"

namespace tc
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