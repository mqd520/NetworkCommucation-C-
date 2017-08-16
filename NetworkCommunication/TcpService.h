#pragma once
#include "Thread.h"
#include "Def.h"
#include "SocketAPI.h"

namespace NetworkCommunication
{
	///tcp服务
	class CTcpService
	{
	private:
		int m_nSrvType;

	private:
		void OnRecvNewConnection();

	public:
		~CTcpService();
		CTcpService(int srvType);

		// 获取tcp服务类型
		int GetSrvType();

		//************************************
		// Method:    获取服务端socket数据
		//************************************
		virtual ServerSocketData GetServerSocketData();

		//************************************
		// Method:    接收到新的客户端连接
		// Parameter: 服务端socket	
		// Parameter: 对端socket数据
		//************************************
		virtual void OnRecvNewConnection(ServerSocketData server, PeerSocketData client);

		virtual void OnPeerCloseSocket(PeerSocketData data);
	};
}