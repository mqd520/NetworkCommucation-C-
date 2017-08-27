#pragma once
#include "TcpAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	//发送对端数据结果动作
	class CSendPeerDataResultAction : public CTcpAction
	{
	private:
		SendPeerDataResult* m_pResult;//发送结果

	public:
		//************************************
		// Method:    构造函数
		// Parameter: 发送数据结果
		// Parameter: 发送数据的socket
		//************************************
		CSendPeerDataResultAction(SendPeerDataResult* data, SOCKET send);
		~CSendPeerDataResultAction();

		//************************************
		// Method:    获取tcp动作类型
		//************************************
		int GetActionType();

		//************************************
		// Method:    获取结果数据
		//************************************
		SendPeerDataResult* GetResult();
	};
}