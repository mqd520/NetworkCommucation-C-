#pragma once
#include "Def.h"
#include "IGPacketSrv.h"
#include "SessionMgr.h"

#include "tc/TcpServer.h"

namespace pck
{
	// IGPacketSrvServer 
	class IGPacketSrvServer : public TcpServer, public IGPacketSrv
	{
	public:
		IGPacketSrvServer(
			string ip = "", int port = 0,
			EServerType localType = EServerType::None,
			bool bRecvPwd = true);
		virtual ~IGPacketSrvServer();

	protected:
		bool bRecvPwd;				// 是否需要接受客户端密码
		int nCurClientId;			// 当前会话的客户端Id
		SessionMgr sessionMgr;		// session mgr

	protected:
		friend class ServerSession;

		//************************************
		// Method:    收到新连接事件处理
		// Parameter: pEvt: tcp事件
		//************************************
		virtual void OnRecvNewConnection(RecvNewConnEvt* pEvt) override;

		//************************************
		// Method:    收到对端数据事件处理
		// Parameter: pEvt: tcp事件
		//************************************
		virtual void OnRecvPeerData(RecvPeerDataEvt* pEvt) override;

		//************************************
		// Method:    连接断开事件处理
		// Parameter: pEvt: tcp事件
		//************************************
		virtual void OnConnDisconnect(ConnDisconnectEvt* pEvt) override;

		//************************************
		// Method:    预处理处理包
		// Parameter: data:	包数据
		//************************************
		virtual void PreProcessPck(PacketData& data) override;

		//************************************
		// Method:    登录服务端请求事件处理
		// Parameter: data:	包数据
		//************************************
		virtual void OnLoginSrvRequest(PacketData& data);

		//************************************
		// Method:    发送登录服务端结果包
		// Parameter: int clientId
		//************************************
		virtual void SendLoginSrvResultPck(int clientId);

		//************************************
		// Method:    session关闭事件处理
		// Parameter: int clientId
		//************************************
		virtual void OnSessionClose(int clientId);
		
		//************************************
		// Method:    发送心跳包
		//************************************
		virtual void SendKeepAlive(int clientId = 0);

		//************************************
		// Method:    丢失心跳包事件处理
		// Parameter: int clientId
		// Parameter: count:	连续丢失次数
		// Parameter: b:	是否已超过允许最大次数
		//************************************
		virtual void OnMissKeepAlive(int clientId, int count, bool b = true);

	public:
		//************************************
		// Method:    发包
		// Parameter: 包数据
		// Parameter: 客户端id
		//************************************
		virtual void SendPck(Packet& pck, int clientId);

		//************************************
		// Method:    退出
		//************************************
		virtual void Exit() override;
	};
}