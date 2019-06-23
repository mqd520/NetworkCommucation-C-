#include "stdafx.h"
#include "ConnDisconnSocEvt.h"

namespace tc
{
	ConnDisconnSocEvt::ConnDisconnSocEvt(SOCKET sendrecv) :
		sendrecv(sendrecv)
	{
		this->evtType = ESocketEvtType::ConnDisconnect;
	}

	ConnDisconnSocEvt::~ConnDisconnSocEvt()
	{

	}

	SOCKET ConnDisconnSocEvt::GetSocket() const
	{
		return sendrecv;
	}
}