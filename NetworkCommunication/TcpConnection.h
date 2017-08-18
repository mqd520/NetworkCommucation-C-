#pragma once
#include "SocketAPI.h"
#include "TcpService.h"

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
		// Method:    接收到对端数据事件处理
		// Parameter: 对端数据
		//************************************
		void OnRecvPeerData(PeerData* data);

		//************************************
		// Method:    对端主动关闭socket事件处理
		// Parameter: 关联到的本地socket
		//************************************
		void OnPeerCloseSocket(SOCKET socket);

		//************************************
		// Method:    发送数据(同步)
		// Returns:   是否成功
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		// Parameter: 实际发送字节长度
		//************************************
		bool SendData(BYTE buf[], int len, int* actualLen = NULL);
	};
}