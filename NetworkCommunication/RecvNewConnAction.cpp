#include "stdafx.h"
#include "RecvNewConnAction.h"

namespace NetworkCommunication
{
	CRecvNewConnAction::CRecvNewConnAction(SOCKET server, SOCKET sendrecv) :
		CTcpAction(sendrecv, server)
	{

	}

	CRecvNewConnAction::~CRecvNewConnAction()
	{

	}

	int CRecvNewConnAction::GetActionType()
	{
		return ETcpActionType::RecvNewConnection;
	}
}