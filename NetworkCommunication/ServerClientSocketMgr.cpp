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

	void CServerClientSocketMgr::PushSocketData(ClientSocketData data)
	{
		m_vec.push_back(data);
	}

	ClientSocketData CServerClientSocketMgr::GetDataByServerClientSocket(SOCKET peer)
	{
		for (int i = 0; i < (int)m_vec.size(); i++)
		{
			if (m_vec[i].scClient == peer)
			{
				return m_vec[i];
				break;
			}
		}
		return{ 0 };
	}

	ClientSocketData CServerClientSocketMgr::GetDataByLocalSocket(SOCKET local)
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
}