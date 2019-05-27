#pragma once
#include "TcpEvt.h"

namespace tc
{
	// tcp连接断开事件
	class ConnDisconnectEvt : public TcpEvt
	{
	public:
		ConnDisconnectEvt(CTcpService* pSrv, SOCKET sendrecv = NULL);
		~ConnDisconnectEvt();

		//************************************
		// Method:    获取断开原因
		//************************************
		int GetReason();
	};
}