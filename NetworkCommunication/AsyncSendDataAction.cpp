#include "stdafx.h"
#include "AsyncSendDataAction.h"

namespace NetworkCommunication
{
	CAsyncSendDataAction::CAsyncSendDataAction(AsyncSendPeerData* pData) :
		CTcpAction(pData->send),
		m_pData(pData)
	{

	}

	CAsyncSendDataAction::~CAsyncSendDataAction()
	{
		if (m_pData)
		{
			if (m_pData->pBuf)
			{
				delete m_pData->pBuf;
			}
			delete m_pData;
		}
	}

	int CAsyncSendDataAction::GetActionType()
	{
		return ETcpActionType::AsyncSendData;
	}

	AsyncSendPeerData* CAsyncSendDataAction::GetSendData()
	{
		return m_pData;
	}
}