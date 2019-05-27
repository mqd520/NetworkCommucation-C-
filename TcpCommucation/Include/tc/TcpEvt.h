#pragma once
#include "SocketAPI.h"

namespace tc
{
	class CTcpService;

	//tcp服务事件基类
	class TcpEvt
	{
	protected:
		CTcpService* pTcpSrv;	// tcp服务对象
		SOCKET socket;			// 关联的用于发送(接收)数据的socket
		int evt;				// 事件类型

	public:
		//************************************
		// Method:    构造函数
		// Parameter: 关联的tcp服务对象
		// Parameter: 关联的用于发送(接收)数据的socket
		//************************************
		TcpEvt(CTcpService* pSrv, SOCKET sendrecv = NULL);
		virtual ~TcpEvt();

		//************************************
		// Method:    获取事件类型
		//************************************
		int GetEvtType();

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