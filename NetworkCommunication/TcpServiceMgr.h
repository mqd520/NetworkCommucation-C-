#pragma once
#include "TcpService.h"
#include "Def.h"
#include "AcceptNewConnAction.h"
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
		CThread* m_thread;
		vector<CTcpService*> m_vecTcpService;//tcp服务对象集合
		queue<CTcpAction*> m_tcpAction;//tcp动作队列

	private:
		~CTcpServiceMgr();

		//处理tcp动作队列
		void ProcessTcpAction();

		//************************************
		// Method:    处理接收到新客户端连接动作
		// Parameter: tcp动作
		//************************************
		void ProcessAcceptNewConnAction(CAcceptNewConnAction* pAction);

		//************************************
		// Method:    处理对端主动关闭动作
		// Parameter: tcp动作
		//************************************
		void ProcessPeerCloseAction(CPeerCloseAction* pAction);

		//************************************
		// Method:    处理收到对端socket数据动作
		// Parameter: tcp动作
		//************************************
		void ProcessRecvPeerDataAction(CRecvPeerDataAction* pAction);

		//************************************
		// Method:    处理发送对端socket数据结果动作
		// Parameter: tcp动作
		//************************************
		void ProcessSendPeerDataResultAction(CSendPeerDataResultAction* pAction);

	public:
		CTcpServiceMgr();

		//启动tcp动作线程
		void Run();

		//线程入口
		void ThreadEntry();

		//增加一个tcp服务对象
		void PushTcpService(CTcpService* srv);

		//************************************
		// Method:    加入一个tcp动作
		// Parameter: tcp动作
		//************************************
		void PushTcpAction(CTcpAction* pAction);

		//************************************
		// Method:    获取指定本地socket的tcp服务对象
		// Return:	  tcp连接对象
		// Parameter: 本地socket
		//************************************
		CTcpService* GetTcpSrvByLocalSocket(SOCKET local);
	};
}