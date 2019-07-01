#include "stdafx.h"
#include "Include/tc/SocketEvt.h"

namespace tc
{
	SocketEvt::SocketEvt()
	{
		evtType = ESocketEvtType::None;
	}

	SocketEvt::~SocketEvt()
	{

	}

	ESocketEvtType SocketEvt::GetEvtType() const
	{
		return evtType;
	}
}