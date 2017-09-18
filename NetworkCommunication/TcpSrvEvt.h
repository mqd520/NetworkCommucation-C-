#pragma once
#include "SocketAPI.h"

namespace NetworkCommunication
{
	class CTcpService;

	//tcp服务事件基类
	class CTcpSrvEvt
	{
	protected:
		CTcpService* m_pTcpSrv;//tcp服务对象
		SOCKET m_socket;//关联的用于发送(接收)数据的socket

	public:
		//************************************
		// Method:    构造函数
		// Parameter: 关联的tcp服务对象
		// Parameter: 关联的用于发送(接收)数据的socket
		//************************************
		CTcpSrvEvt(CTcpService* pSrv, SOCKET sendrecv = NULL);
		~CTcpSrvEvt();

		//************************************
		// Method:    获取事件类型
		//************************************
		virtual int GetEvtType();

		//************************************
		// Method:    获取tcp服务对象
		//************************************
		CTcpService* GetTcpSrv();

		//************************************
		// Method:    获取用于发送(接收)数据的socket
		//************************************
		virtual SOCKET GetSendRecvSocket();
	};
}