#pragma once
#include <vector>
#include "SocketAPI.h"
#include "Def.h"
#include "ThreadLock.h"

using namespace std;

namespace NetworkCommunication
{
	//select类
	class CSelect
	{
	private:
		CSocketAPI m_socketAPI;//socket api
		vector<SelectSocketData> m_vecSocket;//需要监听的socket集合
		fd_set m_readFdSet;//可读socket集合
		fd_set m_writeFdSet;//可写socket集合
		fd_set m_exceptFdSet;//异常socket集合
		vector<vector<SelectSocketData>> m_group;//socket分组
		timeval m_selectTimeout;//
		vector<ProcessingSocketData> m_vecProcessingData;//正在进行处理的socket数据集合
		CThreadLock m_lock1;//线程锁,针对m_vecSocket变量
		CThreadLock m_lock2;//线程锁,针对m_vecProcessingData变量

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
		// Parameter: 信号类型
		//************************************
		bool IsProcessingSingal(SOCKET socket, int type);

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
		CSelect();
		~CSelect();

		//************************************
		// Method:    socket队列是否为空
		//************************************
		bool IsEmpty();

		//************************************
		// Method:    添加socket
		// Parameter: socket
		// Parameter: 类型
		//************************************
		void AddSocket(SOCKET socket, int type);

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
		// Parameter: 信号类型
		//************************************
		void OnProcessingSocketCmp(SOCKET socket, int type);
	};
}