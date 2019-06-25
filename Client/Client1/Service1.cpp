#include "stdafx.h"
#include "Service1.h"
#include "Client1.h"
#include "Msg.h"

#include "tc/TcpEvt.h"
#include "tc/ConnectSrvResultEvt.h"

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
	mainTcpClient.Exit();
}

TcpClient&	Service1::GetMainTcpClient()
{
	return mainTcpClient;
}

//************************************
// Method:    tcp事件回调函数
// Parameter: tcp事件对象
// Parameter: 附加参数1
// Parameter: 附加参数2
//************************************
void OnTcpEvt(TcpEvt* pEvt, void* pParam1, void* pParam2)
{
	ETcpEvtType type = pEvt->GetEvtType();
	if (type == ETcpEvtType::ConnectSrvResult)
	{
		ConnectSrvResultEvt* pEvt1 = static_cast<ConnectSrvResultEvt*>(pEvt);

		PostMessage(theApp.m_pMainWnd->m_hWnd, WM_USER_CONNECTRESULT, (WPARAM)pEvt1->GetConnectResult(), (LPARAM)pEvt1->GetTcpSrv());
	}
	else if (type == ETcpEvtType::ConnDisconnect)
	{
		PostMessage(theApp.m_pMainWnd->m_hWnd, WM_USER_CONNECTRESULT, (WPARAM)false, (LPARAM)pEvt->GetTcpSrv());
	}
}