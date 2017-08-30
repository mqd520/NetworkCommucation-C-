#pragma once
#include "TcpServer.h"
#include <vector>
#include "Def.h"

using namespace std;

namespace NetworkCommunication
{
	//tcp server 管理
	class CTcpServerMgr
	{
	private:
		vector<CTcpServer*> m_vecTcpServer;//tcp server对象集合

	public:
		CTcpServerMgr();
		~CTcpServerMgr();

		//************************************
		// Method:    增加一个tcp server对象
		//************************************
		void Push(CTcpServer* tcpserver);

		//************************************
		// Method:    获取指定服务端socket的tcp server对象
		// Parameter: 服务端socket
		//************************************
		CTcpServer* GetTcpServerByServerSocket(SOCKET server);
	};
}