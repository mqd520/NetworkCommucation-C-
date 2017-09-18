#pragma once
#include "TcpAction.h"
#include "Def.h"

namespace NetworkCommunication
{
	//收到对端数据动作
	class CRecvPeerDataAction : public CTcpAction
	{
	private:
		BYTE* m_pBuf;//接收到的数据缓冲区指针
		int m_nLen;//数据长度

	public:
		CRecvPeerDataAction(SOCKET recv, BYTE buf[], int len);
		~CRecvPeerDataAction();

		//************************************
		// Method:    获取tcp动作类型
		//************************************
		int GetActionType();

		//************************************
		// Method:    获取数据长度
		//************************************
		int GetLen();

		//************************************
		// Method:    获取数据缓冲区指针
		//************************************
		BYTE* GetBuf();
	};
}