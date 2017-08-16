#pragma once

#include "SocketAPI.h"
#include "TcpConnectionMgr.h"
#include "Thread.h"
#include "NetCommuMgr.h"
#include "Def.h"
#include "TcpServer.h"

namespace NetworkCommunication
{
	//tcp服务端
	class CTcpServer : public CTcpService
	{
	protected:
		CSocketAPI m_socketMgr;//socket管理对象
		char m_strServerIP[20];//服务端IP
		int m_nServerPort;//服务端端口
		bool m_bInited;//是否已初始化
		SOCKET m_serverSocket;
		bool m_bListening;//是否正在监听
		ServerSocketData m_socketData;//服务端socket数据

	public:
		CTcpServer();
		~CTcpServer();

		//************************************
		// Method:    初始化
		// Parameter: ip
		// Parameter: 端口
		//************************************
		void Init(char* ip, int port);

		//************************************
		// Method:    开始监听
		// Returns:   是否成功
		//************************************
		bool Listen();

		//************************************
		// Method:    获取服务端socket数据
		//************************************
		ServerSocketData GetServerSocketData();

		void OnRecvNewConnection(ServerSocketData server, PeerSocketData client);

		void SendData(SOCKET client, BYTE buf[], int len);
	};
}