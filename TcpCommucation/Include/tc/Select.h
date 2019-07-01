#pragma once
#include <vector>
#include "Def.h"
#include "ThreadLock.h"

using namespace std;

namespace tc
{
	// select类
	class Select
	{
	public:
		Select();
		~Select();

	private:
		vector<vector<SocketInfoData>> vecGroupSocket;		// socket分组
		CThreadLock lock2;									// 线程锁, 针对vecProcessingSocketData变量

	private:
		//************************************
		// Method:    对所有socket进行分组
		//************************************
		void CalcSocketGroup(vector<SocketInfoData>& vec);

		//************************************
		// Method:    socket发生异常
		// Parameter: socket类型数据
		// Parameter: fs
		//************************************
		void OnSocketExcept(SocketInfoData& socketData, fd_set& fs);

		//************************************
		// Method:    处理socket可读
		// Parameter: socket类型数据
		// Parameter: fs
		//************************************
		void OnSocketRead(SocketInfoData& socketData, fd_set& fs);

		//************************************
		// Method:    处理socket可写
		// Parameter: socket类型数据
		// Parameter: fs
		//************************************
		void OnSocketWrite(SocketInfoData& socketData, fd_set& fs);

		//************************************
		// Method:    收到新连接事件处理
		//************************************
		void OnRecvNewConn(SocketInfoData& socketData);

		//************************************
		// Method:    收到对端数据事件处理
		//************************************
		void OnRecvData(SocketInfoData& socketData);

		//************************************
		// Method:    连接服务端成功事件处理
		//************************************
		void OnConnectSuccess(SocketInfoData& socketData);

		//************************************
		// Method:    连接服务端失败事件处理
		//************************************
		void OnConnectFail(SocketInfoData& socketData);

	public:
		//************************************
		// Method:    查询socket信号
		//************************************
		void QuerySingal(vector<SocketInfoData>& vec);
	};
}