#include "stdafx.h"
#include "ServiceA.h"

ServiceA::ServiceA(string ip /*= ""*/, int port /*= 0*/) :
IGPacketSrvClient(EServerType::Plaza, EServerType::Center, ip, port, true)
{

}

void ServiceA::PreProcessPck(PacketData& data)
{
	__super::PreProcessPck(data);
}

void ServiceA::OnProcessPck(PacketData& data)
{
	__super::OnProcessPck(data);
}