#include "stdafx.h"
#include "RecvPeerDataAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	CRecvPeerDataAction::CRecvPeerDataAction(PeerData* pData) :
		CTcpAction(pData->socket),
		m_pRecvData(pData)
	{

	}

	CRecvPeerDataAction::~CRecvPeerDataAction()
	{
		if (m_pRecvData)
		{
			if (m_pRecvData->pBuf)
			{
				delete m_pRecvData->pBuf;
			}
			delete m_pRecvData;
		}
	}

	int CRecvPeerDataAction::GetActionType()
	{
		return ETcpActionType::RecvPeerData;
	}

	PeerData* CRecvPeerDataAction::GetPeerData()
	{
		return m_pRecvData;
	}
}