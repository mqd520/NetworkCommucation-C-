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

	protected:
		friend class CCommonSingal;
		//************************************
		// Method:    ��ȡ�����socket addr
		//************************************
		SOCKADDR_IN GetServerSocketAddr();

		//************************************
		// Method:    ָ��IP�Ƿ�����
		// Parameter: ip
		//************************************
		bool IsAllow(TCHAR* ip);

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
		// Method:    ��Զ˷�������
		// Returns:   �Ƿ�ɹ�
		// Parameter: socket
		// Parameter: ������ָ��
		// Parameter: �������ֽڳ���
		// Parameter: �Ƿ��첽,Ĭ���첽����
		// Parameter: ʵ�ʷ����ֽڳ���
		//************************************
		bool Send(SOCKET socket, BYTE* pBuf, int len, bool asyncs = true, int* actualLen = NULL);

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
	};
}