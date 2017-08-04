#pragma once
#include "SocketMgr.h"
#include <vector>

using namespace std;

namespace NetworkCommunication
{
	typedef struct tagServerSocketData
	{
		SOCKET socket;
		TCHAR ip[20];
		int port;
		SOCKADDR_IN addr;
	}ServerSocketData;

	class CServerSocketMgr
	{
	private:
		vector<ServerSocketData> m_vecData;

	public:
		CServerSocketMgr();
		~CServerSocketMgr();

		void Push(ServerSocketData data);

		ServerSocketData GetDataBySocket(SOCKET socket);
	};
}
