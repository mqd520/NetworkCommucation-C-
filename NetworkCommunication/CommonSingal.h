#pragma once
#include "SocketSingal.h"
#include "SocketAPI.h"

namespace NetworkCommunication
{
	//收数据信号处理
	class CCommonSingal : public CSocketSingal
	{
	private:
		CSocketAPI m_socketAPI;//socket api

	protected:
		//************************************
		// Method:    处理socket可读信号
		// Parameter: socket
		// Parameter: socket类型
		//************************************
		void ProcessReadSingal(SOCKET socket, int type);

		//************************************
		// Method:    处理socket可写信号
		// Parameter: socket
		// Parameter: socket类型
		//************************************
		void ProcessWriteSingal(SOCKET socket, int type);

		//************************************
		// Method:    处理socket异常信号
		// Parameter: socket
		// Parameter: socket类型
		//************************************
		void ProcessExceptSingal(SOCKET socket, int type);

		//************************************
		// Method:    收到新连接事件处理
		// Parameter: socket
		//************************************
		void OnRecvNewConn(SOCKET socket);

	public:
		CCommonSingal();
		~CCommonSingal();
	};
}