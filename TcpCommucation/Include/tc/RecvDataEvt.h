#pragma once
#include "TcpEvt.h"

namespace tc
{
	// 收到数据事件
	class RecvDataEvt : public TcpEvt
	{
	private:
		BYTE* pBuf;		// 收到的数据缓冲区指针
		int nLen;		// 数据缓冲区长度

	public:
		//************************************
		// Method:    构造函数
		// Parameter: 关联的tcp服务对象
		// Parameter: 关联的用于接收数据的socket
		//************************************
		RecvDataEvt(TcpService* pSrv, SOCKET recv, BYTE* pBuf, int len);
		~RecvDataEvt();

		//************************************
		// Method:    获取接收缓冲区
		//************************************
		BYTE* GetRecvBuf();

		//************************************
		// Method:    获取接收缓冲区长度
		//************************************
		int GetBufLen();
	};
}