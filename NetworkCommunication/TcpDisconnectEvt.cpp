#include "stdafx.h"
#include "TcpDisconnectEvt.h"
#include "Def.h"

namespace NetworkCommunication
{
	CTcpDisconnectEvt::CTcpDisconnectEvt(CTcpService* pSrv, SOCKET sendrecv/* = NULL*/)
		:CTcpEvt(pSrv, sendrecv)
	{

	}

	CTcpDisconnectEvt::~CTcpDisconnectEvt()
	{

	}

	int CTcpDisconnectEvt::GetEvtType()
	{
		return ETcpSrvEvent::ConnDisconnect;
	}
}