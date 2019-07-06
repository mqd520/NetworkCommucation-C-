#include "stdafx.h"
#include "Include/tc/SessionMgr.h"

namespace tc
{
	typedef vector<TcpSession>::iterator	ITTcpSession;

	SessionMgr::SessionMgr()
	{

	}

	SessionMgr::~SessionMgr()
	{

	}

	bool SessionMgr::IsEqual(const TcpSession& obj1, const TcpSession& obj2)
	{
		if (obj1.strPeerIp == obj2.strPeerIp && obj1.nPeerPort == obj2.nPeerPort)
		{
			return true;
		}

		return false;
	}

	void SessionMgr::Add(TcpSession& data)
	{
		bool b = false;
		for (ITTcpSession it = vecSessionDatas.begin(); it != vecSessionDatas.end(); it++)
		{
			if (IsEqual(*it, data))
			{
				b = true;
				break;
			}
		}

		if (!b)
		{
			vecSessionDatas.push_back(data);
		}
	}

	TcpSession SessionMgr::Remove(int clientId)
	{
		TcpSession data;

		for (ITTcpSession it = vecSessionDatas.begin(); it != vecSessionDatas.end(); it++)
		{
			if (it->nClientId == clientId)
			{
				data = *it;
				vecSessionDatas.erase(it);
				break;
			}
		}

		return data;
	}

	TcpSession SessionMgr::Remove(string peerIp, int peerPort)
	{
		TcpSession data;

		for (ITTcpSession it = vecSessionDatas.begin(); it != vecSessionDatas.end(); it++)
		{
			if (it->strPeerIp == peerIp && it->nPeerPort == peerPort)
			{
				data = *it;
				vecSessionDatas.erase(it);
				break;
			}
		}

		return data;
	}

	void SessionMgr::Remove(TcpSession& data)
	{
		for (ITTcpSession it = vecSessionDatas.begin(); it != vecSessionDatas.end(); it++)
		{
			if (IsEqual(*it, data))
			{
				vecSessionDatas.erase(it);
				break;
			}
		}
	}

	void SessionMgr::Remove()
	{
		vecSessionDatas.clear();
	}

	TcpSession SessionMgr::Get(int clientId)
	{
		TcpSession data;

		for (ITTcpSession it = vecSessionDatas.begin(); it != vecSessionDatas.end(); it++)
		{
			if (it->nClientId == clientId)
			{
				data = *it;
				break;
			}
		}

		return data;
	}

	TcpSession SessionMgr::Get(string peerIp, int peerPort)
	{
		TcpSession data;

		for (ITTcpSession it = vecSessionDatas.begin(); it != vecSessionDatas.end(); it++)
		{
			if (it->strPeerIp == peerIp && it->nPeerPort == peerPort)
			{
				data = *it;
				break;
			}
		}

		return data;
	}

	void SessionMgr::Get(vector<TcpSession>& vec)
	{
		for (ITTcpSession it = vecSessionDatas.begin(); it != vecSessionDatas.end(); it++)
		{
			vec.push_back(*it);
		}
	}
}