#pragma once
#include "TcpEvt.h"
#include "TcpService.h"

namespace NetworkCommunication
{
	//收到新连接事件
	class CRecvNewConnEvt : public CTcpEvt
	{
	public:
		bool m_bRefuse;//用户是否拒绝了新连接

	public:
		//************************************
		// Method:    构造函数
		// Parameter: 关联的tcp服务对象
		// Parameter: 关联的客户端socket
		//************************************
		CRecvNewConnEvt(CTcpService* pSrv, SOCKET client);
		~CRecvNewConnEvt();

		//************************************
		// Method:    获取事件类型
		//************************************
		int GetEvtType();
	};
}