#include "stdafx.h"
#include "TcpServiceMgr.h"
#include "NetCommuMgr.h"
#include "RecvNewConnAction.h"
#include "Common.h"

namespace NetworkCommunication
{
	CTcpServiceMgr::CTcpServiceMgr()
	{

	}

	CTcpServiceMgr::~CTcpServiceMgr()
	{

	}

	void CTcpServiceMgr::PushTcpService(CTcpService* srv)
	{
		m_vecTcpService.push_back(srv);
	}

	CTcpService* CTcpServiceMgr::GetTcpSrvBySocket(SOCKET socket)
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