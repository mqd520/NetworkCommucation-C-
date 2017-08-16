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
		// Method:    接收到新的客户端连接事件处理
		// Parameter: 服务端socket	
		// Parameter: 对端socket数据
		//************************************
		virtual void OnRecvNewConnection(ServerSocketData server, PeerSocketData client);

		//************************************
		// Method:    对端主动关闭事件处理
		// Parameter: 服务端socket	
		// Parameter: 对端socket数据
		//************************************
		virtual void OnPeerCloseSocket(PeerSocketData data);

		//************************************
		// Method:    接收到对端socket数据事件处理(调用放释放缓冲区指针)
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区字节长度
		// Parameter: 对端socket数据
		// Return:	  是否已处理完毕
		//************************************
		virtual bool OnRecvPeerData(BYTE buf[], int len, PeerSocketData data);
	};
}