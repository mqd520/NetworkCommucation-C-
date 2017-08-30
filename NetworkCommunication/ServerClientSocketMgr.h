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
		vector<ClientSocketData> m_vec;//accept socket���ݼ���

	public:
		CServerClientSocketMgr();
		~CServerClientSocketMgr();

		//************************************
		// Method:    ����һ��accept socket����
		// Parameter: accept socket����
		//************************************
		void PushSocketData(ClientSocketData data);

		//************************************
		// Method:    ��ȡָ������˿ͻ���socket�������
		// Parameter: ����˿ͻ���socket	
		//************************************
		ClientSocketData GetDataByServerClientSocket(SOCKET peer);

		//************************************
		// Method:    ��ȡָ������socket���������
		// Parameter: ����socket	
		//************************************
		ClientSocketData GetDataByLocalSocket(SOCKET local);
	};
}