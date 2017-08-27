#pragma once
#include "TcpAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	//收到对端数据动作
	class CRecvPeerDataAction : public CTcpAction
	{
	private:
		PeerData* m_pRecvData;//接收到的对端数据

	public:
		CRecvPeerDataAction(PeerData* pData);
		~CRecvPeerDataAction();

		//************************************
		// Method:    获取tcp动作类型
		//************************************
		int GetActionType();

		//************************************
		// Method:    获取接收到的对端数据
		//************************************
		PeerData* GetPeerData();
	};
}