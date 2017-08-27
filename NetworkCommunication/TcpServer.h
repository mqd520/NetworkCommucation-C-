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
		CSocketAPI m_socketAPI;//socket管理对象
		bool m_bListening;//是否正在监听
		ServerSocket m_socketData;//服务端socket数据
		vector<char*> m_vecAllowIP;//允许的客户端IP

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
		// Method:    增加一个允许IP
		// Parameter: ip
		//************************************
		void AddAllowIP(char* ip);

		//************************************
		// Method:    移除指定的允许IP
		// Parameter: ip
		//************************************
		void RemoveAllowIP(char* ip);

		//************************************
		// Method:    清除所有允许IP,表示允许所有IP
		//************************************
		void ClearAllowIP();

		//************************************
		// Method:    指定IP是否被允许
		// Parameter: ip
		//************************************
		bool IsAllow(char* ip);

		//************************************
		// Method:    开始监听
		// Returns:   是否成功
		//************************************
		bool Listen();

		//************************************
		// Method:    获取服务端socket数据
		//************************************
		ServerSocket GetServerSocketData();
	};
}