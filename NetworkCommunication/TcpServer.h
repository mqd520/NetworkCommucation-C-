#pragma once
#include "SocketAPI.h"
#include "TcpConnectionMgr.h"
#include "Def.h"
#include <vector>

using namespace std;

namespace NetworkCommunication
{
	//tcp服务端
	class CTcpServer : public CTcpService
	{
	protected:
		CSocketAPI m_socketAPI;//socket管理对象
		bool m_bListening;//是否正在监听
		vector<TCHAR*> m_vecAllowIP;//允许的客户端IP
		SOCKADDR_IN m_socketAddr;//socket addr
		vector<SOCKET> m_vecClientSocket;

	public:
		CTcpServer();
		~CTcpServer();

		//************************************
		// Method:    开始监听
		// Parameter: 监听IP
		// Parameter: 监听端口
		//************************************
		bool Listen(TCHAR* ip, int port);

		//************************************
		// Method:    获取服务端socket addr
		//************************************
		SOCKADDR_IN GetServerSocketAddr();

		//************************************
		// Method:    增加一个允许IP
		// Parameter: ip
		//************************************
		void AddAllowIP(TCHAR* ip);

		//************************************
		// Method:    移除指定的允许IP
		// Parameter: ip
		//************************************
		void RemoveAllowIP(TCHAR* ip);

		//************************************
		// Method:    清除所有允许IP,表示允许所有IP
		//************************************
		void ClearAllowIP();

		//************************************
		// Method:    指定IP是否被允许
		// Parameter: ip
		//************************************
		bool IsAllow(TCHAR* ip);
	};
}