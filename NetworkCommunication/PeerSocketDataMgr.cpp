#include "stdafx.h"
#include "PeerSocketDataMgr.h"
#include "NetCommuMgr.h"

namespace NetworkCommunication
{
	CPeerSocketDataMgr::CPeerSocketDataMgr()
	{

	}

	CPeerSocketDataMgr::~CPeerSocketDataMgr()
	{

	}

	void CPeerSocketDataMgr::PushPeerSocketData(PeerSocketData data)
	{
		m_vec.push_back(data);
	}

	PeerSocketData CPeerSocketDataMgr::GetDataByPeer(SOCKET peer)
	{
		for (int i = 0; i < (int)m_vec.size(); i++)
		{
			if (m_vec[i].peer == peer)
			{
				return m_vec[i];
				break;
			}
		}
		return{ 0 };
	}

	PeerSocketData CPeerSocketDataMgr::GetDataByLocal(SOCKET local)
	{
		for (int i = 0; i < (int)m_vec.size(); i++)
		{
			if (m_vec[i].local == local)
			{
				return m_vec[i];
				break;
			}
		}
		return{ 0 };
	}

	PeerSocketData CPeerSocketDataMgr::Create(SOCKET peer, SOCKET local)
	{
		CSocketAPI api;
		PeerSocketData data = { 0 };
		data.peer = peer;
		data.local = local;
		api.GetIpAndPort(peer, data.ip, &data.port);
		CNetworkCommuMgr::GetPeerSocketDataMgr()->PushPeerSocketData(data);
		return data;
	}
}