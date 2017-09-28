#pragma once
#include "Thread.h"
#include "Def.h"
#include "SocketAPI.h"
#include "TcpEvt.h"

namespace NetworkCommunication
{
	///tcp服务
	class CTcpService
	{
	protected:
		CSocketAPI m_socketAPI;//socket api
		int m_nSrvType;//服务类型
		SOCKET m_socket;//socket,服务端(客户端)socket
		TCHAR m_strLocalIP[20];//socket关联的本地IP
		int m_nLocalPort;//socket关联的本地端口
		LPTcpEventCallback m_lpCallback;//tcp事件回调函数指针

	protected:
		friend class CTcpEvtMgr;
		//************************************
		// Method:    收到tcp事件处理
		// Parameter: tcp事件
		//************************************
		void OnRecvTcpEvent(CTcpEvt* pEvent);

	public:
		CTcpService(int srvType);
		~CTcpService();

		//************************************
		// Method:    获取tcp服务类型
		//************************************
		int GetSrvType();

		//************************************
		// Method:    获取socket
		//************************************
		SOCKET GetSocket();

		//************************************
		// Method:    获取本地IP
		//************************************
		TCHAR* GetLocalIP();

		//************************************
		// Method:    获取本地端口
		//************************************
		int GetLocalPort();

		//************************************
		// Method:    注册tcp事件回调函数
		//************************************
		void RegTcpEventCallback(LPTcpEventCallback lpCallback);
	};
}