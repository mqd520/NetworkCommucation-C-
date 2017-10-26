#include "stdafx.h"
#include "ConnectCmpEvt.h"
#include "Def.h"

namespace NetworkCommunication
{
	CConnectCmpEvt::CConnectCmpEvt(CTcpService* pSrv, bool success) :
		CTcpEvt(pSrv),
		m_bSuccess(success)
	{

	}

	CConnectCmpEvt::~CConnectCmpEvt()
	{

	}

	int CConnectCmpEvt::GetEvtType()
	{
		return ETcpEvent::ConnectCmp;
	}

	bool CConnectCmpEvt::GetConnectResult()
	{
		return m_bSuccess;
	}
}