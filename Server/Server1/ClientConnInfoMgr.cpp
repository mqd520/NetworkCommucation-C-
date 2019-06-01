#include "stdafx.h"
#include "ClientConnInfoMgr.h"

ClientConnInfoMgr::ClientConnInfoMgr()
{

}

ClientConnInfoMgr::~ClientConnInfoMgr()
{

}

int ClientConnInfoMgr::Add(string ip, int port, int socket)
{
	int index = -1;

	bool b = false;
	for (vector<ClientConnInfo>::iterator it = vecClients.begin(); it != vecClients.end(); it++)
	{
		if (it->socket == socket)
		{
			b = true;
			break;
		}
	}

	if (!b)
	{
		ClientConnInfo info = { ip, port, socket };
		vecClients.push_back(info);
		index = vecClients.size() - 1;
	}

	return index;
}

void ClientConnInfoMgr::Remove(int socket)
{
	for (vector<ClientConnInfo>::iterator it = vecClients.begin(); it != vecClients.end(); it++)
	{
		if (it->socket == socket)
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

ClientConnInfo ClientConnInfoMgr::GetInfoByNetId(int socket)
{
	ClientConnInfo info = { "", 0, 0 };

	for (vector<ClientConnInfo>::iterator it = vecClients.begin(); it != vecClients.end(); it++)
	{
		if (it->socket == socket)
		{
			info = *it;
			break;
		}
	}

	return info;
}