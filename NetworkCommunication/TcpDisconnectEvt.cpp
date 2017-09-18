#include "stdafx.h"
#include "TcpDisconnectEvt.h"
#include "Def.h"

namespace NetworkCommunication
{
	CTcpDisconnectEvt::CTcpDisconnectEvt(int reason, CTcpService* pSrv, SOCKET sendrecv/* = NULL*/)
		:CTcpSrvEvt(pSrv, sendrecv),
		m_nReason(reason)
	{

	}

	CTcpDisconnectEvt::~CTcpDisconnectEvt()
	{

	}

	int CTcpDisconnectEvt::GetEvtType()
	{
		return ETcpSrvEvent::TcpDisconnect;
	}

	int CTcpDisconnectEvt::GetReason()
	{
		return m_nReason;
	}
}