#include "stdafx.h"
#include "SelectThread.h"
#include "NetCommuMgr.h"
#include <tchar.h>
#include "Common.h"

namespace NetworkCommunication
{
	CSelectThread::CSelectThread()
	{

	}

	CSelectThread::~CSelectThread()
	{

	}

	void CSelectThread::OnThreadRun()
	{
		PrintfInfo(_T("Select thread run"));

		if (CNetworkCommuMgr::GetSelect()->IsEmpty())
		{
			Sleep(10);
		}
		else
		{
			CNetworkCommuMgr::GetSelect()->Select();
		}
	}
}