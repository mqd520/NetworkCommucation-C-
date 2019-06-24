#include "stdafx.h"
#include "Service1.h"
#include "Client1.h"

#include "tc/TcpEvt.h"

//************************************
// Method:    tcp事件回调函数
// Parameter: tcp事件对象
// Parameter: 附加参数1
// Parameter: 附加参数2
//************************************
void OnTcpEvt(TcpEvt* pEvt, void* pParam1, void* pParam2);

Service1::Service1()
{
	
}

Service1::~Service1()
{
	
}

void Service1::Init()
{
	mainTcpClient.RegTcpEventCallback(OnTcpEvt, &theApp);
}

void Service1::Exit()
{
	
}

TcpClient&	Service1::GetMainTcpClient()
{
	return mainTcpClient;
}

void OnTcpEvt(TcpEvt* pEvt, void* pParam1, void* pParam2)
{

}