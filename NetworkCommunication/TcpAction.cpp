#include "stdafx.h"
#include "TcpAction.h"

namespace NetworkCommunication
{
	CTcpAction::CTcpAction(SOCKET sendrecv /*= NULL*/, SOCKET attachment /*= NULL*/) :
		m_sendrecvSocket(sendrecv),
		m_attachmentSocket(attachment)
	{

	}

	CTcpAction::~CTcpAction()
	{

	}

	int CTcpAction::GetActionType()
	{
		return 0;
	}

	SOCKET CTcpAction::GetSendRecvSocket()
	{
		return m_sendrecvSocket;
	}

	SOCKET CTcpAction::GetAttachmentSocket()
	{
		return m_attachmentSocket;
	}
}