#include "stdafx.h"
#include "SendThread.h"
#include "NetCommuMgr.h"
#include "Common.h"

namespace NetworkCommunication
{
	CSendThread::CSendThread()
	{

	}

	CSendThread::~CSendThread()
	{

	}

	void CSendThread::OnThreadRun()
	{
		//PrintfInfo(_T("Send thread run"));

		if (CNetworkCommuMgr::GetSendDataSingal()->IsEmpty())
		{
			Sleep(10);
		}
		else
		{
			CNetworkCommuMgr::GetSendDataSingal()->ProcessSocketSingal();
		}
	}
}