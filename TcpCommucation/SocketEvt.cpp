#include "stdafx.h"
#include "SocketEvt.h"

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