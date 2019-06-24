#include "stdafx.h"
#include "ClientConnInfoMgr.h"

ClientConnInfoMgr::ClientConnInfoMgr()
{

}

ClientConnInfoMgr::~ClientConnInfoMgr()
{

}

int ClientConnInfoMgr::Add(string ip, int port, int clientId)
{
	int index = -1;

	bool b = false;
	for (vector<ClientConnInfo>::iterator it = vecClients.begin(); it != vecClients.end(); it++)
	{
		if (it->clientId == clientId)
		{
			b = true;
			break;
		}
	}

	if (!b)
	{
		ClientConnInfo info = { ip, port, clientId };
		vecClients.push_back(info);
		index = vecClients.size() - 1;
	}

	return index;
}

void ClientConnInfoMgr::Remove(int clientId)
{
	for (vector<ClientConnInfo>::iterator it = vecClients.begin(); it != vecClients.end(); it++)
	{
		if (it->clientId == clientId)
		{
			vecClients.erase(it);
			break;
		}
	}
}

void ClientConnInfoMgr::Remove(string ip, int port)
{
	for (vector<ClientConnInfo>::iterator it = vecClients.begin(); it != vecClients.end(); it++)
	{
		if (it->ip == ip && it->port == port)
		{
			vecClients.erase(it);
			break;
		}
	}
}

void ClientConnInfoMgr::RemoveById(int id)
{
	for (int i = 0; i < (int)vecClients.size(); i++)
	{
		if (i == id)
		{
			vecClients.erase(vecClients.begin() + i);
			break;
		}
	}
}

void ClientConnInfoMgr::Clear()
{
	vecClients.clear();
}

ClientConnInfo ClientConnInfoMgr::GetInfo(int id)
{
	ClientConnInfo info = { "", 0, 0 };

	for (int i = 0; i < (int)vecClients.size(); i++)
	{
		if (i == id)
		{
			info = vecClients[i];
			break;
		}
	}

	return info;
}

ClientConnInfo ClientConnInfoMgr::GetInfo(string ip, int port)
{
	ClientConnInfo info = { "", 0, 0 };

	for (vector<ClientConnInfo>::iterator it = vecClients.begin(); it != vecClients.end(); it++)
	{
		if (it->ip == ip && it->port == port)
		{
			info = *it;
			break;
		}
	}

	return info;
}

ClientConnInfo ClientConnInfoMgr::GetInfoByClientId(int clientId)
{
	ClientConnInfo info = { "", 0, 0 };

	for (vector<ClientConnInfo>::iterator it = vecClients.begin(); it != vecClients.end(); it++)
	{
		if (it->clientId == clientId)
		{
			info = *it;
			break;
		}
	}

	return info;
}

vector<ClientConnInfo> ClientConnInfoMgr::GetAll()
{
	vector<ClientConnInfo> vec;

	for (vector<ClientConnInfo>::iterator it = vecClients.begin(); it != vecClients.end(); it++)
	{
		vec.push_back(*it);
	}

	return vec;
}