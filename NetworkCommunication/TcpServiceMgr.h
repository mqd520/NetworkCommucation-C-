#pragma once
#include "TcpService.h"
#include "Def.h"
#include "TcpSrvEvt.h"

#include <queue>
using namespace std;

namespace NetworkCommunication
{
	//tcp服务对象管理
	class CTcpServiceMgr : public CThreadEntry
	{
	private:
		CThread* m_thread;//线程对象
		queue<CTcpSrvEvt*> m_queueEvent;//tcp事件集合
		vector<CTcpService*> m_vecTcpService;//tcp服务对象集合

	private:
		//************************************
		// Method:    处理接收到的tcp事件
		//************************************
		void ProcessTcpEvent();

	public:
		CTcpServiceMgr();
		~CTcpServiceMgr();

		//************************************
		// Method:    运行线程
		//************************************
		void Run();

		//************************************
		// Method:    线程运行事件处理
		//************************************
		void OnThreadRun();

		//增加一个tcp服务对象
		void PushTcpService(CTcpService* srv);

		//************************************
		// Method:    追加一个tcp服务事件
		// Parameter: tcp服务事件
		//************************************
		void PushTcpEvent(CTcpSrvEvt* pEvent);

		//************************************
		// Method:    获取指定socket关联的tcp服务对象
		// Return:	  tcp服务对象
		// Parameter: socket
		//************************************
		CTcpService* GetTcpSrvBySocket(SOCKET socket);
	};
}