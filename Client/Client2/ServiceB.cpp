#include "stdafx.h"
#include "ServiceB.h"
#include "Service1.h"
#include "LogSrv.h"

ServiceB::ServiceB(Service1* pSrv1 /*= NULL*/, string ip /*= ""*/, int port /*= 0*/) :
LibServer(EServiceType::CenterSrv, true),
pSrv1(pSrv1)
{

}

ServiceB::~ServiceB()
{

}

void ServiceB::OnLog(ETcpLogType type, string log)
{
	pSrv1->WriteLog(type, log);
}

void ServiceB::OnProcessBusinessPck(PacketData& data)
{
	__super::OnProcessBusinessPck(data);
}

void ServiceB::SetService(Service1* pSrv1)
{
	this->pSrv1 = pSrv1;
}