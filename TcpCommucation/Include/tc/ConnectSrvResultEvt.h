#pragma once
#include "TcpEvt.h"

namespace tc
{
	// 连接服务端结果事件类
	class ConnectSrvResultEvt : public CTcpEvt
	{
	private:
		bool bSuccess;	// 连接是否成功

	public:
		ConnectSrvResultEvt(CTcpService* pSrv, bool success);
		~ConnectSrvResultEvt();

		//************************************
		// Method:    获取事件类型
		//************************************
		int GetEvtType();

		//************************************
		// Method:    获取连接结果
		//************************************
		bool GetConnectResult();
	};
}