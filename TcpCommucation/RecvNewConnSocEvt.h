#pragma once
#include "SocketEvt.h"

namespace tc
{
	// 收到新连接socket事件
	class RecvNewConnSocEvt : public SocketEvt
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: server:	服务端socket
		// Parameter: clients:	接收到的新客户端socket集合
		//************************************
		RecvNewConnSocEvt(SOCKET server, vector<SOCKET>& clients);
		~RecvNewConnSocEvt();

	private:
		SOCKET server;				// 服务端的socket
		vector<SOCKET> vecClients;	// 接收到的新客户端socket集合

	public:
		SOCKET GetServerSocket() const;

		vector<SOCKET> GetClients();
	};
}