#include "stdafx.h"
#include "PeerCloseAction.h"

namespace NetworkCommunication
{
	CPeerCloseAction::CPeerCloseAction(SOCKET recv) :
		CTcpAction(recv, NULL)
	{

	}

	CPeerCloseAction::~CPeerCloseAction()
	{

	}

	int CPeerCloseAction::GetActionType()
	{
		return ETcpActionType::PeerCloseConn;
	}
}