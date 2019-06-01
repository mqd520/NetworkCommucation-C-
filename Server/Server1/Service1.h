#pragma once

#include "ClientConnInfoMgr.h"

#include "tc/TcpServer.h"

using namespace tc;

// 用户服务类
class Service1
{
public:
	Service1();
	~Service1();

protected:
	TcpServer* pMainTcpSrv;	// tcp服务

protected:
	ClientConnInfoMgr ccMgr;	// 

public:
	void Init();

	TcpServer* GetMainTcpSrv();

	ClientConnInfoMgr* GetClientConnInfoMgr();
};