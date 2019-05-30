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

	void TcpServiceMgr::PushTcpService(TcpService* srv)
	{
		vecTcpService.push_back(srv);
	}

	TcpService* TcpServiceMgr::GetTcpSrvBySocket(SOCKET socket)
	{
		for (int i = 0; i < (int)vecTcpService.size(); i++)
		{
			if (vecTcpService[i]->GetSocket() == socket)
			{
				return vecTcpService[i];
			}
		}
		return NULL;
	}
}