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

	protected:
		//************************************
		// Method:    指定IP是否被允许
		// Parameter: ip
		//************************************
		bool IsAllow(TCHAR* ip);

		//************************************
		// Method:    收到tcp事件处理
		// Parameter: tcp事件
		//************************************
		void OnRecvTcpEvent(CTcpEvt* pEvent);

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
		// Method:    向对端发送数据
		// Returns:   是否成功
		// Parameter: socket
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		// Parameter: 是否异步,默认异步发送
		// Parameter: 实际发送字节长度
		//************************************
		bool Send(SOCKET socket, BYTE* pBuf, int len, bool asyncs = true, int* actualLen = NULL);

		//************************************
		// Method:    关闭指定客户端
		// Parameter: 客户端SOCKET
		//************************************
		void CloseClient(SOCKET client);

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
	};
}