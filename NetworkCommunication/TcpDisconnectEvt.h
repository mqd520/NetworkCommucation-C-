#pragma once
#include "TcpSrvEvt.h"

namespace NetworkCommunication
{
	//tcp连接断开事件
	class CTcpDisconnectEvt : public CTcpSrvEvt
	{
	private:
		int m_nReason;//断开原因

	public:
		CTcpDisconnectEvt(int reason, CTcpService* pSrv, SOCKET sendrecv = NULL);
		~CTcpDisconnectEvt();

		//************************************
		// Method:    获取事件类型
		//************************************
		int GetEvtType();

		//************************************
		// Method:    获取断开原因
		//************************************
		int GetReason();
	};
}