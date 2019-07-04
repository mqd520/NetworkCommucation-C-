#pragma once
#include "ServerSession.h"
#include <vector>

using namespace std;

namespace pck
{
	// session mgr
	class SessionMgr
	{
	public:
		SessionMgr();

	protected:
		vector<ServerSession*>	vecSessions;	// session集合

	public:
		//************************************
		// Method:    获取指定client id session
		// Parameter: int clientId
		//************************************
		ServerSession* GetSession(int clientId);

		//************************************
		// Method:    创建session
		// Parameter: int clientId
		// Parameter: void* pObj:	IGPacketSrvServer对象
		// Parameter: recvPwd:	是否需要验证客户端密码
		//************************************
		ServerSession* CreateSession(int clientId, void* pObj, bool recvPwd = true);

		//************************************
		// Method:    关闭session
		// Parameter: int clientId
		//************************************
		void CloseSession(int clientId);

		//************************************
		// Method:    关闭session
		//************************************
		void CloseSession();
	};
}