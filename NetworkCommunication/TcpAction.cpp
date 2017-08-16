#include "stdafx.h"
#include "TcpAction.h"

namespace NetworkCommunication
{
	CTcpAction::CTcpAction(SOCKET local /*= NULL*/, SOCKET peer /*= NULL*/) :
		m_local(local),
		m_peer(peer)
	{

	}

	CTcpAction::~CTcpAction()
	{

	}

	int CTcpAction::GetActionType()
	{
		return 0;
	}

	SOCKET CTcpAction::GetLocalSocket()
	{
		return m_local;
	}

	SOCKET CTcpAction::GetPeerSocket()
	{
		return m_peer;
	}
}