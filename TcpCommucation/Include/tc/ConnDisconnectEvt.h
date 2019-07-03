#pragma once
#include "TcpEvt.h"

namespace tc
{
	// 连接断开事件
	class ConnDisconnectEvt : public TcpEvt
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: tcp service
		// Parameter: SOCKET sendrecv
		// Parameter: 连接断开原因
		//************************************
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