#pragma once
#include "SocketAPI.h"

namespace NetworkCommunication
{
	//tcp动作
	class CTcpAction
	{
	protected:
		CSocketAPI m_socketAPI;//socket api
		SOCKET m_localSocket;//本地socket,服务端socket或者客户端socket
		SOCKET m_socket;//附属的socket,具体作用由派生类决定

	public:
		CTcpAction(SOCKET local = NULL, SOCKET socket = NULL);
		~CTcpAction();

		//获取tcp动作类型
		virtual int GetActionType();

		//获取本地socket
		SOCKET GetLocalSocket();
	};
}