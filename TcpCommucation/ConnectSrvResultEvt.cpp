#include "stdafx.h"
#include "Include/tc/ConnectSrvResultEvt.h"
#include "Def.h"
#include "Include/tc/Def1.h"

namespace tc
{
	ConnectSrvResultEvt::ConnectSrvResultEvt(TcpService* pSrv, SOCKET socket, bool success) :
		TcpEvt(pSrv, socket),
		bSuccess(success)
	{
		this->evtType = ETcpEvtType::ConnectSrvResult;
	}

	ConnectSrvResultEvt::~ConnectSrvResultEvt()
	{

	}

	bool ConnectSrvResultEvt::GetConnectResult()
	{
		return bSuccess;
	}
}