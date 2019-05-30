#pragma once
#include "TcpService.h"
#include <queue>
using namespace std;

namespace tc
{
	// tcp服务对象管理类
	class TcpServiceMgr
	{
	private:
		vector<TcpService*> vecTcpService;	// tcp服务对象集合

	public:
		TcpServiceMgr();
		~TcpServiceMgr();

		//************************************
		// Method:    加入一个tcp服务对象
		// Parameter: tcp服务对象
		//************************************
		void PushTcpService(TcpService* srv);

		//************************************
		// Method:    获取指定socket关联的tcp服务对象
		// Return:	  tcp服务对象
		// Parameter: socket
		//************************************
		TcpService* GetTcpSrvBySocket(SOCKET socket);
	};
}