#pragma once
#include "SocketEvt.h"

namespace tc
{
	// 连接完成socket事件
	class ConnectCplSocEvt : public SocketEvt
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: 用于连接的socket
		// Parameter: 连接是否成功
		//************************************
		ConnectCplSocEvt(SOCKET socket, bool success);
		~ConnectCplSocEvt();

	private:
		SOCKET	socket;		// 用于连接的socket
		bool	success;	// 连接是否成功

	public:
		//************************************
		// Method:    用于连接的socket
		//************************************
		SOCKET	GetSocket() const;

		//************************************
		// Method:    获取连接是否成功
		//************************************
		bool	GetResult() const;
	};
}