#include "stdafx.h"
#include "Include/tc/ThreadMgr.h"

namespace tc
{
	CThreadMgr::CThreadMgr()
	{

	}

	CThreadMgr::~CThreadMgr()
	{
		Recycle();
	}

	void CThreadMgr::AddRecycleThread(CThread* pThread)
	{
		m_vecThread.push_back(pThread);
	}

	void CThreadMgr::Recycle()
	{
		m_vecThread.clear();
	}
}