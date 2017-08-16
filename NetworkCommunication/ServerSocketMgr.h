#pragma once
#include "SocketAPI.h"
#include <vector>
#include "Def.h"

using namespace std;

namespace NetworkCommunication
{
	//�����socket�������ݹ���
	class CServerSocketDataMgr
	{
	private:
		CSocketAPI m_socketAPI;
		vector<ServerSocketData> m_vecData;

	public:
		CServerSocketDataMgr();
		~CServerSocketDataMgr();

		//************************************
		// Method:    ����һ�������socket����
		// Parameter: ip
		// Parameter: �˿�
		// Parameter: socket��ַ
		// Parameter: tcp����˶���
		//************************************
		static ServerSocketData Create(char* ip, int port, SOCKET socket, void* server);

		//************************************
		// Method:    ���ӷ����socket����
		// Parameter: socket��������
		//************************************
		void PushServerSocketData(ServerSocketData data);

		//************************************
		// Method:    ��ȡָ��socket�Ĺ�������
		// Parameter: socket
		// Return:	  socket��������
		//************************************
		ServerSocketData GetDataBySocket(SOCKET socket);

		//************************************
		// Method:    ��ȡָ��tcp����˵Ĺ�������
		// Parameter: tcp����˶���
		// Return:	  socket��������
		//************************************
		ServerSocketData GetDataByServer(void* server);
	};
}
