#pragma once
#include "TcpEvt.h"

namespace tc
{
	// 连接服务端结果事件
	class ConnectSrvResultEvt : public TcpEvt
	{
	private:
		bool bSuccess;	// 连接是否成功

	public:
		ConnectSrvResultEvt(CTcpService* pSrv, bool success);
		~ConnectSrvResultEvt();

		//************************************
		// Method:    获取连接结果
		//************************************
		bool GetConnectResult();
	};
}