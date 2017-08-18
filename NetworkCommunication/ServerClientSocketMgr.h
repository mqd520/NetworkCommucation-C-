#pragma once
#include "SocketAPI.h"
#include "Def.h"
#include <vector>

using namespace std;

namespace NetworkCommunication
{
	//����˹����ͻ���socket����
	class CServerClientSocketMgr
	{
	private:
		vector<ServerClientSocket> m_vec;//accept socket���ݼ���

	public:
		CServerClientSocketMgr();
		~CServerClientSocketMgr();

		//************************************
		// Method:    ����һ��accept socket����
		// Parameter: accept socket����
		//************************************
		void PushAcceptSocketData(ServerClientSocket data);

		static ServerClientSocket Create(SOCKET peer, SOCKET local);

		//************************************
		// Method:    ��ȡָ������˿ͻ���socket�������
		// Parameter: ����˿ͻ���socket	
		//************************************
		ServerClientSocket GetDataByServerClientSocket(SOCKET peer);

		//************************************
		// Method:    ��ȡָ������socket���������
		// Parameter: ����socket	
		//************************************
		ServerClientSocket GetDataByLocal(SOCKET local);
	};
}