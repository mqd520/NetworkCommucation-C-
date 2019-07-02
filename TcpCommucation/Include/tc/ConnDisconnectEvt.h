#pragma once
#include "TcpEvt.h"

namespace tc
{
	// 连接断开事件
	class ConnDisconnectEvt : public TcpEvt
	{
	public:
		ConnDisconnectEvt(TcpService* pSrv, SOCKET sendrecv, EDisconnReason reason);

	private:
		EDisconnReason reason;	// 连接断开原因

	public:
		//************************************
		// Method:    获取断开原因
		//************************************
		EDisconnReason GetReason();
	};
}