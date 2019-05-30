#pragma once
#include "Include/tc/SocketTool.h"
#include "../../TcpConnectionMgr.h"
#include "../../Def.h"
#include "../../TcpService.h"
#include <vector>

using namespace std;

namespace tc
{
	// tcp服务端类
	class TcpServer : public TcpService
	{
	protected:
		bool bListening;				// 是否正在监听
		vector<string> vecAllowIP;		// 允许的客户端IP
		SOCKADDR_IN socketAddr;			// socket addr

	protected:
		//************************************
		// Method:    指定IP是否被允许
		// Parameter: ip
		//************************************
		bool IsAllow(string ip);

		//************************************
		// Method:    收到tcp事件处理
		// Parameter: tcp事件
		//************************************
		void OnRecvTcpEvent(TcpEvt* pEvent);

	public:
		TcpServer(string ip = "", int port = 0);
		~TcpServer();

		//************************************
		// Method:    设置监听信息
		//************************************
		void SetListenInfo(string ip, int port);

		//************************************
		// Method:    开始监听
		//************************************
		bool Listen();

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
		void AddAllowIP(string ip);

		//************************************
		// Method:    移除指定的允许IP
		// Parameter: ip
		//************************************
		void RemoveAllowIP(string ip);

		//************************************
		// Method:    清除所有允许IP, 表示允许所有IP
		//************************************
		void ClearAllowIP();
	};
}