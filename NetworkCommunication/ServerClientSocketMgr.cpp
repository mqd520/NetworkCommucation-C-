#include "stdafx.h"
#include "ServerClientSocketMgr.h"
#include "NetCommuMgr.h"

namespace NetworkCommunication
{
	CServerClientSocketMgr::CServerClientSocketMgr()
	{

	}

	CServerClientSocketMgr::~CServerClientSocketMgr()
	{

	}

	void CServerClientSocketMgr::PushAcceptSocketData(ServerClientSocket data)
	{
		m_vec.push_back(data);
	}

	ServerClientSocket CServerClientSocketMgr::GetDataByServerClientSocket(SOCKET peer)
	{
		for (int i = 0; i < (int)m_vec.size(); i++)
		{
			if (m_vec[i].client == peer)
			{
				return m_vec[i];
				break;
			}
		}
		return{ 0 };
	}

	ServerClientSocket CServerClientSocketMgr::GetDataByLocal(SOCKET local)
	{
		for (int i = 0; i < (int)m_vec.size(); i++)
		{
			if (m_vec[i].server == local)
			{
				return m_vec[i];
				break;
			}
		}
		return{ 0 };
	}

	ServerClientSocket CServerClientSocketMgr::Create(SOCKET peer, SOCKET local)
	{
		CSocketAPI api;
		ServerClientSocket data = { 0 };
		data.client = peer;
		data.server = local;
		api.GetIpAndPort(peer, data.ip, &data.port);
		CNetworkCommuMgr::GetServerClientSocketMgr()->PushAcceptSocketData(data);
		return data;
	}
}