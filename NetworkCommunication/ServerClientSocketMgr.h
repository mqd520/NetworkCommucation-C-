#pragma once
#include "SocketAPI.h"
#include "Def.h"
#include <vector>

using namespace std;

namespace NetworkCommunication
{
	//服务端关联客户端socket管理
	class CServerClientSocketMgr
	{
	private:
		vector<ServerClientSocket> m_vec;//accept socket数据集合

	public:
		CServerClientSocketMgr();
		~CServerClientSocketMgr();

		//************************************
		// Method:    增加一个accept socket数据
		// Parameter: accept socket数据
		//************************************
		void PushAcceptSocketData(ServerClientSocket data);

		static ServerClientSocket Create(SOCKET peer, SOCKET local);

		//************************************
		// Method:    获取指定服务端客户端socket相关数据
		// Parameter: 服务端客户端socket	
		//************************************
		ServerClientSocket GetDataByServerClientSocket(SOCKET peer);

		//************************************
		// Method:    获取指定本地socket的相关数据
		// Parameter: 本地socket	
		//************************************
		ServerClientSocket GetDataByLocal(SOCKET local);
	};
}