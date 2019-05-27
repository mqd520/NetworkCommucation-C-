#include "stdafx.h"
#include "Def.h"
#include "Include/tc/Def1.h"
#include "Include/tc/TcpEvt.h"

namespace tc
{
	TcpEvt::TcpEvt(CTcpService* pSrv, SOCKET sendrecv/* = NULL*/) :
		pTcpSrv(pSrv),
		socket(sendrecv),
		evt(ETcpEvt::None)
	{

	}

	TcpEvt::~TcpEvt()
	{

	}

	int TcpEvt::GetEvtType()
	{
		return evt;
	}

	CTcpService* TcpEvt::GetTcpSrv()
	{
		return pTcpSrv;
	}

	SOCKET TcpEvt::GetSendRecvSocket()
	{
		return socket;
	}
}