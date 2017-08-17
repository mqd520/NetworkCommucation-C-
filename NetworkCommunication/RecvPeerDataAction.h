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
		//************************************
		// Method:    构造函数
		// Parameter: 接收到的对端数据
		// Parameter: 本地socket
		//************************************
		CRecvPeerDataAction(SocketRecvData data, SOCKET local);
		~CRecvPeerDataAction();

		//获取tcp动作类型
		int GetActionType();

		//获取接收数据
		SocketRecvData GetRecvData();
	};
}