#pragma once
#include "Def.h"
#include "Timer.h"

namespace tc
{
	// 心跳包服务
	class KeepAliveSrv
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: int clientId
		// Parameter: nTimeout:		心跳包超时时间
		// Parameter: nMaxCount:	允许丢失心跳包最大次数
		// Parameter: pObj1:	TcpService对象
		// Parameter: pObj2:	PacketSrv对象
		//************************************
		KeepAliveSrv(int clientId = 0, int nTimeout = TC_KeepAlive_Timeout, int nMaxCount = TC_KeepAlive_MaxMissCount, void* pObj1 = NULL, void* pObj2 = NULL);
		virtual ~KeepAliveSrv();

	protected:
		const int nTimeout;		// 默认心跳包超时时间
		const int nMaxCount;	// 默认允许丢失心跳包最大次数
		void* pObj1;			// TcpService对象
		void* pObj2;			// PacketSrv对象
		int nMissCount;			// 丢失次数
		Timer tTimeout;			// 丢失心跳包定时器
		int nClientId;			// clientId
		string strPeerIp;		// ip
		int nPort;				// port

	protected:
		//************************************
		// Method:    附加PacketSrv对象
		// Parameter: void pObj1:	TcpService对象
		// Parameter: void pObj2:	PacketSrv对象
		//************************************
		virtual void AttachObj(void* pObj1, void* pObj2);

		//************************************
		// Method:    获取对端ip
		//************************************
		string GetPeerIp();

		//************************************
		// Method:    获取对端port
		//************************************
		int GetPeerPort();

		//************************************
		// Method:    发送心跳包
		//************************************
		virtual void SendKeepAlive(int clientId = 0);

		//************************************
		// Method:    心跳包事件处理
		//************************************
		virtual void OnKeepAlive();

		//************************************
		// Method:    定时器事件处理
		// Parameter: 定时器对象
		// Parameter: 次数
		// Parameter: void * pParam1
		// Parameter: void * pParam2
		//************************************
		void OnTimerTimeout(Timer* pTimer, int count, void* pParam1 = NULL, void* pParam2 = NULL);

		//************************************
		// Method:    丢失心跳包事件处理
		// Parameter: count:	连续丢失次数
		// Parameter: b:	是否已超过允许最大次数
		//************************************
		virtual void OnMissKeepAlive(int count, bool b = true);

		//************************************
		// Method:    开始心跳包
		//************************************
		virtual void StartKeepAlive();

		//************************************
		// Method:    关闭心跳包
		//************************************
		virtual void CloseKeepAlive();

		//************************************
		// Method:    退出
		//************************************
		virtual void Exit();
	};
}