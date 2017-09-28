#include "stdafx.h"
#include "TcpEvt.h"
#include "Def.h"

namespace NetworkCommunication
{
	CTcpEvt::CTcpEvt(CTcpService* pSrv, SOCKET sendrecv/* = NULL*/) :
		m_pTcpSrv(pSrv),
		m_socket(sendrecv)
	{

	}

	CTcpEvt::~CTcpEvt()
	{

	}

	int CTcpEvt::GetEvtType()
	{
		return ETcpSrvEvent::None;
	}

	CTcpService* CTcpEvt::GetTcpSrv()
	{
		return m_pTcpSrv;
	}

	SOCKET CTcpEvt::GetSendRecvSocket()
	{
		return m_socket;
	}
}