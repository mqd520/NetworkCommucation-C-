#include "stdafx.h"
#include "Include/tc/TcpCommuMgr.h"
#include "Include/tc/ConnDisconnectEvt.h"
#include "Def.h"
#include "Include/tc/Def1.h"
#include "SocketDataMgr.h"

namespace tc
{
	ConnDisconnectEvt::ConnDisconnectEvt(TcpService* pSrv, SOCKET sendrecv/* = NULL*/)
		:TcpEvt(pSrv, sendrecv)
	{
		evtType = ETcpEvtType::ConnDisconnect;
		SocketInfoData data = TcpCommu::GetSocketDataMgr()->GetSocketData(sendrecv);
		strIP = data.peerIp;
		nPort = data.peerPort;
	}

	ConnDisconnectEvt::~ConnDisconnectEvt()
	{

	}

	int ConnDisconnectEvt::GetReason()
	{
		return 0;
	}

	string ConnDisconnectEvt::GetPeerIp()
	{
		return strIP;
	}

	int ConnDisconnectEvt::GetPeerPort()
	{
		return nPort;
	}
}
