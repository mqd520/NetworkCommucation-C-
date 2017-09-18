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
#include "SocketExceptAction.h"

using namespace std;

namespace NetworkCommunication
{
	//tcp类,处理tcp各种事件
	class CTcp : public CThreadEntry
	{
	private:
		queue<CTcpAction*> m_queueTcpAction;//tcp动作队列
		CThread* m_thread;//线程对象
		CSocketAPI m_socketAPI;//socket api

	private:
		//************************************
		// Method:    处理tcp动作
		//************************************
		void ProcessTcpAction();

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
		// Method:    处理socket异常
		// Parameter: socket异常动作
		//************************************
		void ProcessSocketExcept(CSocketExcept* pAction);

	public:
		CTcp();
		~CTcp();

		//************************************
		// Method:    运行线程
		//************************************
		void Run();

		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadRun();

		//************************************
		// Method:    增加一个tcp动作
		// Parameter: tcp动作
		//************************************
		void PushTcpAction(CTcpAction* pAction);
	};
}
