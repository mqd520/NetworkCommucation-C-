#pragma once
#include "TcpService.h"
#include "Def.h"
#include <vector>

using namespace std;

namespace tc
{
	// tcp服务端类
	class TcpServer : public TcpService
	{
	public:
		TcpServer(string ip = "", int port = 0);
		virtual ~TcpServer();

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
		// Method:    收到新连接事件处理
		// Parameter: pEvt: tcp事件
		//************************************
		virtual void OnRecvNewConnection(RecvNewConnEvt* pEvt) override;

	public:
		//************************************
		// Method:    设置监听信息
		//************************************
		virtual void SetListenInfo(string ip, int port);

		//************************************
		// Method:    开始监听
		//************************************
		virtual bool Listen();

		//************************************
		// Method:    向对端发送数据
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		//************************************
		virtual void Send(int clientId, BYTE* pBuf, int len);

		//************************************
		// Method:    关闭指定客户端
		// Parameter: clientId:	客户端SOCKET
		// Parameter: b:	是否产生连接断开事件, 默认: true
		//************************************
		virtual void CloseClient(int clientId, bool b = true);

		//************************************
		// Method:    关闭Lisetn
		//************************************
		virtual void CloseListen();

		//************************************
		// Method:    退出
		//************************************
		virtual void Exit() override;

		//************************************
		// Method:    获取对端ip
		// Parameter: client id
		//************************************
		virtual string GetPeerIp(int clientId);

		//************************************
		// Method:    获取对端ip
		// Parameter: client id
		//************************************
		virtual int GetPeerPort(int clientId);

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