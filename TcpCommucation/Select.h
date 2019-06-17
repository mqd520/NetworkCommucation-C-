#pragma once
#include <vector>
#include "Def.h"
#include "Include/tc/SocketTool.h"
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
		// Method:    处理socket异常
		// Parameter: socket类型数据
		// Parameter: fs
		//************************************
		void processSocketExcept(SocketInfoData socketData, fd_set& fs);

		//************************************
		// Method:    处理socket可读
		// Parameter: socket类型数据
		// Parameter: fs
		//************************************
		void processSocketRead(SocketInfoData socketData, fd_set& fs);

	public:
		//************************************
		// Method:    查询socket信号
		//************************************
		void QuerySingal(vector<SocketInfoData>& vec);
	};
}