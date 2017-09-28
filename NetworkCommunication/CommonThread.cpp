#include "stdafx.h"
#include "CommonThread.h"
#include "NetCommuMgr.h"
#include "Common.h"
#include <tchar.h>

namespace NetworkCommunication
{
	CCommonThread::CCommonThread()
	{

	}

	CCommonThread::~CCommonThread()
	{

	}

	void CCommonThread::OnThreadRun()
	{
		PrintfInfo(_T("Common thread run"));

		if (CNetworkCommuMgr::GetCommonSingal()->IsEmpty())
		{
			Sleep(10);
		}
		else
		{
			CNetworkCommuMgr::GetCommonSingal()->ProcessSocketSingal();
		}
	}
}