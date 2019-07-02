#include "stdafx.h"
#include "Include/tc/PacketClient.h"
#include "Include/tc/PacketHeadBase.h"

namespace tc
{
	PacketClient::PacketClient(string ip /*= ""*/, int port /*= 0*/) :
		TcpClient(ip, port),
		PacketCommuSrv(0, PacketHeadBase(0, 0))
	{

	}

	void PacketClient::OnTcpEvt(TcpEvt* pEvt)
	{
		TcpClient::OnTcpEvt(pEvt);
		PacketCommuSrv::OnRecvConnection(pEvt);
	}
}