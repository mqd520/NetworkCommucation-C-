#include "stdafx.h"
#include "Include/tc/ConnDisconnectEvt.h"
#include "Def.h"
#include "Include/tc/Def1.h"

namespace tc
{
	ConnDisconnectEvt::ConnDisconnectEvt(TcpService* pSrv, SOCKET sendrecv/* = NULL*/)
		:TcpEvt(pSrv, sendrecv)
	{
		evt = ETcpEvt::ConnDisconnect;
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
