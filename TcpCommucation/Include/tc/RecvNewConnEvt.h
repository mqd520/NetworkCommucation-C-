#pragma once
#include <string>
#include "TcpEvt.h"

using namespace std;

namespace tc
{
	// 收到新连接事件
	class RecvNewConnEvt : public TcpEvt
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: tcp服务
		// Parameter: 客户端socket
		//************************************
		RecvNewConnEvt(TcpService* pSrv, SOCKET client);

	private:
		bool bIsAllow;		// whether allow by the server

	public:
		//************************************
		// Method:    Is Allow
		//************************************
		bool IsAllow();

		//************************************
		// Method:    Allow the new connection
		//************************************
		void Allow();
	};
}