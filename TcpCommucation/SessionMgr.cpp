#include "stdafx.h"
#include "Include/tc/SessionMgr.h"

namespace tc
{
	typedef vector<TcpSession*>::iterator	ITTcpSession;

	SessionMgr::SessionMgr()
	{

	}

	SessionMgr::~SessionMgr()
	{
		Remove();
	}

	TcpSession* SessionMgr::CreateSession()
	{
		return new TcpSession();
	}

	void SessionMgr::Add(TcpSession* pData)
	{
		bool b = false;
		for (ITTcpSession it = vecSessions.begin(); it != vecSessions.end(); it++)
		{
			if ((*it)->strPeerIp == pData->strPeerIp && (*it)->nPeerPort == pData->nPeerPort)
			{
				b = true;
				break;
			}
		}

		if (!b)
		{
			vecSessions.push_back(pData);
		}
	}

	TcpSession* SessionMgr::Add(string peerIp /*= ""*/, int peerPort /*= 0*/, int clientId /*= 0*/, string localIp /*= ""*/, int localPort /*= 0*/)
	{
		TcpSession* pSession = CreateSession();
		pSession->strPeerIp = peerIp;
		pSession->nPeerPort = peerPort;
		pSession->nClientId = clientId;
		pSession->strLocalIp = localIp;
		pSession->nLocalPort = localPort;

		Add(pSession);

		return pSession;
	}

	TcpSession SessionMgr::Remove(int clientId)
	{
		TcpSession data;

		for (ITTcpSession it = vecSessions.begin(); it != vecSessions.end(); it++)
		{
			if ((*it)->nClientId == clientId)
			{
				data = *(*it);
				vecSessions.erase(it);
				break;
			}
		}

		return data;
	}

	TcpSession SessionMgr::Remove(string peerIp, int peerPort)
	{
		TcpSession data;

		for (ITTcpSession it = vecSessions.begin(); it != vecSessions.end(); it++)
		{
			if ((*it)->strPeerIp == peerIp && (*it)->nPeerPort == peerPort)
			{
				data = *(*it);
				vecSessions.erase(it);
				break;
			}
		}

		return data;
	}

	void SessionMgr::Remove()
	{
		for (ITTcpSession it = vecSessions.begin(); it != vecSessions.end(); it++)
		{
			delete *it;
		}

		vecSessions.clear();
	}

	TcpSession SessionMgr::Get(int clientId)
	{
		TcpSession data;

		for (ITTcpSession it = vecSessions.begin(); it != vecSessions.end(); it++)
		{
			if ((*it)->nClientId == clientId)
			{
				data = *(*it);
				break;
			}
		}

		return data;
	}

	TcpSession SessionMgr::Get(string peerIp, int peerPort)
	{
		TcpSession data;

		for (ITTcpSession it = vecSessions.begin(); it != vecSessions.end(); it++)
		{
			if ((*it)->strPeerIp == peerIp && (*it)->nPeerPort == peerPort)
			{
				data = *(*it);
				break;
			}
		}

		return data;
	}

	TcpSession* SessionMgr::Get1(int clientId)
	{
		TcpSession* p = NULL;

		for (ITTcpSession it = vecSessions.begin(); it != vecSessions.end(); it++)
		{
			if ((*it)->nClientId == clientId)
			{
				p = (*it);
				break;
			}
		}

		return p;
	}

	TcpSession* SessionMgr::Get1(string peerIp, int peerPort)
	{
		TcpSession* p = NULL;

		for (ITTcpSession it = vecSessions.begin(); it != vecSessions.end(); it++)
		{
			if ((*it)->strPeerIp == peerIp && (*it)->nPeerPort == peerPort)
			{
				p = (*it);
				break;
			}
		}

		return p;
	}

	void SessionMgr::GetAllClientId(vector<int>& vec)
	{
		for (ITTcpSession it = vecSessions.begin(); it != vecSessions.end(); it++)
		{
			vec.push_back((*it)->nClientId);
		}
	}
}