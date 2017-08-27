#pragma once
#include "SocketAPI.h"
#include <queue>
#include "Thread.h"
#include "Def.h"
#include "TcpAction.h"
#include "RecvNewConnAction.h"
#include "RecvPeerDataAction.h"
#include "PeerCloseAction.h"
#include "SendPeerDataResultAction.h"
#include "NetErrorAction.h"
#include "AsyncSendDataAction.h"
#include "RefuseNewConnAction.h"

using namespace std;

namespace NetworkCommunication
{
	//处理tcp动作
	class CTcp
	{
	private:
		queue<CTcpAction*> m_quTcpAction;//tcp动作队列
		CThread* m_threadAccept;//处理新socket连接的线程
		CSocketAPI m_socketAPI;//socket api

	private:
		//************************************
		// Method:    处理tcp动作队列
		//************************************
		void ProcessQueue();

		//************************************
		// Method:    处理收到新连接动作
		// Parameter: 收到新连接动作
		//************************************
		void ProcessRecvNewConnection(CRecvNewConnAction* pAction);

		//************************************
		// Method:    处理收到对端数据动作
		// Parameter: 收到对端数据动作
		//************************************
		void ProcessRecvPeerData(CRecvPeerDataAction* pAction);

		//************************************
		// Method:    处理对端主动关闭连接动作
		// Parameter: 对端主动关闭连接动作
		//************************************
		void ProcessPeerCloseConn(CPeerCloseAction* pAction);

		//************************************
		// Method:    处理异步发送数据动作
		// Parameter: 异步发送数据动作
		//************************************
		void ProcessAsyncSendData(CAsyncSendDataAction* pAction);

		//************************************
		// Method:    处理发送对端数据结果动作
		// Parameter: 发送对端数据结果动作
		//************************************
		void ProcessSendPeerDataResult(CSendPeerDataResultAction* pAction);

		//************************************
		// Method:    处理网络错误
		// Parameter: 网络错误动作
		//************************************
		void ProcessNetError(CNetErrorAction* pAction);

		//************************************
		// Method:    处理拒绝新客户端连接动作
		// Parameter: 拒绝新客户端连接动作
		//************************************
		void ProcessRefuseNewConn(CRefuseNewConnAction* pAction);

	public:
		CTcp();
		~CTcp();

		//************************************
		// Method:    运行处理新连接线程
		//************************************
		void Run();

		//************************************
		// Method:    accept线程入口点
		//************************************
		void ThreadEntry();

		//************************************
		// Method:    增加一个tcp动作
		// Parameter: tcp动作
		//************************************
		void PushTcpAction(CTcpAction* pAction);
	};
}
