#include "stdafx.h"
#include "RecvNewConnEvt.h"
#include "Def.h"

namespace NetworkCommunication
{
	CRecvNewConnEvt::CRecvNewConnEvt(CTcpService* pSrv, SOCKET client) :
		CTcpSrvEvt(pSrv, client),
		m_bRefuse(false)
	{

	}

	CRecvNewConnEvt::~CRecvNewConnEvt()
	{

	}

	int CRecvNewConnEvt::GetEvtType()
	{
		return ETcpSrvEvent::RecvNewConnection;
	}
}