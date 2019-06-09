#include "stdafx.h"
#include "Def.h"
#include "Include/tc/TcpEvt.h"

namespace tc
{
	TcpEvt::TcpEvt(TcpService* pSrv, SOCKET sendrecv/* = NULL*/) :
		pTcpSrv(pSrv),
		socket(sendrecv),
		evt(ETcpEvt::None)
	{

	}

	TcpEvt::~TcpEvt()
	{

	}

	ETcpEvt TcpEvt::GetEvtType()
	{
		return evt;
	}

	TcpService* TcpEvt::GetTcpSrv()
	{
		return pTcpSrv;
	}

	SOCKET TcpEvt::GetSendRecvSocket()
	{
		return socket;
	}
}