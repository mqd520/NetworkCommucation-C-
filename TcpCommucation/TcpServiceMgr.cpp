#include "stdafx.h"
#include "TcpServiceMgr.h"

namespace tc
{
	CTcpServiceMgr::CTcpServiceMgr()
	{

	}

	CTcpServiceMgr::~CTcpServiceMgr()
	{
		
	}

	void CTcpServiceMgr::PushTcpService(TcpService* srv)
	{
		m_vecTcpService.push_back(srv);
	}

	TcpService* CTcpServiceMgr::GetTcpSrvBySocket(SOCKET socket)
	{
		for (int i = 0; i < (int)m_vecTcpService.size(); i++)
		{
			if (m_vecTcpService[i]->GetSocket() == socket)
			{
				return m_vecTcpService[i];
			}
		}
		return NULL;
	}
}