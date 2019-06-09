#pragma once
#include "Include/tc/SocketTool.h"
#include "Include/tc/Def1.h"

namespace tc
{
	class TcpService;

	// tcp服务事件基类
	class TcpEvt
	{
	protected:
		TcpService* pTcpSrv;	// tcp服务对象
		SOCKET socket;			// 关联的用于发送(接收)数据的socket
		ETcpEvt evt;			// 事件类型

	public:
		//************************************
		// Method:    构造函数
		// Parameter: 关联的tcp服务对象
		// Parameter: 关联的用于发送(接收)数据的socket
		//************************************
		TcpEvt(TcpService* pSrv, SOCKET sendrecv = NULL);
		virtual ~TcpEvt();

		//************************************
		// Method:    获取事件类型
		//************************************
		ETcpEvt GetEvtType();

		//************************************
		// Method:    获取tcp服务对象
		//************************************
		TcpService* GetTcpSrv();

		//************************************
		// Method:    获取用于发送(接收)数据的socket
		//************************************
		virtual SOCKET GetSendRecvSocket();
	};
}