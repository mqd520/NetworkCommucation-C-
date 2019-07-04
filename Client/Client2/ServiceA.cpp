#include "stdafx.h"
#include "ServiceA.h"

ServiceA::ServiceA(string ip /*= ""*/, int port /*= 0*/) :
IGPacketSrvClient(ip, port, EServerType::Plaza, EServerType::Center, true)
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