#pragma once
#include <queue>
#include "Def.h"

using namespace std;

namespace NetworkCommunication
{
	//socket信号处理
	class CSocketSingal
	{
	protected:
		queue<SocketSingalData> m_queueSocketData;//有信号的socket数据队列

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