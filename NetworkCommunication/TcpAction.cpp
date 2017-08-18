#include "stdafx.h"
#include "TcpAction.h"

namespace NetworkCommunication
{
	CTcpAction::CTcpAction(SOCKET local /*= NULL*/, SOCKET socket /*= NULL*/) :
		m_localSocket(local),
		m_socket(socket)
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
		return m_localSocket;
	}
}