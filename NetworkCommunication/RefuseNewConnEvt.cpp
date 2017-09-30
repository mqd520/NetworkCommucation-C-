#include "stdafx.h"
#include "RefuseNewConnEvt.h"

namespace NetworkCommunication
{
	CRefuseNewConnEvt::CRefuseNewConnEvt(CTcpService* pSrv, SOCKET client, TCHAR* ip, int port) :
		CTcpEvt(pSrv, client),
		m_nPort(port)
	{
		_tcscpy(m_strIP, ip);
	}

	CRefuseNewConnEvt::~CRefuseNewConnEvt()
	{

	}

	int CRefuseNewConnEvt::GetEvtType()
	{
		return ETcpEvent::RefuseNewConnection;
	}

	TCHAR* CRefuseNewConnEvt::GetClientIP()
	{
		return m_strIP;
	}

	int CRefuseNewConnEvt::GetClientPort()
	{
		return m_nPort;
	}
}