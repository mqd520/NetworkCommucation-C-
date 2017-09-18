#include "stdafx.h"
#include "TcpSrvEvt.h"
#include "Def.h"

namespace NetworkCommunication
{
	CTcpSrvEvt::CTcpSrvEvt(CTcpService* pSrv, SOCKET sendrecv/* = NULL*/) :
		m_pTcpSrv(pSrv),
		m_socket(sendrecv)
	{

	}

	CTcpSrvEvt::~CTcpSrvEvt()
	{

	}

	int CTcpSrvEvt::GetEvtType()
	{
		return ETcpSrvEvent::None;
	}

	CTcpService* CTcpSrvEvt::GetTcpSrv()
	{
		return m_pTcpSrv;
	}

	SOCKET CTcpSrvEvt::GetSendRecvSocket()
	{
		return m_socket;
	}
}