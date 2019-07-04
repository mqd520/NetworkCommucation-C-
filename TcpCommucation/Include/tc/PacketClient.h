#pragma once
#include "TcpClient.h"

namespace tc
{
	// 基于包的通信服务客户端
	class PacketClient : public TcpClient
	{
	public:
		PacketClient(string ip = "", int port = 0);

	//protected:
	//	//************************************
	//	// Method:    收到tcp事件处理
	//	// Parameter: pEvt: tcp事件
	//	//************************************
	//	virtual void OnTcpEvt(TcpEvt* pEvt) override;

	//public:
	//	//************************************
	//	// Method:    发包
	//	// Parameter: Packet & pck:	包数据
	//	//************************************
	//	virtual void SendPck(Packet& pck);
	};
}