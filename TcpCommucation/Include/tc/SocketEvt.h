#pragma once
#include "Def.h"

namespace tc
{
	// socket事件(基类)
	class SocketEvt
	{
	public:
		SocketEvt();
		virtual ~SocketEvt();

	protected:
		ESocketEvtType evtType;		// socket事件类型

	public:
		//************************************
		// Method:    获取事件类型
		//************************************
		ESocketEvtType GetEvtType() const;
	};
}