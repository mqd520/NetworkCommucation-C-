#include "stdafx.h"
#include "Service1.h"
#include "Client1.h"
#include "Msg.h"

#include "tc/TcpEvt.h"
#include "tc/ConnectSrvCplEvt.h"


Service1::Service1()
{

}

void Service1::Init()
{
	Fun2 fun = std::bind(&Service1::OnTcpEvt, this, _1, _2, _3);
	mainTcpClient.RegTcpEventCallback(fun, NULL, NULL);
}

void Service1::Exit()
{
	mainTcpClient.Exit();
}

TcpClient& Service1::GetMainTcpClient()
{
	return mainTcpClient;
}

void Service1::OnTcpEvt(TcpEvt* pEvt, void* pParam1 /*= NULL*/, void* pParam2 /*= NULL*/)
{
	ETcpEvtType type = pEvt->GetEvtType();
	if (type == ETcpEvtType::ConnectSrvCpl)
	{
		ConnectSrvCplEvt* pEvt1 = static_cast<ConnectSrvCplEvt*>(pEvt);
		PostMessage(theApp.m_pMainWnd->m_hWnd, WM_USER_CONNECTRESULT, (WPARAM)pEvt1->GetConnectResult(), (LPARAM)pEvt1->GetTcpSrv());
	}
	else if (type == ETcpEvtType::ConnDisconnect)
	{
		PostMessage(theApp.m_pMainWnd->m_hWnd, WM_USER_CONNECTRESULT, (WPARAM)false, (LPARAM)pEvt->GetTcpSrv());
	}
}