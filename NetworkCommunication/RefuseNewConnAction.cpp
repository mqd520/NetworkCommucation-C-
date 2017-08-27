#include "stdafx.h"
#include "RefuseNewConnAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	CRefuseNewConnAction::CRefuseNewConnAction(SOCKET server, SOCKET scSocket, char* ip, int port) :
		CTcpAction(scSocket, server)
	{
		strcpy(m_strIP, ip);
		m_nPort = port;
	}

	CRefuseNewConnAction::~CRefuseNewConnAction()
	{

	}

	int CRefuseNewConnAction::GetActionType()
	{
		return ETcpActionType::RefuseNewConn;
	}

	char* CRefuseNewConnAction::GetPeerIP()
	{
		return m_strIP;
	}

	int CRefuseNewConnAction::GetPeerPort()
	{
		return m_nPort;
	}
}