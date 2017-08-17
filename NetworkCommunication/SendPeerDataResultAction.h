#pragma once
#include "TcpAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	//发送对端数据结果动作
	class CSendPeerDataResultAction : public CTcpAction
	{
	private:
		SendPeerDataResult m_result;//发送结果

	public:
		CSendPeerDataResultAction(SendPeerDataResult data, SOCKET local);
		~CSendPeerDataResultAction();

		//获取tcp动作类型
		int GetActionType();

		//获取结果数据
		SendPeerDataResult GetResult();
	};
}