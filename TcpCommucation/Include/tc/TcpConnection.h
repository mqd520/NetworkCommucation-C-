#pragma once
#include "SocketAPI.h"
#include "TcpService.h"
#include "Def.h"

using namespace std;

namespace tc
{
	// tcp连接会话类
	class TcpConnection
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: tcp服务对象
		// Parameter: 用于发送(接收)数据的socket
		// Parameter: 是否立即加入select
		//************************************
		TcpConnection(TcpService* pSrv, SOCKET sendrecv, bool bEnable = true);
		~TcpConnection();

	protected:
		TcpService* pTcpSrv;	// tcp服务对象
		SOCKET sendrecvSocket;	// 用于发送(接收)数据的socket

	public:
		//************************************
		// Method:    获取用于发送(接收)数据的socket
		// Returns:   socket
		//************************************
		SOCKET GetSendRecvSocket();

		//************************************
		// Method:    获取关联的tcp服务对象
		// Returns:   tcp服务对象
		//************************************
		TcpService* GetTcpService();

		//************************************
		// Method:    发送数据
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		//************************************
		void SendData(BYTE* pBuf, int len);

		//************************************
		// Method:    关闭tcp连接
		// Parameter: b:	是否生成连接断开事件, 默认: false
		//************************************
		void Close(bool b = false);

		//************************************
		// Method:    收到对端数据事件处理
		// Parameter: pBuf:		缓冲区指针
		// Parameter: len:		缓冲区指针长度
		//************************************
		virtual void OnRecvPeerData(BYTE* pBuf, int len);

		//************************************
		// Method:    连接断开事件处理
		// Parameter: reason:	连接断开原因
		// Parameter: b:	是否生成连接断开事件, 默认: true
		//************************************
		virtual void OnConnDisconnect(EDisconnReason reason, bool b = true);

		//************************************
		// Method:    网络错误事件处理
		//************************************
		virtual void OnNetError();
	};
}