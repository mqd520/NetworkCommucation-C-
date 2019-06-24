#pragma once
#include <string>
#include "TcpEvt.h"

using namespace std;

namespace tc
{
	// 收到新连接事件
	class RecvNewConnEvt : public TcpEvt
	{
	private:
		string strClientIP;	// 客户端IP
		int nClientPort;	// 客户端端口

	public:
		RecvNewConnEvt(TcpService* pSrv, SOCKET client);
		~RecvNewConnEvt();

		//************************************
		// Method:    获取客户端IP
		//************************************
		string GetClientIP();

		//************************************
		// Method:    获取客户端端口
		//************************************
		int GetClientPort();
	};
}