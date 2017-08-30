#pragma once
#include "SocketAPI.h"
#include "TcpConnectionMgr.h"
#include "Def.h"
#include <vector>

using namespace std;

namespace NetworkCommunication
{
	//tcp�����
	class CTcpServer : public CTcpService
	{
	protected:
		CSocketAPI m_socketAPI;//socket�������
		bool m_bListening;//�Ƿ����ڼ���
		vector<TCHAR*> m_vecAllowIP;//����Ŀͻ���IP
		SOCKADDR_IN m_socketAddr;//socket addr
		vector<SOCKET> m_vecClientSocket;

	public:
		CTcpServer();
		~CTcpServer();

		//************************************
		// Method:    ��ʼ����
		// Parameter: ����IP
		// Parameter: �����˿�
		//************************************
		bool Listen(TCHAR* ip, int port);

		//************************************
		// Method:    ��ȡ�����socket addr
		//************************************
		SOCKADDR_IN GetServerSocketAddr();

		//************************************
		// Method:    ����һ������IP
		// Parameter: ip
		//************************************
		void AddAllowIP(TCHAR* ip);

		//************************************
		// Method:    �Ƴ�ָ��������IP
		// Parameter: ip
		//************************************
		void RemoveAllowIP(TCHAR* ip);

		//************************************
		// Method:    �����������IP,��ʾ��������IP
		//************************************
		void ClearAllowIP();

		//************************************
		// Method:    ָ��IP�Ƿ�����
		// Parameter: ip
		//************************************
		bool IsAllow(TCHAR* ip);
	};
}