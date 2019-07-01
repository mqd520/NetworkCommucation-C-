#pragma once
#include "TcpService.h"
#include <queue>
using namespace std;

namespace tc
{
	// tcp服务对象管理类
	class TcpServiceMgr
	{
	public:
		TcpServiceMgr();
		~TcpServiceMgr();

	private:
		vector<TcpService*> vecTcpSrv;	// tcp服务对象集合

	public:
		//************************************
		// Method:    加入一个tcp服务对象
		// Parameter: tcp服务对象
		//************************************
		void Remove(TcpService* pTcpSrv);

		//************************************
		// Method:    清除所有tcp服务对象
		//************************************
		void Clear();

		//************************************
		// Method:    加入一个tcp服务对象
		// Parameter: tcp服务对象
		//************************************
		void PushTcpService(TcpService* pTcpSrv);

		//************************************
		// Method:    获取指定socket关联的tcp服务对象
		// Return:	  tcp服务对象
		// Parameter: socket
		//************************************
		TcpService* GetTcpSrvBySocket(SOCKET socket);
	};
}