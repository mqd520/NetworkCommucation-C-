#include "stdafx.h"
#include "Include/tc/PacketClient.h"

namespace tc
{
	PacketClient::PacketClient(string ip /*= ""*/, int port /*= 0*/) :
		TcpClient(ip, port)
	{

	}

	//void PacketClient::OnTcpEvt(TcpEvt* pEvt)
	//{
	//	TcpClient::OnTcpEvt(pEvt);

	//	if (pEvt->GetEvtType() == ETcpEvtType::RecvPeerData)
	//	{
	//		RecvPeerDataEvt* pEvt1 = (RecvPeerDataEvt*)pEvt;
	//		PacketSrv::ProcessRecvBuf(pEvt1->GetRecvBuf(), pEvt1->GetBufLen());
	//	}
	//}

	//void PacketClient::SendPck(Packet& pck)
	//{
	//	
	//}
}