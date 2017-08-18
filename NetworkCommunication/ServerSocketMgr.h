#pragma once
#include "SocketAPI.h"
#include <vector>
#include "Def.h"

using namespace std;

namespace NetworkCommunication
{
	//�����socket����
	class CServerSocketMgr
	{
	private:
		CSocketAPI m_socketAPI;
		vector<ServerSocket> m_vecData;

	public:
		CServerSocketMgr();
		~CServerSocketMgr();

		//************************************
		// Method:    ����һ�������socket����
		// Parameter: ip
		// Parameter: �˿�
		// Parameter: socket��ַ
		// Parameter: tcp����˶���
		//************************************
		static ServerSocket Create(char* ip, int port, SOCKET socket, void* server);

		//************************************
		// Method:    ���ӷ����socket����
		// Parameter: socket��������
		//************************************
		void PushServerSocketData(ServerSocket data);

		//************************************
		// Method:    ��ȡָ��socket�Ĺ�������
		// Parameter: socket
		// Return:	  socket��������
		//************************************
		ServerSocket GetDataBySocket(SOCKET socket);

		//************************************
		// Method:    ��ȡָ��tcp����˵Ĺ�������
		// Parameter: tcp����˶���
		// Return:	  socket��������
		//************************************
		ServerSocket GetDataByServer(void* server);
	};
}
