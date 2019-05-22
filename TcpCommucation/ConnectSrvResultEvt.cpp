#include "stdafx.h"
#include "ConnectSrvResultEvt.h"
#include "Def.h"

namespace tc
{
	ConnectSrvResultEvt::ConnectSrvResultEvt(CTcpService* pSrv, bool success) :
		CTcpEvt(pSrv),
		bSuccess(success)
	{

	}

	ConnectSrvResultEvt::~ConnectSrvResultEvt()
	{

	}

	int ConnectSrvResultEvt::GetEvtType()
	{
		return ETcpEvent::ConnectSrvResult;
	}

	bool ConnectSrvResultEvt::GetConnectResult()
	{
		return bSuccess;
	}
}