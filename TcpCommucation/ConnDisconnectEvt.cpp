#include "stdafx.h"
#include "Include/tc/ConnDisconnectEvt.h"
#include "Def.h"
#include "Include/tc/Def1.h"

namespace tc
{
	ConnDisconnectEvt::ConnDisconnectEvt(CTcpService* pSrv, SOCKET sendrecv/* = NULL*/)
		:TcpEvt(pSrv, sendrecv)
	{
		evt = ETcpEvt::ConnDisconnect;
	}

	ConnDisconnectEvt::~ConnDisconnectEvt()
	{

	}
}