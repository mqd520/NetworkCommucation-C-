#include "stdafx.h"
#include "RecvPeerDataAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	CRecvPeerDataAction::CRecvPeerDataAction(SocketRecvData data, SOCKET local) :
		CTcpAction(local, data.peer),
		m_recvData(data)
	{

	}

	CRecvPeerDataAction::~CRecvPeerDataAction()
	{

	}

	int CRecvPeerDataAction::GetActionType()
	{
		return ETcpActionType::RecvPeerData;
	}

	SocketRecvData CRecvPeerDataAction::GetRecvData()
	{
		return m_recvData;
	}
}