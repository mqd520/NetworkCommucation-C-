#pragma once
#include <queue>
#include "Def.h"
#include "Include/tc/SocketTool.h"

using namespace std;

namespace tc
{
	// socket信号处理类
	class SocketSingalProcess
	{
	protected:
		queue<SocketSingalData> quSignalSocketData;	// 有信号的socket数据队列

	protected:
		//************************************
		// Method:    处理socket可读信号
		// Parameter: socket
		// Parameter: socket类型: ESocketType
		//************************************
		virtual void ProcessReadSingal(SOCKET socket, ESocketType type);

		//************************************
		// Method:    处理socket可写信号
		// Parameter: socket
		// Parameter: socket类型: ESocketType
		//************************************
		virtual void ProcessWriteSingal(SOCKET socket, ESocketType type);

		//************************************
		// Method:    处理socket异常信号
		// Parameter: socket
		// Parameter: socket类型: ESocketType
		//************************************
		virtual void ProcessExceptSingal(SOCKET socket, ESocketType type);

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
		SocketSingalProcess();
		~SocketSingalProcess();

		//************************************
		// Method:    加入一个socket信号数据
		// Parameter: socket信号数据
		//************************************
		void PushSocket(SocketSingalData data);

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