#pragma once
#include <vector>
#include "Def.h"
#include "Include/tc/SocketTool.h"
#include "ThreadLock.h"

using namespace std;

namespace tc
{
	// select类
	class CSelect
	{
	public:
		CSelect();
		~CSelect();

	private:
		vector<SelectSocketData> vecListenSocket;	//需要监听的socket集合
		fd_set fsRead;			// 可读socket集合
		fd_set fsWrite;			// 可写socket集合
		fd_set fsExcept;		// 异常socket集合
		vector<vector<SelectSocketData>> groupSocket;	// socket分组
		timeval m_selectTimeout;
		vector<ProcessingSocketData> vecProcessingSocketData; // 正在进行处理的socket数据集合
		CThreadLock m_lock1;	// 线程锁, 针对vecListenSocket变量
		CThreadLock m_lock2;	// 线程锁, 针对vecProcessingSocketData变量

	private:
		//************************************
		// Method:    处理等待监听的socket
		//************************************
		void ProcessSocket();

		//************************************
		// Method:    对所有socket进行分组
		//************************************
		void CalcSocketGroup();

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
		// Method:    检查指定socket是否异常
		// Parameter: 监听socket关联数据
		//************************************
		void CheckSocketExcept(SelectSocketData socketData);

		//************************************
		// Method:    检查指定socket是否可读
		// Parameter: 监听socket关联数据
		//************************************
		void CheckSocketCanRead(SelectSocketData socketData);

		//************************************
		// Method:    检查指定socket是否可写
		// Parameter: 监听socket关联数据
		//************************************
		void CheckSocketCanWrite(SelectSocketData socketData);

	public:
		//************************************
		// Method:    socket队列是否为空
		//************************************
		bool IsEmpty();

		//************************************
		// Method:    添加socket
		// Parameter: socket
		// Parameter: socket类型: ESocketType
		//************************************
		void AddSocket(SOCKET socket, ESocketType type);

		//************************************
		// Method:    移除指定的socket
		// Parameter: socket
		// Parameter: 是否关闭,默认关闭
		//************************************
		void RemoveSocket(SOCKET socket, bool close = true);

		//************************************
		// Method:    查询socket信号
		//************************************
		void Select();

		//************************************
		// Method:    socket信号处理完毕事件处理
		// Parameter: socket
		// Parameter: socket类型: ESocketSingalType
		//************************************
		void OnProcessingSocketCmp(SOCKET socket, ESocketSingalType type);

		//************************************
		// Method:    指示用户退出
		//************************************
		void Exit();
	};
}