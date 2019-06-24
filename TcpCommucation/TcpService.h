#pragma once
#include "Def.h"
#include "Include/tc/Def1.h"
#include "Thread.h"
#include "SocketAPI.h"
#include "Include/tc/TcpEvt.h"
#include "TcpConnection.h"
#include "Include/tc/SocketTool.h"

namespace tc
{
	// tcp服务基类
	class TcpService
	{
	public:
		TcpService(string ip = "", int port = 0);
		virtual ~TcpService();

	protected:
		SOCKET socket;			// 关联的socket
		string strIP;			// socket关联的服务端IP
		int nPort;				// socket关联的服务端端口
		LPTcpEventCallback lpCallback;	// tcp事件回调函数指针
		void* pParam1;					// 事件附加参数1
		void* pParam2;					// 事件附加参数2
		ETcpSrvType tcpSrvType;			// tcp srv type

	protected:
		friend class TcpEvtMgr;
		//************************************
		// Method:    收到tcp事件处理
		// Parameter: pEvent: tcp事件
		//************************************
		virtual void OnRecvTcpEvent(TcpEvt* pEvent);

		//************************************
		// Method:    向对端发送数据
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		//************************************
		void SendData(SOCKET socket, BYTE* pBuf, int len);

		//************************************
		// Method:    通知调用者tcp事件
		// Parameter: tcp事件
		//************************************
		void DispatchTcpEvt(TcpEvt* pEvent);

	public:
		//************************************
		// Method:    获取tcp srv type
		//************************************
		ETcpSrvType GetTcpSrvType();

		//************************************
		// Method:    获取关联的socket
		//************************************
		SOCKET GetSocket();

		//************************************
		// Method:    获取关联的服务端IP
		//************************************
		string GetIP();

		//************************************
		// Method:    获取关联的服务端端口
		//************************************
		int GetPort();

		//************************************
		// Method:    注册tcp事件回调函数
		// Parameter: lpCallback:	回调函数
		// Parameter: pParam1:		附加参数1
		// Parameter: pParam1:		附加参数2
		//************************************
		void RegTcpEventCallback(LPTcpEventCallback lpCallback, void* pParam1 = NULL, void* pParam2 = NULL);
	};
}