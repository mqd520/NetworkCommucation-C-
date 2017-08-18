#pragma once
#include "TcpService.h"
#include "Def.h"
#include "RecvNewConnAction.h"
#include "PeerCloseAction.h"
#include "RecvPeerDataAction.h"
#include "SendPeerDataResultAction.h"

#include <queue>
using namespace std;

namespace NetworkCommunication
{
	//tcp服务对象管理
	class CTcpServiceMgr
	{
	private:
		vector<CTcpService*> m_vecTcpService;//tcp服务对象集合

	public:
		CTcpServiceMgr();
		~CTcpServiceMgr();

		//增加一个tcp服务对象
		void PushTcpService(CTcpService* srv);

		//************************************
		// Method:    获取指定本地socket的tcp服务对象
		// Return:	  tcp连接对象
		// Parameter: 本地socket
		//************************************
		CTcpService* GetTcpSrvByLocalSocket(SOCKET local);

		//************************************
		// Method:    收到新连接事件处理
		// Parameter: tcp动作
		//************************************
		void OnRecvNewConnection(CRecvNewConnAction* pAction);

		//************************************
		// Method:    收到对端数据事件处理
		// Parameter: tcp动作
		//************************************
		//void OnRecvPeerData(CRecvPeerDataAction* pAction);

		//************************************
		// Method:    对端主动关闭事件处理
		// Parameter: tcp动作
		//************************************
		void OnPeerClose(CPeerCloseAction* pAction);

		//************************************
		// Method:    向对端发送数据完成事件处理
		// Parameter: tcp动作
		//************************************
		void OnSendPeerDataCompleted(CSendPeerDataResultAction* pAction);
	};
}