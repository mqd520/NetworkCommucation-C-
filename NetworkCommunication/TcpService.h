#pragma once
#include "Thread.h"
#include "Def.h"
#include "SocketAPI.h"
#include "TcpSrvEvt.h"

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
		friend class CTcpServiceMgr;
		//************************************
		// Method:    收到tcp事件处理
		// Parameter: tcp事件
		//************************************
		void OnRecvTcpEvent(CTcpSrvEvt* pEvent);

		////************************************
		//// Method:    收到新的客户端连接事件处理
		////************************************
		//virtual void OnRecvNewConnection(CTcpAction* pEvent);

		////************************************
		//// Method:    收到对端数据事件处理
		//// Parameter: 对端数据
		////************************************
		//virtual bool OnRecvPeerData(PeerData* data);

		////************************************
		//// Method:    对端主动关闭连接事件处理
		//// Parameter: 对端IP
		//// Parameter: 对端端口
		////************************************
		//virtual void OnPeerCloseConn(TCHAR* ip, int port);

		////************************************
		//// Method:    发送对端数据完成事件处理
		//// Parameter: 发送数据结果
		////************************************
		//virtual void OnSendPeerDataCompleted(SendPeerDataResult* result);

		////************************************
		//// Method:    网络错误事件处理
		//// Parameter: 对端IP
		//// Parameter: 对端端口
		////************************************
		//virtual void OnNetError(TCHAR* ip, int port);

		////************************************
		//// Method:    拒绝新客户端连接事件处理
		//// Parameter: 对端IP
		//// Parameter: 对端端口
		////************************************
		//virtual void OnRefuseNewConn(TCHAR* ip, int port);

	public:
		CTcpService(int srvType);
		~CTcpService();

		//************************************
		// Method:    运行处理新连接线程
		//************************************
		void Run();

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
		// Method:    向对端发送数据(同步)
		// Returns:   是否成功
		// Parameter: socket
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		// Parameter: 实际发送字节长度
		//************************************
		bool SendData(SOCKET socket, BYTE buf[], int len, int* actualLen = NULL);

		//************************************
		// Method:    向对端发送数据(异步)
		// Returns:   是否成功
		// Parameter: socket
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		// Parameter: 实际发送字节长度
		//************************************
		virtual void AsyncSendData(SOCKET socket, BYTE buf[], int len, int* actualLen = NULL);

		//************************************
		// Method:    注册tcp事件回调函数
		//************************************
		void RegTcpEventCallback(LPTcpEventCallback lpCallback);
	};
}