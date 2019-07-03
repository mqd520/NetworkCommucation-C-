#include "stdafx.h"
#include "Include/tc/RecvPeerDataEvt.h"
#include "Include/tc/Def.h"

namespace tc
{
	RecvPeerDataEvt::RecvPeerDataEvt(TcpService* pSrv, SOCKET recv, BYTE* pBuf, int len) :
		TcpEvt(pSrv, recv),
		pBuf(pBuf),
		nLen(len)
	{
		evtType = ETcpEvtType::RecvPeerData;
	}

	RecvPeerDataEvt::~RecvPeerDataEvt()
	{
		if (pBuf)
		{
			delete pBuf;
		}
	}

	BYTE* RecvPeerDataEvt::GetRecvBuf()
	{
		return pBuf;
	}

	int RecvPeerDataEvt::GetBufLen()
	{
		return nLen;
	}
}