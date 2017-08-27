#pragma once
#include "SocketAPI.h"

namespace NetworkCommunication
{
	//tcp动作
	class CTcpAction
	{
	protected:
		CSocketAPI m_socketAPI;//socket api
		SOCKET m_sendrecvSocket;//本地发送(接收)数据的socket
		SOCKET m_attachmentSocket;//附属socket,具体作用由派生类决定

	public:
		//************************************
		// Method:    构造函数
		// Parameter: 发送(接收)数据的socket
		// Parameter: 附属socket,具体作用由派生类决定
		//************************************
		CTcpAction(SOCKET sendrecv = NULL, SOCKET attachment = NULL);
		~CTcpAction();

		//************************************
		// Method:    获取tcp动作类型
		//************************************
		virtual int GetActionType();

		//************************************
		// Method:    获取发送(接收)数据的socket
		//************************************
		SOCKET GetSendRecvSocket();

		//************************************
		// Method:    获取附属socket,具体作用由派生类决定
		//************************************
		SOCKET GetAttachmentSocket();
	};
}