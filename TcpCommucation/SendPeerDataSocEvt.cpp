#include "stdafx.h"
#include "SendPeerDataSocEvt.h"

namespace tc
{
	SendPeerDataSocEvt::SendPeerDataSocEvt(SOCKET send, BYTE* pBuf, int len) :
		send(send),
		pBuf(pBuf),
		nLen(len)
	{
		__super::evtType = ESocketEvtType::SendPeerData;
	}

	SendPeerDataSocEvt::~SendPeerDataSocEvt()
	{

	}

	SOCKET	SendPeerDataSocEvt::GetSocket()
	{
		return send;
	}

	BYTE*	SendPeerDataSocEvt::GetBuf()
	{
		return pBuf;
	}

	int		SendPeerDataSocEvt::GetLen()
	{
		return nLen;
	}
}