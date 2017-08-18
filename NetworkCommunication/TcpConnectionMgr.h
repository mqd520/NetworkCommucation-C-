#pragma once
#include <vector>
#include "TcpConnection.h"
#include "Thread.h"
#include "Def.h"
#include <queue>

using namespace std;

namespace NetworkCommunication
{
	//tcp连接管理对象
	class CTcpConnectionMgr
	{
	private:
		CSocketAPI m_socketAPI;//socket api
		vector<CTcpConnection*> m_vecTcpConnection;//tcp连接集合

	public:
		CTcpConnectionMgr();
		~CTcpConnectionMgr();

		//增加一个tcp连接
		void PushTcpConn(CTcpConnection* conn);

		//************************************
		// Method:    移除指定收发数据的socket关联的tcp连接对象
		// Parameter: 收发数据的socket
		//************************************
		void RemoveBySendRecvSocket(SOCKET socket);

		//************************************
		// Method:    获取指定收发数据的socket关联的tcp连接对象
		// Parameter: 收发数据的socket
		// Return:	  tcp连接对象
		//************************************
		CTcpConnection* GetBySendRecvSocket(SOCKET socket);

		//void AsyncSend(SOCKET socket, BYTE buf[], int len, int* actualLen);

		//************************************
		// Method:    接收到对端数据事件处理
		// Parameter: 对端数据
		//************************************
		void OnRecvPeerData(PeerData* data);

		//对端主动关闭事件处理
		void OnPeerClose(SOCKET peer);
	};
}