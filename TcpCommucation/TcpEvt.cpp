#include "stdafx.h"
#include "Include/tc/Def.h"
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
		if (pSrv->GetTcpSrvType() == ETcpSrvType::Client)
		{
			strPeerIp = pSrv->GetIP();
			nPeerPort = pSrv->GetPort();
		}
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

	string TcpEvt::GetPeerIp()
	{
		return strPeerIp;
	}

	int TcpEvt::GetPeerPort()
	{
		return nPeerPort;
	}
}