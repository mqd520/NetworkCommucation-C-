#include "stdafx.h"
#include "ServiceA.h"
#include "Service1.h"
#include "LogSrv.h"

ServiceA::ServiceA(Service1* pSrv1 /*= NULL*/, string ip /*= ""*/, int port /*= 0*/) :
LibClient(EServiceType::PlazaSrv, true),
pSrv1(pSrv1)
{
	this->SetAutoReconnect(false);
}

ServiceA::~ServiceA()
{

}

void ServiceA::OnLog(ETcpLogType type, string log)
{
	pSrv1->WriteLog(type, log);
}

void ServiceA::OnProcessBusinessPck(PacketData& data)
{
	__super::OnProcessBusinessPck(data);
}

void ServiceA::SetService(Service1* pSrv1)
{
	this->pSrv1 = pSrv1;
}