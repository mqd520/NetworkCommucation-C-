#pragma once
#include "SocketEvt.h"

namespace tc
{
	// 收到对端数据socket事件
	class RecvPeerDataSocEvt : public SocketEvt
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: recv:		接收数据的socket
		// Parameter: pBuf:		接收数据的缓冲区指针
		// Parameter: len:		接收数据的缓冲区指针长度
		//************************************
		RecvPeerDataSocEvt(SOCKET recv, BYTE* pBuf, int len);
		~RecvPeerDataSocEvt();

	private:
		SOCKET	recv;		// 接收数据的socket
		BYTE*	pBuf;		// 接收数据的缓冲区指针
		int		len;		// 接收数据的缓冲区指针长度

	public:
		//************************************
		// Method:    获取socket
		//************************************
		SOCKET GetSocket() const;

		//************************************
		// Method:    获取数据缓冲区指针
		//************************************
		BYTE* GetBuf() const;

		//************************************
		// Method:    获取数据缓冲区指针长度
		//************************************
		int GetLen() const;
	};
}