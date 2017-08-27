#pragma once
#include "TcpAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	//异步发送数据动作
	class CAsyncSendDataAction :public CTcpAction
	{
	private:
		AsyncSendPeerData* m_pData;//发送数据

	public:
		//************************************
		// Method:    构造函数
		// Parameter: 发送的数据
		//************************************
		CAsyncSendDataAction(AsyncSendPeerData* pData);
		~CAsyncSendDataAction();

		//************************************
		// Method:    获取tcp动作类型
		//************************************
		int GetActionType();

		//************************************
		// Method:    获取发送数据
		//************************************
		AsyncSendPeerData* GetSendData();
	};
}