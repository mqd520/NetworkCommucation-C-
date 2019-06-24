#pragma once
#include "tc/TcpClient.h"

using namespace tc;

// Service1
class Service1
{
public:
	Service1();
	~Service1();

protected:
	TcpClient mainTcpClient;	// main tcp client

public:
	//************************************
	// Method:    初始化
	//************************************
	void Init();

	//************************************
	// Method:    退出
	//************************************
	void Exit();

	//************************************
	// Method:    获取主tcp client
	//************************************
	TcpClient&	GetMainTcpClient();
};