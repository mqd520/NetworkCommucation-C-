#include "stdafx.h"
#include "ThreadMgr.h"

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