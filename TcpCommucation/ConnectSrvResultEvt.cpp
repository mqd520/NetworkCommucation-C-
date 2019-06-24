#include "stdafx.h"
#include "Include/tc/ConnectSrvResultEvt.h"
#include "Def.h"
#include "Include/tc/Def1.h"

namespace tc
{
	ConnectSrvResultEvt::ConnectSrvResultEvt(TcpService* pSrv, bool success) :
		TcpEvt(pSrv),
		bSuccess(success)
	{
		evtType = ETcpEvtType::ConnectSrvResult;
	}

	ConnectSrvResultEvt::~ConnectSrvResultEvt()
	{

	}

	bool ConnectSrvResultEvt::GetConnectResult()
	{
		return bSuccess;
	}
}