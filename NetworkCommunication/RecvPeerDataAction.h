#pragma once
#include "TcpAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	//收到对端数据动作
	class CRecvPeerDataAction : public CTcpAction
	{
	private:
		SocketRecvData m_recvData;

	public:
		CRecvPeerDataAction(SocketRecvData data);
		~CRecvPeerDataAction();

		//获取tcp动作类型
		int GetActionType();

		BYTE* GetBuf();
	};
}