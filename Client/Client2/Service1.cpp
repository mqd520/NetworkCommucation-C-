#include "stdafx.h"
#include "Service1.h"
#include "Client2.h"
#include "Msg.h"
#include "LogSrv.h"

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
	srvA.SetService(this);
	srvA.RegTcpEventCallback(OnTcpEvt, &theApp);

	srvB.SetService(this);
	srvB.RegTcpEventCallback(OnTcpEvt, &theApp);
}

void Service1::Exit()
{
	srvA.Exit();
	srvB.Exit();
}

ServiceA& Service1::GetSrvA()
{
	return srvA;
}

ServiceB& Service1::GetSrvB()
{
	return srvB;
}

void Service1::WriteLog(ETcpLogType type, string log)
{
	if (theApp.m_pMainWnd)
	{
		SendMessage(theApp.m_pMainWnd->m_hWnd, WM_USER_LOGINFO, (WPARAM)log.c_str(), NULL);
	}

	ELogType type1 = ELogType::Other;
	if (type == ETcpLogType::Info)
	{
		type1 = ELogType::Info;
	}
	else if (type == ETcpLogType::Warn)
	{
		type1 = ELogType::Warn;
	}
	else if (type == ETcpLogType::Debug)
	{
		type1 = ELogType::Debug;
	}
	else if (type == ETcpLogType::Error)
	{
		type1 = ELogType::Error;
	}
	else if (type == ETcpLogType::Fatal)
	{
		type1 = ELogType::Fatal;
	}

	LogSrv::GetInstance()->Add(log, type1);
}

//************************************
// Method:    tcp事件回调函数
// Parameter: tcp事件对象
// Parameter: 附加参数1
// Parameter: 附加参数2
//************************************
void OnTcpEvt(TcpEvt* pEvt, void* pParam1, void* pParam2)
{
	if (pEvt->GetTcpSrv() == &theApp.GetSrv1().GetSrvA())
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
}