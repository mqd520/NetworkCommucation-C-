#pragma once

#include "ClientConnInfoMgr.h"

#include "tc/TcpServer.h"

using namespace tc;

// �û�������
class Service1
{
public:
	Service1();
	~Service1();

protected:
	TcpServer* pMainTcpSrv;	// tcp����

protected:
	ClientConnInfoMgr ccMgr;	// 

public:
	void Init();

	TcpServer* GetMainTcpSrv();

	ClientConnInfoMgr* GetClientConnInfoMgr();
};