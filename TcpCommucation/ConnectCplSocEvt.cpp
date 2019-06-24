#include "stdafx.h"
#include "ConnectCplSocEvt.h"

namespace tc
{
	ConnectCplSocEvt::ConnectCplSocEvt(SOCKET socket, bool success) :
		socket(socket),
		success(success)
	{
		this->evtType = ESocketEvtType::ConnectCpl;
	}

	ConnectCplSocEvt::~ConnectCplSocEvt()
	{

	}

	SOCKET	ConnectCplSocEvt::GetSocket() const
	{
		return socket;
	}

	bool	ConnectCplSocEvt::GetResult() const
	{
		return success;
	}
}