#include "stdafx.h"
#include "SendPeerDataResultAction.h"

namespace NetworkCommunication
{
	CSendPeerDataResultAction::CSendPeerDataResultAction(SendPeerDataResult* data, SOCKET send) :
		CTcpAction(send, NULL),
		m_pResult(data)
	{

	}

	CSendPeerDataResultAction::~CSendPeerDataResultAction()
	{
		if (m_pResult)
		{
			delete m_pResult;
		}
	}

	int CSendPeerDataResultAction::GetActionType()
	{
		return ETcpActionType::SendDataResult;
	}

	SendPeerDataResult* CSendPeerDataResultAction::GetResult()
	{
		return m_pResult;
	}
}