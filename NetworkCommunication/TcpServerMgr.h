#pragma once
#include "TcpServer.h"
#include <vector>
#include "Def.h"

using namespace std;

namespace NetworkCommunication
{
	//tcp server ����
	class CTcpServerMgr
	{
	private:
		vector<CTcpServer*> m_vecTcpServer;//tcp server���󼯺�

	public:
		CTcpServerMgr();
		~CTcpServerMgr();

		//************************************
		// Method:    ����һ��tcp server����
		//************************************
		void Push(CTcpServer* tcpserver);

		//************************************
		// Method:    ��ȡָ�������socket��tcp server����
		// Parameter: �����socket
		//************************************
		CTcpServer* GetTcpServerByServerSocket(SOCKET server);
	};
}