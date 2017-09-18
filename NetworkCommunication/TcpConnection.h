#pragma once
#include "SocketAPI.h"
#include "TcpService.h"
#include "SendPeerDataResultAction.h"
#include "RecvPeerDataAction.h"

using namespace std;

namespace NetworkCommunication
{
	//tcp连接
	class CTcpConnection
	{
	protected:
		CSocketAPI m_socketAPI;//socket api
		CTcpService* m_pTcpSrv;//tcp服务对象
		SOCKET m_sendrecvSocket;//用于发送(接收)数据的socket

	public:
		//************************************
		// Method:    构造函数
		// Parameter: tcp服务对象
		// Parameter: 用于发送(接收)数据的socket
		//************************************
		CTcpConnection(CTcpService* pSrv, SOCKET sendrecv);
		~CTcpConnection();

		//************************************
		// Method:    获取用于发送(接收)数据的socket
		// Returns:   socket
		//************************************
		SOCKET GetSendRecvSocket();

		//************************************
		// Method:    获取关联的tcp服务对象
		// Returns:   tcp服务对象
		//************************************
		CTcpService* GetTcpService();

		//************************************
		// Method:    发送数据
		// Returns:   是否成功
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		// Parameter: 实际发送字节长度
		//************************************
		bool SendData(BYTE buf[], int len, int* actualLen = NULL);

		//************************************
		// Method:    收到对端数据事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnRecvPeerData(CRecvPeerDataAction* pAction);

		//************************************
		// Method:    tcp连接断开事件处理
		//************************************
		virtual void OnTcpDisconnect(int reason);

		//************************************
		// Method:    发送对端数据完成事件处理
		// Parameter: 发送对端数据结果
		//************************************
		virtual void OnSendDataCompleted(SendPeerDataResult* pResult);

		//************************************
		// Method:    网络错误事件处理
		//************************************
		virtual void OnNetError();
	};
}