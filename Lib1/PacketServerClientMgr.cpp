#include "stdafx.h"
#include "PacketServerClientMgr.h"

namespace lib1
{
	PacketServerClientMgr::PacketServerClientMgr()
	{

	}

	PacketServerClientMgr::~PacketServerClientMgr()
	{
		for (vector<PacketServerClient*>::iterator it = vecClients.begin(); it != vecClients.end(); it++)
		{
			delete *it;
		}

		vecClients.clear();
	}

	PacketServerClient* PacketServerClientMgr::CreateClient(int clientId, void* pSrv, bool bNeedVertify /*= true*/)
	{
		PacketServerClient* p = NULL;

		bool b = false;
		for (vector<PacketServerClient*>::iterator it = vecClients.begin(); it != vecClients.end(); it++)
		{
			if ((*it)->GetClientId() == clientId)
			{
				b = true;
				break;
			}
		}

		if (!b)
		{
			p = new PacketServerClient(clientId, pSrv, bNeedVertify);
			vecClients.push_back(p);
		}

		return p;
	}

	PacketServerClient* PacketServerClientMgr::GetClient(int clientId)
	{
		PacketServerClient* p = NULL;

		for (vector<PacketServerClient*>::iterator it = vecClients.begin(); it != vecClients.end(); it++)
		{
			if ((*it)->GetClientId() == clientId)
			{
				p = *it;
				break;
			}
		}

		return p;
	}

	void PacketServerClientMgr::Remove(int clientId)
	{
		for (vector<PacketServerClient*>::iterator it = vecClients.begin(); it != vecClients.end(); it++)
		{
			if ((*it)->GetClientId() == clientId)
			{
				delete *it;

				vecClients.erase(it);
				break;
			}
		}
	}

	void PacketServerClientMgr::CloseAll()
	{
		for (vector<PacketServerClient*>::iterator it = vecClients.begin(); it != vecClients.end(); it++)
		{
			(*it)->OnClose();

			delete (*it);
		}

		vecClients.clear();
	}
}