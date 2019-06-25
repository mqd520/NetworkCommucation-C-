#include "stdafx.h"
#include "TcpServiceMgr.h"

namespace tc
{
	TcpServiceMgr::TcpServiceMgr()
	{

	}

	TcpServiceMgr::~TcpServiceMgr()
	{

	}

	void TcpServiceMgr::Remove(TcpService* pTcpSrv)
	{
		for (vector<TcpService*>::iterator it = vecTcpSrv.begin(); it != vecTcpSrv.end(); it++)
		{
			if (*it == pTcpSrv)
			{
				vecTcpSrv.erase(it);
				break;
			}
		}
	}

	void TcpServiceMgr::Clear()
	{
		vecTcpSrv.clear();
	}

	void TcpServiceMgr::PushTcpService(TcpService* srv)
	{
		vecTcpSrv.push_back(srv);
	}

	TcpService* TcpServiceMgr::GetTcpSrvBySocket(SOCKET socket)
	{
		for (vector<TcpService*>::iterator it = vecTcpSrv.begin(); it != vecTcpSrv.end(); it++)
		{
			if ((*it)->GetSocket() == socket)
			{
				return *it;
			}
		}
		return NULL;
	}
}