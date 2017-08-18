#include "stdafx.h"
#include "PeerCloseAction.h"

namespace NetworkCommunication
{
	CPeerCloseAction::CPeerCloseAction(SOCKET local) :
		CTcpAction(local)
	{

	}

	CPeerCloseAction::~CPeerCloseAction()
	{

	}

	int CPeerCloseAction::GetActionType()
	{
		return ETcpActionType::PeerClose;
	}
}