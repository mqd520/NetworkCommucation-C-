#pragma once
#include "SocketTool.h"
#include "Def.h"

namespace tc
{
	class TcpService;

	// tcp服务事件基类
	class TcpEvt
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: 关联的tcp服务对象
		// Parameter: 关联的用于发送(接收)数据的socket
		//************************************
		TcpEvt(TcpService* pSrv, SOCKET sendrecv = NULL);
		virtual ~TcpEvt();

	protected:
		TcpService* pTcpSrv;	// tcp服务对象
		SOCKET socket;			// 关联的用于发送(接收)数据的socket
		ETcpEvtType evtType;	// 事件类型
		int socketId;			// socket id
		string strPeerIp;		// peer ip
		int nPeerPort;			// peer port

	public:
		//************************************
		// Method:    获取事件类型
		//************************************
		virtual ETcpEvtType GetEvtType();

		//************************************
		// Method:    获取tcp服务对象
		//************************************
		virtual TcpService* GetTcpSrv();

		//************************************
		// Method:    获取用于发送(接收)数据的socket id
		//************************************
		virtual int GetSendRecvSocketId();

		//************************************
		// Method:    获取socket
		//************************************
		virtual SOCKET GetSendRecvSocket();

		//************************************
		// Method:    获取对端ip
		//************************************
		virtual string GetPeerIp();

		//************************************
		// Method:    获取对端port
		//************************************
		virtual int GetPeerPort();
	};
}