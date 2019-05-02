#pragma once
#include <queue>
#include "Def.h"
#include "SocketAPI.h"

using namespace std;

namespace NetworkCommunication
{
	//socket信号处理
	class CSocketSingal
	{
	protected:
		queue<SocketSingalData> m_queueSocketData;//有信号的socket数据队列
		CSocketAPI m_socketAPI;//

	protected:
		//************************************
		// Method:    处理socket可读信号
		// Parameter: socket
		// Parameter: socket类型
		//************************************
		virtual void ProcessReadSingal(SOCKET socket, int type);

		//************************************
		// Method:    处理socket可写信号
		// Parameter: socket
		// Parameter: socket类型
		//************************************
		virtual void ProcessWriteSingal(SOCKET socket, int type);

		//************************************
		// Method:    处理socket异常信号
		// Parameter: socket
		// Parameter: socket类型
		//************************************
		virtual void ProcessExceptSingal(SOCKET socket, int type);

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
		CSocketSingal();
		~CSocketSingal();

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