#include "stdafx.h"
#include "Include/pck/SessionMgr.h"

namespace pck
{
	SessionMgr::SessionMgr()
	{

	}

	ServerSession* SessionMgr::GetSession(int clientId)
	{
		ServerSession* p = NULL;

		for (vector<ServerSession*>::iterator it = vecSessions.begin(); it != vecSessions.end(); it++)
		{
			if ((*it)->GetClientId() == clientId)
			{
				p = *it;
				break;
			}
		}

		return p;
	}

	ServerSession* SessionMgr::CreateSession(int clientId, void* pObj, bool recvPwd /*= true*/)
	{
		ServerSession* p = NULL;

		p = GetSession(clientId);
		if (p == NULL)
		{
			p = new ServerSession(clientId, pObj, recvPwd);
			vecSessions.push_back(p);
		}

		return p;
	}

	void SessionMgr::CloseSession(int clientId)
	{
		for (vector<ServerSession*>::iterator it = vecSessions.begin(); it != vecSessions.end(); it++)
		{
			if ((*it)->GetClientId() == clientId)
			{
				(*it)->Close();
				delete *it;
				vecSessions.erase(it);

				break;
			}
		}
	}

	void SessionMgr::CloseSession()
	{
		for (vector<ServerSession*>::iterator it = vecSessions.begin(); it != vecSessions.end(); it++)
		{
			(*it)->Close();
			delete *it;
			vecSessions.erase(it);
		}
	}
}