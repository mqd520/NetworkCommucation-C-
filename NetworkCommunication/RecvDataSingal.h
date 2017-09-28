#pragma once
#include "SocketSingal.h"

namespace NetworkCommunication
{
	//收数据信号处理
	class CRecvDataSingal : public CSocketSingal 
	{
	protected:
		//************************************
		// Method:    处理socket可读信号
		// Parameter: socket
		// Parameter: socket类型
		//************************************
		void ProcessReadSingal(SOCKET socket, int type);

	public:
		CRecvDataSingal();
		~CRecvDataSingal();
	};
}