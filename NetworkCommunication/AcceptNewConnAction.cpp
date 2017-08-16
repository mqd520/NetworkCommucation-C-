#include "stdafx.h"
#include "AcceptNewConnAction.h"

namespace NetworkCommunication
{
	CAcceptNewConnAction::CAcceptNewConnAction(SOCKET server, SOCKET client) :
		CTcpAction(server, client)
	{

	}

	CAcceptNewConnAction::~CAcceptNewConnAction()
	{

	}

	int CAcceptNewConnAction::GetActionType()
	{
		return ETcpActionType::AcceptNewConnection;
	}
}