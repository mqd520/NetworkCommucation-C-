#pragma once
#include "SocketAPI.h"
#include <vector>
#include "Def.h"

using namespace std;

namespace NetworkCommunication
{
	//服务端socket管理
	class CServerSocketMgr
	{
	private:
		CSocketAPI m_socketAPI;
		vector<ServerSocket> m_vecData;

	public:
		CServerSocketMgr();
		~CServerSocketMgr();

		//************************************
		// Method:    创建一个服务端socket数据
		// Parameter: ip
		// Parameter: 端口
		// Parameter: socket地址
		// Parameter: tcp服务端对象
		//************************************
		static ServerSocket Create(char* ip, int port, SOCKET socket, void* server);

		//************************************
		// Method:    增加服务端socket数据
		// Parameter: socket关联数据
		//************************************
		void PushServerSocketData(ServerSocket data);

		//************************************
		// Method:    获取指定socket的关联数据
		// Parameter: socket
		// Return:	  socket关联数据
		//************************************
		ServerSocket GetDataBySocket(SOCKET socket);

		//************************************
		// Method:    获取指定tcp服务端的关联数据
		// Parameter: tcp服务端对象
		// Return:	  socket关联数据
		//************************************
		ServerSocket GetDataByServer(void* server);
	};
}
