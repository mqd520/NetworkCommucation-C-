#pragma once
#include <vector>
#include "SocketAPI.h"
#include "Thread.h"
#include "Def.h"

using namespace std;

namespace NetworkCommunication
{
	class CSelect
	{
	private:
		CSocketAPI m_socketAPI;//socket api
		vector<SelectSocketData> m_vecSocket;//需要监听的socket集合
		bool m_bExit;//指示线程是否应该结束
		CThread* m_threadSelect;//线程对象
		bool m_bSleep;//select线程是否间隔sleep
		fd_set m_readSet;//读数据fd
		vector<vector<SelectSocketData>> m_group;//socket分组
		timeval m_selectTimeout;//
		int m_nBufLen;//接收缓冲区字节最大长度

	private:
		//************************************
		// Method:    开始查询socket状态
		//************************************
		void StartSelect();

		// 对所有socket进行分组
		void CalcSocketGroup();

		//检查指定socket信号
		void CheckSocketSingal(SelectSocketData socket);

		//************************************
		// Method:    接收新连接
		// Parameter: 服务端server
		//************************************
		void RecvNewConnection(SOCKET server);

		//************************************
		// Method:    接收对端数据
		// Parameter: 接收数据的socket
		//************************************
		void RecvPeerData(SOCKET recv);

	public:
		CSelect();
		~CSelect();

		//************************************
		// Method:    添加socket
		// Parameter: socket
		// Parameter: 类型
		//************************************
		void AddSocket(SOCKET socket, int type); 

		// 移除指定socket
		void RemoveSocket(SOCKET socket);

		//************************************
		// Method:    开启select线程
		//************************************
		void Run();

		//************************************
		// Method:    select线程入口点
		//************************************
		void ThreadEntry();
	};
}