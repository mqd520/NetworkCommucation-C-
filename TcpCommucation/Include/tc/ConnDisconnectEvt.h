#pragma once
#include "TcpEvt.h"

namespace tc
{
	// 连接断开事件
	class ConnDisconnectEvt : public TcpEvt
	{
	public:
		ConnDisconnectEvt(TcpService* pSrv, SOCKET sendrecv = NULL);
		~ConnDisconnectEvt();

	private:
		string strIP;	// 对端IP
		int nPort;		// 对端端口

	public:
		//************************************
		// Method:    获取断开原因
		//************************************
		int GetReason();
		
		//************************************
		// Method:    获取对端ip
		//************************************
		string GetPeerIp();

		//************************************
		// Method:    获取对端端口
		//************************************
		int GetPeerPort();
	};
}