#pragma once
#include "Def.h"
#include "IGPacketSrv.h"

#include "tc/PacketClient.h"
#include "tc/KeepAliveClient.h"
using namespace tc;

namespace pck
{
	// ig包通信服务
	class IGPacketSrvClient : public PacketClient, public IGPacketSrv, public KeepAliveClient
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: EServerType localType:	本地服务器类型
		// Parameter: EServerType peerType:		对端服务器类型
		// Parameter: string ip:	ip
		// Parameter: int port:		port
		// Parameter: bool bSendPwd:	是否需要向服务端发送密码
		//************************************
		IGPacketSrvClient(
			EServerType localType = EServerType::None, EServerType peerType = EServerType::None,
			string ip = "", int port = 0,
			bool bSendPwd = true);
		~IGPacketSrvClient();

	protected:
		bool bSendPwd;			// 是否需要向服务端发送密码

	protected:
		//************************************
		// Method:    连接服务端完成事件处理
		// Parameter: pEvt: tcp事件
		//************************************
		virtual void OnConnectSrvCpl(ConnectSrvCplEvt* pEvt) override;

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
		// Method:    向服务端发送密码
		//************************************
		virtual void SendPwd();

		//************************************
		// Method:    发送登录服务端请求包
		//************************************
		virtual void SendLoginSrvRequestPck();

		//************************************
		// Method:    登录服务成功事件处理
		//************************************
		virtual void OnLoginSrvSuccess();

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

	public:
		//************************************
		// Method:    发包
		// Parameter: Packet & pck
		//************************************
		virtual void SendPck(Packet& pck);
	};
}