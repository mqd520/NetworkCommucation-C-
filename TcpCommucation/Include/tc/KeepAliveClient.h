#pragma once
#include "KeepAliveSrv.h"
#include "Timer.h"

namespace tc
{
	// 心跳包客户端服务
	class KeepAliveClient : public KeepAliveSrv
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: int nTimespan:	发送间隔时间
		// Parameter: int nTimeout:		丢失心跳包超时时间
		// Parameter: int nMaxCount:	允许丢失最大次数
		// Parameter: void * pObj1
		// Parameter: void * pObj2
		//************************************
		KeepAliveClient(
			int nTimespan = TC_KeepAlive_Timespan, int nTimeout = TC_KeepAlive_Timeout,
			int nMaxCount = TC_KeepAlive_MaxMissCount, void* pObj1 = NULL, void* pObj2 = NULL);
		virtual ~KeepAliveClient();

	protected:
		const int nTimespan;	// 发送间隔时间
		Timer tTimespan;		// 发送心跳包定时器

	protected:
		//************************************
		// Method:    定时器事件处理
		// Parameter: 定时器对象
		// Parameter: 次数
		// Parameter: void * pParam1
		// Parameter: void * pParam2
		//************************************
		void OnTimerClient(Timer* pTimer, int count, void* pParam1 = NULL, void* pParam2 = NULL);

		//************************************
		// Method:    心跳包事件处理
		//************************************
		virtual void OnKeepAlive() override;

		//************************************
		// Method:    丢失心跳包事件处理
		// Parameter: count:	连续丢失次数
		// Parameter: b:	是否已超过允许最大次数
		//************************************
		virtual void OnMissKeepAlive(int count, bool b = true) override;

		//************************************
		// Method:    开始心跳包
		//************************************
		virtual void StartKeepAlive() override;

		//************************************
		// Method:    关闭心跳包
		//************************************
		virtual void CloseKeepAlive() override;

		//************************************
		// Method:    退出
		//************************************
		virtual void Exit() override;
	};
}