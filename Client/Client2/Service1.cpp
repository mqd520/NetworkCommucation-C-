#include "stdafx.h"
#include "Service1.h"
#include "Client2.h"
#include "Msg.h"

#include "log/LogSrv.h"
using namespace llog;

#include "tc/TcpEvt.h"
#include "tc/ConnectSrvCplEvt.h"
using namespace tc;


Service1::Service1()
{

}

Service1::~Service1()
{

}

void Service1::Init()
{

}

void Service1::Exit()
{
	//srvA.Exit();
	//srvB.Exit();
}

ServiceA& Service1::GetSrvA()
{
	return srvA;
}

//ServiceB& Service1::GetSrvB()
//{
//	return srvB;
//}

void Service1::WriteLog(ETcpLogType type, string log)
{
	if (theApp.m_pMainWnd)
	{
		bool b = true;
		if (type == ETcpLogType::Debug || type == ETcpLogType::Exception)
		{
#if _DEBUG
			b = true;
#else
			b = false;
#endif
		}

		if (b)
		{
			SendMessage(theApp.m_pMainWnd->m_hWnd, WM_USER_LOGINFO, (WPARAM)log.c_str(), NULL);
		}
	}

	ELogSrvType type1 = ELogSrvType::Info;
	if (type == ETcpLogType::Warn)
	{
		type1 = ELogSrvType::Warn;
	}
	else if (type == ETcpLogType::Debug)
	{
		type1 = ELogSrvType::Debug;
	}
	else if (type == ETcpLogType::Error)
	{
		type1 = ELogSrvType::Error;
	}
	else if (type == ETcpLogType::Fatal)
	{
		type1 = ELogSrvType::Fatal;
	}

	LogSrv::WriteLine(type1, log);
}