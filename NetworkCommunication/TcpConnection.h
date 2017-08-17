#pragma once
#include "SocketAPI.h"
#include "TcpService.h"

using namespace std;

namespace NetworkCommunication
{
	//tcp会话
	class CTcpConnection
	{
	private:
		CSocketAPI m_socketAPI;
		SOCKET m_peerSocket;//对端socket
		SOCKET m_localSocket;//本地socket
		CTcpService* m_pTcpSrv;//tcp服务对象

	private:
		//获取可以发送数据的socket
		SOCKET GetSendSocket();

	public:
		CTcpConnection(SOCKET localSocket, SOCKET peerSocket = NULL, CTcpService* pSrv = NULL);
		~CTcpConnection();

		// 湖区本地socket
		SOCKET GetLocalSocket();

		//获取对端socket
		SOCKET GetPeerSocket();

		//************************************
		// Method:    发送数据(同步)
		// Returns:   是否成功
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		// Parameter: 实际发送长度
		//************************************
		bool SendData(BYTE buf[], int len, int* actualLen = NULL);

		//************************************
		// Method:    接收到对端数据事件处理
		// Parameter: socket接收数据
		//************************************
		void OnRecvPeerData(SocketRecvData data);

		//************************************
		// Method:    对端关闭事件处理
		// Parameter: 对端socket
		//************************************
		void OnPeerClose(SOCKET peer);
	};
}