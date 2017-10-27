#include "stdafx.h"
#include "ConnectSrvResultEvt.h"
#include "Def.h"

namespace NetworkCommunication
{
	CConnectSrvResultEvt::CConnectSrvResultEvt(CTcpService* pSrv, bool success) :
		CTcpEvt(pSrv),
		m_bSuccess(success)
	{

	}

	CConnectSrvResultEvt::~CConnectSrvResultEvt()
	{

	}

	int CConnectSrvResultEvt::GetEvtType()
	{
		return ETcpEvent::ConnectSrvResult;
	}

	bool CConnectSrvResultEvt::GetConnectResult()
	{
		return m_bSuccess;
	}
}