#pragma once
#include "TcpAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	//收到对端数据动作
	class CRecvPeerDataAction : public CTcpAction
	{
	private:
		PeerData* m_recvData;

	public:
		CRecvPeerDataAction(PeerData* pData);
		~CRecvPeerDataAction();

		//获取tcp动作类型
		int GetActionType();

		//获取接收对端数据
		PeerData* GetPeerData();
	};
}