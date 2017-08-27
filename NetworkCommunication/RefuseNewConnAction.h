#pragma once
#include "TcpAction.h"
#include "SocketAPI.h"

namespace NetworkCommunication
{
	//拒绝客户端连接动作
	class CRefuseNewConnAction :public CTcpAction
	{
	private:
		char m_strIP[20];//对端IP
		int m_nPort;//对端端口

	public:
		//************************************
		// Method:    构造函数
		// Parameter: 服务端socket
		// Parameter: 服务端的客户端socket
		//************************************
		CRefuseNewConnAction(SOCKET server, SOCKET scSocket, char* ip, int port);
		~CRefuseNewConnAction();

		//************************************
		// Method:    获取tcp动作类型
		//************************************
		int GetActionType();

		//************************************
		// Method:    获取对端IP
		//************************************
		char* GetPeerIP();

		//************************************
		// Method:    获取对端端口
		//************************************
		int GetPeerPort();
	};
}