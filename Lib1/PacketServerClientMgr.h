#pragma once
#include "PacketServerClient.h"

namespace lib1
{
	// 
	class PacketServerClientMgr
	{
	public:
		PacketServerClientMgr();
		~PacketServerClientMgr();

	protected:
		vector<PacketServerClient*> vecClients;		// 客户端对象集合

	public:
		//************************************
		// Method:    创建一个客户端对象
		// Parameter: int clientId
		//************************************
		PacketServerClient* CreateClient(int clientId, void* pSrv, bool bNeedVertify = true);

		//************************************
		// Method:    获取客户端对象
		// Parameter: int clientId
		//************************************
		PacketServerClient* GetClient(int clientId);

		//************************************
		// Method:    移除一个客户端对象
		// Parameter: int clientId
		//************************************
		void Remove(int clientId);

		//************************************
		// Method:    关闭所有
		//************************************
		void CloseAll();
	};
}