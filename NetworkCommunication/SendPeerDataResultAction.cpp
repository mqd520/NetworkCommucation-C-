#include "stdafx.h"
#include "SendPeerDataResultAction.h"

namespace NetworkCommunication
{
	CSendPeerDataResultAction::CSendPeerDataResultAction(SendPeerDataResult data, SOCKET local) :
		CTcpAction(local, data.peer),
		m_result(data)
	{

	}

	CSendPeerDataResultAction::~CSendPeerDataResultAction()
	{

	}

	int CSendPeerDataResultAction::GetActionType()
	{
		return ETcpActionType::SendPeerDataResult;
	}

	SendPeerDataResult CSendPeerDataResultAction::GetResult()
	{
		return m_result;
	}
}