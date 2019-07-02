#include "stdafx.h"
#include "Include/tc/ConnectSrvCplEvt.h"
#include "Include/tc/Def.h"

namespace tc
{
	ConnectSrvCplEvt::ConnectSrvCplEvt(TcpService* pSrv, SOCKET socket, bool success) :
		TcpEvt(pSrv, socket),
		bSuccess(success)
	{
		this->evtType = ETcpEvtType::ConnectSrvCpl;
	}

	//ConnectSrvCplEvt::~ConnectSrvCplEvt()
	//{

	//}

	bool ConnectSrvCplEvt::GetConnectResult()
	{
		return bSuccess;
	}
}