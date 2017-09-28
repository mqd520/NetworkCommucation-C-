#include "stdafx.h"
#include "SelectThread.h"
#include "NetCommuMgr.h"

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
		//PrintfInfo(_T(""));

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