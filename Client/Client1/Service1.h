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
	// Method:    tcp�¼�����
	// Parameter: pEvent: tcp�¼�
	//************************************
	void OnTcpEvt(TcpEvt* pEvt, void* pParam1 = NULL, void* pParam2 = NULL);

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