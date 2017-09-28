#include "stdafx.h"
#include "RecvThread.h"
#include "NetCommuMgr.h"
#include "Common.h"

namespace NetworkCommunication
{
	CRecvThread::CRecvThread()
	{

	}

	CRecvThread::~CRecvThread()
	{

	}

	void CRecvThread::OnThreadRun()
	{
		//PrintfInfo(_T("Recv thread run"));

		if (CNetworkCommuMgr::GetRecvDataSingal()->IsEmpty())
		{
			Sleep(10);
		}
		else
		{
			CNetworkCommuMgr::GetRecvDataSingal()->ProcessSocketSingal();
		}
	}
}