#pragma once
#include "TcpEvt.h"

namespace tc
{
	// 连接服务端完成事件
	class ConnectSrvCplEvt : public TcpEvt
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: tcp 服务类
		// Parameter: socket
		// Parameter: 连接是否成功
		//************************************
		ConnectSrvCplEvt(TcpService* pSrv, SOCKET socket, bool success);
		~ConnectSrvCplEvt();

	private:
		bool	bSuccess;		// 连接是否成功

	public:
		//************************************
		// Method:    获取连接结果
		//************************************
		bool	GetConnectResult();
	};
}