#include "stdafx.h"
#include "RecvPeerDataAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	CRecvPeerDataAction::CRecvPeerDataAction(SOCKET recv, BYTE buf[], int len) :
		CTcpAction(recv),
		m_pBuf(buf),
		m_nLen(len)
	{

	}

	CRecvPeerDataAction::~CRecvPeerDataAction()
	{
		//m_pBufָ�뽫�ᴫ�ݸ���Ӧ���¼�����,���¼������ͷ�ָ��
	}

	int CRecvPeerDataAction::GetActionType()
	{
		return ETcpActionType::RecvPeerData;
	}

	int CRecvPeerDataAction::GetLen()
	{
		return m_nLen;
	}

	BYTE* CRecvPeerDataAction::GetBuf()
	{
		return m_pBuf;
	}
}