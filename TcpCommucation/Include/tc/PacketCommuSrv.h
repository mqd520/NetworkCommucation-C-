#pragma once
#include "Include/tc/TcpService.h"
#include "Include/tc/MemoryStream.h"

namespace tc
{
	// 基于包的通信服务
	class PacketCommuSrv : public TcpService
	{
	public:
		PacketCommuSrv(string ip = "", int port = 0);

	protected:
		MemoryStream ms;			// 内存流对象

	protected:
		//************************************
		// Method:    收到tcp事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnRecvTcpEvent(TcpEvt* pEvt) override;

		//************************************
		// Method:    连接服务端完成事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnConnectCpl(TcpEvt* pEvt);

		//************************************
		// Method:    连接断开事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnConnDiconnect(TcpEvt* pEvt);

		//************************************
		// Method:    收到新连接事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnRecvConnection(TcpEvt* pEvt);

		//************************************
		// Method:    收到对端数据事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnRecvPeerData(TcpEvt* pEvt);

		//************************************
		// Method:    处理接收缓冲区数据
		// Parameter: pBuf:		缓冲区
		// Parameter: len:		缓冲区长度
		// Parameter: clientId:	客户端id
		//************************************
		virtual void ProcessRecvBuf(BYTE* pBuf, int len, int clientId = 0);

		//************************************
		// Method:    解析包缓冲区
		//************************************
		virtual void ParsePacketBuf(vector<PacketData>& vec);
	};
}