#pragma once
#include "SocketAPI.h"
#include "TcpService.h"
#include "Def.h"

using namespace std;

namespace tc
{
	//tcp连接
	class CTcpConnection
	{
	protected:
		TcpService* m_pTcpSrv;//tcp服务对象
		SOCKET m_sendrecvSocket;//用于发送(接收)数据的socket
		BYTE* m_pAsyncSendBuf;//异步发送缓冲区                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
		int m_nAsyncSendLen;//异步发送数据长度
		int m_nAsyncSendStatus;//异步发送状态
		bool m_bCanAsyncSend;//指示发送线程是否可以发送数据
		NetAddress m_localAddress;//本地地址
		NetAddress m_peerAddress;//对端地址

	protected:
		//************************************
		// Method:    处理发送结果
		// Parameter: 发送成功与否
		//************************************
		virtual void ProcessSendResult(bool success);

	public:
		//************************************
		// Method:    构造函数
		// Parameter: tcp服务对象
		// Parameter: 用于发送(接收)数据的socket
		//************************************
		CTcpConnection(TcpService* pSrv, SOCKET sendrecv);
		~CTcpConnection();

		//************************************
		// Method:    获取用于发送(接收)数据的socket
		// Returns:   socket
		//************************************
		SOCKET GetSendRecvSocket();

		//************************************
		// Method:    获取本地地址
		//************************************
		NetAddress GetLocalAddress();

		//************************************
		// Method:    获取对端地址
		//************************************
		NetAddress GetPeerAddress();

		//************************************
		// Method:    获取关联的tcp服务对象
		// Returns:   tcp服务对象
		//************************************
		TcpService* GetTcpService();

		//************************************
		// Method:    异步发送数据
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		// Parameter: 实际发送字节长度
		//************************************
		void SetAsyncSendData(BYTE* pBuf, int len, int* actualLen = NULL);

		//************************************
		// Method:    发送数据
		// Returns:   是否成功
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		// Parameter: 实际发送字节长度
		//************************************
		bool SendData(BYTE* pBuf, int len, int* actualLen = NULL);

		//************************************
		// Method:    关闭tcp连接
		// Parameter: b:	是否产生连接断开事件, 默认: false
		//************************************
		void Close(bool b = false);

		//************************************
		// Method:    异步发送
		//************************************
		void AsyncSendData();

		//************************************
		// Method:    收到对端数据事件处理
		//************************************
		virtual void OnRecvPeerData();

		//************************************
		// Method:    连接断开事件处理
		//************************************
		virtual void OnConnDisconnect();

		//************************************
		// Method:    网络错误事件处理
		//************************************
		virtual void OnNetError();
	};
}