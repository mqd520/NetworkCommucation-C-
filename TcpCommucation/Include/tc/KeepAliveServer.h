#pragma once
#include "KeepAliveSrv.h"

namespace tc
{
	// keepAliveServer
	class KeepAliveServer : public KeepAliveSrv
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: int clientId
		// Parameter: int nRecvTimespan	服务端接收客户端心跳包的间隔时间
		// Parameter: int nTimeout:		丢失心跳包超时时间
		// Parameter: int nMaxCount:	允许丢失最大次数
		// Parameter: void * pObj1
		// Parameter: void * pObj2
		//************************************
		KeepAliveServer(
			int clientId = 0, int nRecvTimespan = TC_KeepAlive_RecvTimespan, 
			int nTimeout = TC_KeepAlive_Timeout, int nMaxCount = TC_KeepAlive_MaxMissCount,
			void* pObj1 = NULL, void* pObj2 = NULL);
		virtual ~KeepAliveServer();

	protected:
		const int nRecvTimespan;	// 服务端接收客户端心跳包的间隔时间
		DWORD dwLastRecv;			// 上次接收时间(精确到毫秒)

	protected:
		//************************************
		// Method:    心跳包事件处理
		//************************************
		virtual void OnKeepAlive() override;
	};
}