#include "stdafx.h"
#include "Def.h"
#include "Include/tc/TcpEvt.h"
#include "Include/tc/TcpCommuMgr.h"

namespace tc
{
	TcpEvt::TcpEvt(TcpService* pSrv, SOCKET sendrecv/* = NULL*/) :
		pTcpSrv(pSrv),
		socket(sendrecv),
		evtType(ETcpEvtType::None)
	{
		SocketInfoData data = TcpCommu::GetSocketDataMgr()->GetSocketData(sendrecv);
		socketId = data.socketId;
	}

	TcpEvt::~TcpEvt()
	{

	}

	ETcpEvtType TcpEvt::GetEvtType()
	{
		return evtType;
	}

	TcpService* TcpEvt::GetTcpSrv()
	{
		return pTcpSrv;
	}

	int TcpEvt::GetSendRecvSocketId()
	{
		return socketId;
	}
}