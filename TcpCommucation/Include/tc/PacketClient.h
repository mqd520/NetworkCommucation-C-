#pragma once
#include "PacketCommuSrv.h"
#include "TcpClient.h"

namespace tc
{
	// 基于包的通信服务客户端
	class PacketClient : public TcpClient, public PacketCommuSrv
	{
	public:
		PacketClient(string ip = "", int port = 0);

	protected:
		//************************************
		// Method:    收到tcp事件处理
		// Parameter: pEvt: tcp事件
		//************************************
		virtual void OnTcpEvt(TcpEvt* pEvt) override;
	};
}