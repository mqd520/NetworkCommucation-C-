#include "stdafx.h"
#include "Include/tc/RecvPeerDataSocEvt.h"

namespace tc
{
	RecvPeerDataSocEvt::RecvPeerDataSocEvt(SOCKET recv, BYTE* pBuf, int len) :
		recv(recv),
		pBuf(pBuf),
		len(len)
	{
		this->evtType = ESocketEvtType::RecvPeerData;
	}

	RecvPeerDataSocEvt::~RecvPeerDataSocEvt()
	{

	}

	SOCKET RecvPeerDataSocEvt::GetSocket() const
	{
		return recv;
	}

	BYTE* RecvPeerDataSocEvt::GetBuf() const
	{
		return pBuf;
	}

	int RecvPeerDataSocEvt::GetLen() const
	{
		return len;
	}
}