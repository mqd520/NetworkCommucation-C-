#pragma once
#include "SocketEvt.h"

namespace tc
{
	// 连接断开socket事件
	class ConnDisconnSocEvt : public SocketEvt
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: sendrecv:	收发数据的socket
		//************************************
		ConnDisconnSocEvt(SOCKET sendrecv);
		~ConnDisconnSocEvt();

	private:
		SOCKET sendrecv;	// 关联的socket

	public:
		SOCKET GetSocket() const;
	};
}