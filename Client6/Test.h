#pragma once

#include "TcpClientT.h"

using namespace NetworkCommunication;

class MyClass
{
public:
	MyClass();
	~MyClass();

protected:
	CTcpClientT<MyClass> m_tcp;

protected:
	bool OnRecvData(BYTE buf[], int len);
	void OnRecvEvt(TcpEvtType type, TCHAR* msg);

public:
	void Init(TCHAR* ip, int port);
	void Connect();
	bool SendData(BYTE* buf, int len);
};