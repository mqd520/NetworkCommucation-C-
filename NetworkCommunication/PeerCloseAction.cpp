#include "stdafx.h"
#include "PeerCloseAction.h"

namespace NetworkCommunication
{
	CPeerCloseAction::CPeerCloseAction(SOCKET local, SOCKET peer) :
		CTcpAction(local, peer)
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