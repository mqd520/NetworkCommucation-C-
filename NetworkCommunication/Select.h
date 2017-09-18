#pragma once
#include <vector>
#include "SocketAPI.h"
#include "Thread.h"
#include "Def.h"

using namespace std;

namespace NetworkCommunication
{
	//select类
	class CSelect : public CThreadEntry
	{
	private:
		CSocketAPI m_socketAPI;//socket api
		vector<SelectSocketData> m_vecSocket;//需要监听的socket集合
		CThread* m_thread;//线程对象
		fd_set m_readFdSet;
		fd_set m_exceptFdSet;
		vector<vector<SelectSocketData>> m_group;//socket分组
		timeval m_selectTimeout;//
		int m_nBufLen;//接收缓冲区字节最大长度

	private:
		//************************************
		// Method:    处理等待监听的socket
		//************************************
		void ProcessSocket();

		// 对所有socket进行分组
		void CalcSocketGroup();

		//************************************
		// Method:    检查指定socket是否可读
		// Parameter: 监听socket关联数据
		//************************************
		void CheckSocketCanRead(SelectSocketData socketData);

		//************************************
		// Method:    检查指定socket是否异常
		// Parameter: 监听socket关联数据
		//************************************
		void CheckSocketExcept(SelectSocketData socketData);

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
		// Method:    运行线程
		//************************************
		void Run();

		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadRun();

		//************************************
		// Method:    添加socket
		// Parameter: socket
		// Parameter: 类型
		//************************************
		void AddSocket(SOCKET socket, int type);

		// 移除指定socket
		void RemoveSocket(SOCKET socket);
	};
}