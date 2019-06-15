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
		vector<vector<SelectSocketData>> vecGroupSocket;	// socket分组
		vector<ProcessingSocketData> vecProcessingSocketData; // 正在进行处理的socket数据集合
		CThreadLock lock2;	// 线程锁, 针对vecProcessingSocketData变量

	private:
		//************************************
		// Method:    处理等待监听的socket
		//************************************
		void ProcessSocket();

		//************************************
		// Method:    对所有socket进行分组
		//************************************
		void CalcSocketGroup(vector<SelectSocketData>& vec);

		//************************************
		// Method:    判断指定socket的信号是否正在被处理
		// Parameter: socket
		// Parameter: socket类型: ESocketSingalType
		//************************************
		bool IsProcessingSingal(SOCKET socket, ESocketSingalType type);

		//************************************
		// Method:    移除正在进行处理的socket
		// Parameter: socket
		//************************************
		void RemoveProcessingSocket(SOCKET socket);

		//************************************
		// Method:    处理socket异常
		// Parameter: socket类型数据
		// Parameter: fs
		//************************************
		void processSocketExcept(SelectSocketData socketData, fd_set& fs);

		//************************************
		// Method:    处理socket可读
		// Parameter: socket类型数据
		// Parameter: fs
		//************************************
		void processSocketRead(SelectSocketData socketData, fd_set& fs);

	public:
		//************************************
		// Method:    查询socket信号
		//************************************
		void QuerySingal(vector<SelectSocketData>& vec);

		//************************************
		// Method:    指示用户退出
		//************************************
		void Exit();
	};
}