#pragma once

#include "tc/TcpEvt.h"
#include "tc/RecvPeerDataEvt.h"
#include "tc/ConnDisconnectEvt.h"
#include "tc/Timer.h"
#include "tc/KeepAliveServer.h"
using namespace tc;

namespace pck
{
	// server session
	class ServerSession : public KeepAliveServer
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: int clientId
		// Parameter: void* pObj:	IGPacketSrvServer对象
		// Parameter: recvPwd:	是否需要验证客户端密码
		//************************************
		ServerSession(int clientId, void* pObj, bool recvPwd = true);
		virtual ~ServerSession();

	protected:
		int nClientId;		// 客户端id
		string strIp;		// 对端ip
		int nPort;			// 对端port
		bool bRecvPwd;		// 是否需要验证客户端密码
		bool bVertified;	// 是否已验证客户端密码
		Timer tVertify;		// 验证客户端密码和登录服务端请求定时器
		void* pObj;			// IGPacketSrvServer对象

	protected:
		//************************************
		// Method:    定时器事件处理
		// Parameter: 定时器对象
		// Parameter: 次数
		// Parameter: void * pParam1
		// Parameter: void * pParam2
		//************************************
		void OnTimerVertify(Timer* pTimer, int count, void* pParam1 = NULL, void* pParam2 = NULL);

	public:
		//************************************
		// Method:    附加PacketSrv对象
		// Parameter: void pObj:	TcpService对象
		//************************************
		void AttachObj(void* pObj);

		//************************************
		// Method:    收到对端数据事件处理
		// Parameter: pEvt: tcp事件
		//************************************
		bool OnRecvPeerData(RecvPeerDataEvt* pEvt);

		//************************************
		// Method:    连接断开事件处理
		// Parameter: pEvt: tcp事件
		//************************************
		void OnConnDisconnect(ConnDisconnectEvt* pEvt);

		// Method:    登录服务端请求事件处理
		// Parameter: data:	包数据
		// Parameter: b:	验证是否通过
		//************************************
		void OnLoginSrvRequest(PacketData& data, bool b = true);

		//************************************
		// Method:    发送心跳包
		//************************************
		virtual void SendKeepAlive(int clientId = 0) override;

		//************************************
		// Method:    丢失心跳包事件处理
		// Parameter: count:	连续丢失次数
		// Parameter: b:	是否已超过允许最大次数
		//************************************
		virtual void OnMissKeepAlive(int count, bool b = true) override;

		//************************************
		// Method:    心跳包事件处理
		//************************************
		void OnRecvKeepAlive();

		//************************************
		// Method:    获取client id
		//************************************
		int GetClientId() const;

		//************************************
		// Method:    获取ip
		//************************************
		string GetIp() const;

		//************************************
		// Method:    获取port
		//************************************
		int GetPort() const;

		//************************************
		// Method:    是否已验证通过
		//************************************
		bool IsVertified();

		//************************************
		// Method:    关闭
		//************************************
		void Close();
	};
}