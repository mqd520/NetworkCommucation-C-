#pragma once
#include "TcpService.h"
#include <queue>
using namespace std;

namespace NetworkCommunication
{
	//tcp服务对象管理
	class CTcpServiceMgr
	{
	private:
		vector<CTcpService*> m_vecTcpService;//tcp服务对象集合

	public:
		CTcpServiceMgr();
		~CTcpServiceMgr();

		//************************************
		// Method:    加入一个tcp服务对象
		// Parameter: tcp服务对象
		//************************************
		void PushTcpService(CTcpService* srv);

		//************************************
		// Method:    获取指定socket关联的tcp服务对象
		// Return:	  tcp服务对象
		// Parameter: socket
		//************************************
		CTcpService* GetTcpSrvBySocket(SOCKET socket);
	};
}