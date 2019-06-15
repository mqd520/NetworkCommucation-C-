#pragma once
#include <queue>
#include "Def.h"
#include "Include/tc/SocketTool.h"
#include "ThreadLock.h"

using namespace std;

namespace tc
{
	// select信号处理类
	class SelectSingal
	{
	protected:
		queue<SocketSingalData> quSockets;		// 有信号的socket数据队列
		//vector<SocketSingalData> vecSockets;	// 有信号的socket数据集合
		CThreadLock lock1;						// 线程锁, 针对: quSignalSocketData

	protected:
		//************************************
		// Method:    接收新连接
		// Parameter: 服务端socket
		//************************************
		void RecvNewConnection(SOCKET socket);

		//************************************
		// Method:    接收对端数据
		// Parameter: 收发数据的socket
		//************************************
		void RecvPeerData(SOCKET socket);

		//************************************
		// Method:    发送数据
		// Parameter: 收发数据的socket
		//************************************
		void SendData(SOCKET socket);

		//************************************
		// Method:    连接服务端成功事件处理
		// Parameter: 客户端socket
		//************************************
		void OnConnectSuccess(SOCKET socket);

		//************************************
		// Method:    连接服务端失败事件处理
		// Parameter: 客户端socket
		//************************************
		void OnConnectFail(SOCKET socket);

	public:
		SelectSingal();
		~SelectSingal();

		//************************************
		// Method:    加入一个socket信号数据
		// Parameter: socket信号数据
		//************************************
		void PushSocketSingal(SocketSingalData data);

		//************************************
		// Method:    处理socket信号
		//************************************
		void ProcessSocketSingal();

		//************************************
		// Method:    等待处理的socket队列是否为空
		//************************************
		bool IsEmpty();
	};
}