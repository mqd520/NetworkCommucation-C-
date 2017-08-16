#pragma once
#include "SocketAPI.h"
#include "PacketBase.h"
#include <vector>
#include "Def.h"

using namespace std;

namespace NetworkCommunication
{
	//tcp会话
	class CTcpConnection
	{
	private:
		CSocketAPI m_mgr;

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
		// Method:    接收数据
		// Parameter: socket接收数据
		//************************************
		void OnRecvData(SocketRecvData data);
	};
}