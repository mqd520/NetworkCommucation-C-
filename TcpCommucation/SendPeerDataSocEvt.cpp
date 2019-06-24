#include "stdafx.h"
#include "SendPeerDataSocEvt.h"

namespace tc
{
	SendPeerDataSocEvt::SendPeerDataSocEvt(SOCKET send, BYTE* buf, int len) :
		send(send),
		nLen(len)
	{
		__super::evtType = ESocketEvtType::SendPeerData;
		if (len > 0)
		{
			this->pBuf = new BYTE[len];
			memcpy(this->pBuf, buf, len);
		}
	}

	SendPeerDataSocEvt::~SendPeerDataSocEvt()
	{
		delete this->pBuf;
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