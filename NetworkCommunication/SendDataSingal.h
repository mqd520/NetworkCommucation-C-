#pragma once
#include "SocketSingal.h"

namespace NetworkCommunication
{
	//发数据信号处理
	class CSendDataSingal : public CSocketSingal
	{
	protected:
		//************************************
		// Method:    处理socket可写信号
		// Parameter: socket
		// Parameter: socket类型
		//************************************
		void ProcessWriteSingal(SOCKET socket, int type);

	public:
		CSendDataSingal();
		~CSendDataSingal();
	};
}