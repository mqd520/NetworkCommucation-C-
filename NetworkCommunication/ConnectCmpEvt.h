#pragma once
#include "TcpEvt.h"

namespace NetworkCommunication
{
	//连接完成事件
	class CConnectCmpEvt : public CTcpEvt
	{
	private:
		bool m_bSuccess;//连接是否成功

	public:
		CConnectCmpEvt(CTcpService* pSrv, bool success);
		~CConnectCmpEvt();

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