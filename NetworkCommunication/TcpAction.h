#pragma once
#include "SocketAPI.h"

namespace NetworkCommunication
{
	//tcp动作
	class CTcpAction
	{
	private:
		SOCKET m_local;//本地socket
		SOCKET m_peer;//对端socket

	public:
		CTcpAction(SOCKET local = NULL, SOCKET peer = NULL);
		~CTcpAction();

		//获取本地socket
		SOCKET GetLocalSocket();

		//获取对端socket
		SOCKET GetPeerSocket();

		//获取tcp动作类型
		virtual int GetActionType();
	};
}