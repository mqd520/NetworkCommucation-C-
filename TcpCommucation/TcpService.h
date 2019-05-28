#pragma once
#include "Def.h"
#include "Include/tc/Def1.h"
#include "Thread.h"
#include "SocketAPI.h"
#include "Include/tc/TcpEvt.h"
#include "TcpConnection.h"

namespace tc
{
	// tcp服务
	class TcpService
	{
	protected:
		CSocketAPI m_socketAPI;			// socket api
		SOCKET socket;				// 关联的socket
		string strSelfIP;		// socket关联的服务端IP
		int nSelfPort;				// socket关联的服务端端口
		LPTcpEventCallback lpCallback;// tcp事件回调函数指针
		void* pParam;					// 事件附加参数

	protected:
		friend class CTcpEvtMgr;
		//************************************
		// Method:    收到tcp事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnRecvTcpEvent(TcpEvt* pEvent);

		//************************************
		// Method:    向对端发送数据
		// Returns:   是否成功
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		// Parameter: 是否异步,默认异步发送
		// Parameter: 实际发送字节长度
		//************************************
		bool SendData(SOCKET socket, BYTE* pBuf, int len, bool asyncs = true, int* actualLen = NULL);

		//************************************
		// Method:    通知调用者tcp事件
		// Parameter: tcp事件
		//************************************
		void DispatchTcpEvt(TcpEvt* pEvent);

	public:
		TcpService();
		~TcpService();

		//************************************
		// Method:    获取服务关联的socket
		//************************************
		SOCKET GetSocket();

		//************************************
		// Method:    获取自身关联的IP
		//************************************
		string GetSelfIP();

		//************************************
		// Method:    获取自身关联的端口
		//************************************
		int GetSelfPort();

		//************************************
		// Method:    注册tcp事件回调函数
		// Parameter: lpCallback:	回调函数
		// Parameter: pParam:		附加参数
		//************************************
		void RegTcpEventCallback(LPTcpEventCallback lpCallback, void* param);
	};
}