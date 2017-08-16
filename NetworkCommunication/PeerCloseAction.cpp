#include "stdafx.h"
#include "PeerCloseAction.h"

namespace NetworkCommunication
{
	CPeerCloseAction::CPeerCloseAction(SOCKET peer) :
		CTcpAction(NULL, peer)
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