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
	// Method:    ��ʼ��
	//************************************
	void Init();

	//************************************
	// Method:    �˳�
	//************************************
	void Exit();

	//************************************
	// Method:    ��ȡ��tcp client
	//************************************
	TcpClient&	GetMainTcpClient();
};