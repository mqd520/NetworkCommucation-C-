#pragma once
#include "TcpEvt.h"

namespace NetworkCommunication
{
	//tcp连接断开事件
	class CTcpDisconnectEvt : public CTcpEvt
	{
	public:
		CTcpDisconnectEvt(CTcpService* pSrv, SOCKET sendrecv = NULL);
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