#include "stdafx.h"
#include "RecvPeerDataEvt.h"
#include "Def.h"

namespace tc
{
	CRecvPeerDataEvt::CRecvPeerDataEvt(CTcpService* pSrv, SOCKET recv, BYTE* pBuf, int len) :
		CTcpEvt(pSrv, recv),
		m_pBuf(pBuf),
		m_nLen(len)
	{

	}

	CRecvPeerDataEvt::~CRecvPeerDataEvt()
	{
		if (m_pBuf)
		{
			delete m_pBuf;
		}
	}

	int CRecvPeerDataEvt::GetEvtType()
	{
		return ETcpEvent::RecvPeerData;
	}

	BYTE* CRecvPeerDataEvt::GetRecvBuf()
	{
		return m_pBuf;
	}

	int CRecvPeerDataEvt::GetBufLen()
	{
		return m_nLen;
	}
}