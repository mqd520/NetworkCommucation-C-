#include "stdafx.h"
#include "SelectThread.h"
#include "Include/tc/TcpCommuMgr.h"
#include <tchar.h>
#include "Common.h"

namespace tc
{
	CSelectThread::CSelectThread()
	{

	}

	CSelectThread::~CSelectThread()
	{
		int n = 0;
	}

	void CSelectThread::Run()
	{
		if (!m_bRun)
		{
			PrintfInfo(_T("Select thread run"));
			__super::Run();
		}
	}

	void CSelectThread::OnThreadExecute()
	{
		if (CTcpCommuMgr::GetSelect()->IsEmpty())
		{
			SetSleepTime(10);
		}
		else
		{
			CTcpCommuMgr::GetSelect()->Select();
		}
	}
}