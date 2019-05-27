#include "stdafx.h"
#include "RecvNewConnEvt.h"
#include "Def.h"

namespace tc
{
	CRecvNewConnEvt::CRecvNewConnEvt(CTcpService* pSrv, SOCKET client) :
		TcpEvt(pSrv, client),
		m_bRefuse(false)
	{

	}

	CRecvNewConnEvt::~CRecvNewConnEvt()
	{

	}

	int CRecvNewConnEvt::GetEvtType()
	{
		return ETcpEvent::RecvNewConnection;
	}
}