#pragma once

#include <string>
#include <vector>
#include "Def.h"

using namespace std;

// 客户端连接信息管理类
class ClientConnInfoMgr
{
public:
	ClientConnInfoMgr();
	~ClientConnInfoMgr();

private:
	vector<ClientConnInfo> vecClients;	// 客户端连接信息集合

public:
	int Add(string ip, int port, int clientId);

	void Remove(int clientId);

	void Remove(string ip, int port);

	void RemoveById(int id);

	void Clear();

	ClientConnInfo GetInfo(int id);

	ClientConnInfo GetInfo(string ip, int port);

	ClientConnInfo GetInfoByClientId(int clientId);

	vector<ClientConnInfo> GetAll();
};