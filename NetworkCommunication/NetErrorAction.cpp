#include "stdafx.h"
#include "NetErrorAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	CNetErrorAction::CNetErrorAction(SOCKET sendrecv) :
		CTcpAction(sendrecv)
	{

	}

	CNetErrorAction::~CNetErrorAction()
	{

	}

	int CNetErrorAction::GetActionType()
	{
		return ETcpActionType::NetError;
	}
}