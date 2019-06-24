#pragma once
#include "SocketEvt.h"

namespace tc
{
	// 发送对端数据socket事件
	class SendPeerDataSocEvt : public SocketEvt
	{
	public:
		SendPeerDataSocEvt(SOCKET send, BYTE* buf, int len);
		~SendPeerDataSocEvt();

	private:
		SOCKET	send;	// 发送数据的socket
		BYTE*	pBuf;	// 发送数据缓冲区
		int		nLen;	// 发送数据缓冲区长度

	public:
		//************************************
		// Method:    获取发送数据的socket
		//************************************
		SOCKET	GetSocket();

		//************************************
		// Method:    获取发送数据的缓冲区
		//************************************
		BYTE*	GetBuf();

		//************************************
		// Method:    获取发送数据的缓冲区长度
		//************************************
		int		GetLen();
	};
}