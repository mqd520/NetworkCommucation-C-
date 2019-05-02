#include "stdafx.h"
#include "RecvConnResultEvt.h"
#include "Def.h"

namespace NetworkCommunication
{
	CRecvConnResultEvt::CRecvConnResultEvt(CTcpService* pSrv, bool success, SOCKET client, TCHAR* ip, int port) :
		CTcpEvt(pSrv, client),
		m_bSuccess(success),
		m_nClientPort(port)
	{
		_tcscpy(m_strClientIP, ip);
	}

	CRecvConnResultEvt::~CRecvConnResultEvt()
	{

	}

	int CRecvConnResultEvt::GetEvtType()
	{
		return ETcpEvent::RecvConnResult;
	}

	bool CRecvConnResultEvt::GetRecvResult()
	{
		return m_bSuccess;
	}

	TCHAR* CRecvConnResultEvt::GetClientIP()
	{
		return m_strClientIP;
	}

	int CRecvConnResultEvt::GetClientPort()
	{
		return m_nClientPort;
	}
}