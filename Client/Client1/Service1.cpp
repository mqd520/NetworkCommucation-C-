#include "stdafx.h"
#include "Service1.h"
#include "Client1.h"

#include "tc/TcpEvt.h"

//************************************
// Method:    tcp�¼��ص�����
// Parameter: tcp�¼�����
// Parameter: ���Ӳ���1
// Parameter: ���Ӳ���2
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