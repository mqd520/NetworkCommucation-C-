#pragma once
#include "PacketHeadBase.h"
#include "MemoryStream.h"
#include "TcpEvt.h"

namespace tc
{
	// 基于包的通信服务
	class PacketCommuSrv
	{
	public:
		PacketCommuSrv(const int nHeadLen, PacketHeadBase header);

	protected:
		const int nHeadLen;			// 包头长度
		PacketHeadBase header;
		MemoryStream ms;			// 内存流对象

	protected:
		//************************************
		// Method:    收到tcp事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnRecvTcpEvent(TcpEvt* pEvt);

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

		//************************************
		// Method:    处理原始包缓冲区
		// Returns:   是否处理成功
		// Parameter: header:	包头
		// Parameter: pBuf:		缓冲区
		// Parameter: len:		缓冲区长度
		//************************************
		virtual bool ProcessOriginPckBuf(PacketHeadBase& header, BYTE* pBuf, int len);

		//************************************
		// Method:    预处理处理包
		// Parameter: data:	包数据
		//************************************
		virtual void PreProcessPck(PacketData& data);

		//************************************
		// Method:    处理包事件处理程序
		// Parameter: data:	包数据
		//************************************
		virtual void OnProcessPck(PacketData& data);
	};
}