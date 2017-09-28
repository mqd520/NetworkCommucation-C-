#include "stdafx.h"
#include "CommonThread.h"
#include "NetCommuMgr.h"
#include "Common.h"

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
		//PrintfInfo(_T(""));

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