#pragma once
#include "TcpEvt.h"

namespace tc
{
	//连接服务端结果事件
	class CConnectSrvResultEvt : public CTcpEvt
	{
	private:
		bool m_bSuccess;//连接是否成功

	public:
		CConnectSrvResultEvt(CTcpService* pSrv, bool success);
		~CConnectSrvResultEvt();

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