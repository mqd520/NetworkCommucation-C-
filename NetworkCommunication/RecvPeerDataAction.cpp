#include "stdafx.h"
#include "RecvPeerDataAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	CRecvPeerDataAction::CRecvPeerDataAction(PeerData* pData) :
		CTcpAction(pData->socket),
		m_recvData(pData)
	{

	}

	CRecvPeerDataAction::~CRecvPeerDataAction()
	{
		if (m_recvData)
		{
			delete m_recvData;
		}
	}

	int CRecvPeerDataAction::GetActionType()
	{
		return ETcpActionType::RecvPeerData;
	}

	PeerData* CRecvPeerDataAction::GetPeerData()
	{
		return m_recvData;
	}
}