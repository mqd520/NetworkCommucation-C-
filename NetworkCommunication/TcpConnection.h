#pragma once
#include "SocketMgr.h"
#include "PacketBase.h"
#include <vector>

using namespace std;

namespace NetworkCommunication
{
	//tcp会话
	class CTcpConnection
	{
	private:
		CSocketMgr m_mgr;

	protected:
		SOCKET m_peerSocket;//对端socket
		SOCKET m_localSocket;//本地socket
		BYTE* m_pRecvBuf;
		int m_nRecvBufLen;

	private:
		SOCKET GetRecvSocket();

	public:
		CTcpConnection(SOCKET localSocket, SOCKET peerSocket);
		~CTcpConnection();

		SOCKET GetLocalSocket();

		SOCKET GetPeerSocket();

		//************************************
		// Method:    发送数据(同步)
		// Returns:   是否成功
		// Parameter: 缓冲区指针
		// Parameter: 缓冲区长度
		//************************************
		bool SendData(BYTE buf[], int len);

		//************************************
		// Method:    发送单个网络包(同步)
		// Returns:   是否成功
		// Parameter: 网络包
		//************************************
		bool SendPacket(PacketBase* pack);

		//************************************
		// Method:    批量发送网络包(同步)
		// Returns:   是否成功
		// Parameter: 网络包集合
		//************************************
		bool BatchSendPacket(vector<PacketBase*> packs);

		//************************************
		// Method:    有数据可读
		//************************************
		void OnReadData();
	};
}