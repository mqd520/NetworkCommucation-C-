#pragma once
#include "SocketAPI.h"
#include <vector>
#include "Def.h"

using namespace std;

namespace NetworkCommunication
{
	//服务端socket关联数据管理
	class CServerSocketDataMgr
	{
	private:
		CSocketAPI m_socketAPI;
		vector<ServerSocketData> m_vecData;

	public:
		CServerSocketDataMgr();
		~CServerSocketDataMgr();

		//************************************
		// Method:    创建一个服务端socket数据
		// Parameter: ip
		// Parameter: 端口
		// Parameter: socket地址
		// Parameter: tcp服务端对象
		//************************************
		static ServerSocketData Create(char* ip, int port, SOCKET socket, void* server);

		//************************************
		// Method:    增加服务端socket数据
		// Parameter: socket关联数据
		//************************************
		void PushServerSocketData(ServerSocketData data);

		//************************************
		// Method:    获取指定socket的关联数据
		// Parameter: socket
		// Return:	  socket关联数据
		//************************************
		ServerSocketData GetDataBySocket(SOCKET socket);

		//************************************
		// Method:    获取指定tcp服务端的关联数据
		// Parameter: tcp服务端对象
		// Return:	  socket关联数据
		//************************************
		ServerSocketData GetDataByServer(void* server);
	};
}
