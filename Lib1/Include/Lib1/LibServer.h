#pragma once
#include "tc/TcpServer.h"
#include "../../LibSrv1.h"
#include "../../PacketServerClientMgr.h"

namespace lib1
{
	// 基于包的通信服务服务器端
	class LibServer : public TcpServer, public LibSrv1
	{
	public:
		//************************************
		// Method:    构造函数
		// Parameter: type:	服务类型
		// Parameter: bNeedVertify:	连接成功后是否需要发送密码
		// Parameter: string ip
		// Parameter: int port
		//************************************
		LibServer(EServiceType type = EServiceType::None, bool bNeedVertify = true, string ip = "", int port = 0);
		virtual ~LibServer();

	protected:
		int nClientId;						// client id
		PacketServerClientMgr clientMgr;	// client mgr
		bool bNeedVertify;					// 是否需要验证客户端密码

	protected:
		//************************************
		// Method:    收到tcp事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnRecvTcpEvent(TcpEvt* pEvt) override;

		//************************************
		// Method:    收到新连接事件处理
		// Parameter: tcp事件
		//************************************
		virtual void OnRecvConnection(TcpEvt* pEvt) override;

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
		// Method:    登录服务端请求包事件处理程序
		// Parameter: data:	包数据
		//************************************
		virtual void OnLoginSrvRequest(PacketData& data) override;

		//************************************
		// Method:    心跳包事件处理程序
		// Parameter: data:	包数据
		//************************************
		virtual void OnKeepAlive(PacketData& data) override;

	public:
		//************************************
		// Method:    发包
		//************************************
		virtual void SendPck(PacketBase& pck, int clientId);

		//************************************
		// Method:    关闭客户端
		//************************************
		virtual void CloseClient(int clientId, bool b = true) override;

		//************************************
		// Method:    退出
		//************************************
		virtual void Exit() override;

		//************************************
		// Method:    丢失心跳包事件处理程序
		// Parameter: clientId:	client id
		// Parameter: count: 连续丢失次数
		//************************************
		virtual void OnMissKeepAlive(int clientId, int count);
	};
}