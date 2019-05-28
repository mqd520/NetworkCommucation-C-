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
		bool bRecvConn;		// 是否接受新连接

	public:
		RecvNewConnEvt(TcpService* pSrv, SOCKET client);
		~RecvNewConnEvt();

		//************************************
		// Method:    拒绝新连接
		//************************************
		void Refuse();

		//************************************
		// Method:    是否接受新连接
		//************************************
		bool IsRecv();

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