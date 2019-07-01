#pragma once
#include "tc/TcpClient.h"

using namespace tc;

// Service1
class Service1
{
public:
	Service1();

protected:
	TcpClient mainTcpClient;	// main tcp client

protected:
	//************************************
	// Method:    tcp事件处理
	// Parameter: pEvent: tcp事件
	//************************************
	void OnTcpEvt(TcpEvt* pEvt, void* pParam1 = NULL, void* pParam2 = NULL);

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