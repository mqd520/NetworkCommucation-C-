#include "stdafx.h"
#include "RefuseNewConnAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	CRefuseNewConnAction::CRefuseNewConnAction(SOCKET server, SOCKET scSocket, TCHAR* ip, int port) :
		CTcpAction(scSocket, server)
	{
		_tcscpy(m_strIP, ip);
		m_nPort = port;
	}

	CRefuseNewConnAction::~CRefuseNewConnAction()
	{

	}

	int CRefuseNewConnAction::GetActionType()
	{
		return ETcpActionType::RefuseNewConn;
	}

	TCHAR* CRefuseNewConnAction::GetPeerIP()
	{
		return m_strIP;
	}

	int CRefuseNewConnAction::GetPeerPort()
	{
		return m_nPort;
	}
}