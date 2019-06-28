#pragma once
#include "tc/TcpClient.h"
#include "../../LibSrv1.h"
#include "tc/Timer.h"

using namespace tc;

namespace lib1
{
	// 基于包的通信服务客户端
	class LibClient : public TcpClient, public LibSrv1
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: type:	服务类型
		// Parameter: bNeedVertify:	连接成功后是否需要发送密码
		// Parameter: string ip
		// Parameter: int port
		//************************************
		LibClient(EServiceType type = EServiceType::None, bool bNeedVertify = true, string ip = "", int port = 0);
		virtual ~LibClient();

	protected:
		bool bNeedVertify;		// 是否需要发送密码
		Timer t1;				// 丢失心跳包时间间隔
		Timer t2;				// 发送心跳包时间间隔

	private:
		friend class TimerCallback_PacketClient;

		//************************************
		// Method:    发送密码
		//************************************
		void SendPwd();

		//************************************
		// Method:    发送登录服务端请求包
		//************************************
		void SendLoginSrvRequest();

		//************************************
		// Method:    发送心跳包
		//************************************
		void SendKeepAlive();

		void OnTimerKeepAlive(Timer* pTimer, int count, void* pParam1 = NULL, void* pParam2 = NULL);

	protected:
		//************************************
		// Method:    收到tcp事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnRecvTcpEvent(TcpEvt* pEvt) override;

		//************************************
		// Method:    连接服务端完成事件处理
		//************************************
		virtual void OnConnectCpl(TcpEvt* pEvt) override;

		//************************************
		// Method:    连接断开事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnConnDiconnect(TcpEvt* pEvt) override;

		//************************************
		// Method:    收到对端数据事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnRecvPeerData(TcpEvt* pEvt) override;

		//************************************
		// Method:    登录服务端结果包事件处理程序
		// Parameter: data:	包数据
		//************************************
		virtual void OnLoginSrvResult(PacketData& data) override;

		//************************************
		// Method:    心跳包事件处理程序
		// Parameter: data:	包数据
		//************************************
		virtual void OnKeepAlive(PacketData& data) override;

	public:
		//************************************
		// Method:    发包
		// Parameter: PacketBase & pck
		//************************************
		virtual void SendPck(PacketBase& pck);

		//************************************
		// Method:    退出
		//************************************
		virtual void Exit() override;
	};

	class TimerCallback_PacketClient
	{
	public:
		static void OnTimer(Timer* pTimer, int count, void* pParam1 = NULL, void* pParam2 = NULL);
	};
}