#pragma once
#include "../../SocketAPI.h"
#include "../../TcpConnectionMgr.h"
#include "../../Def.h"
#include "../../TcpService.h"
#include <vector>

using namespace std;

namespace tc
{
	//tcp�����
	class TcpServer : public TcpService
	{
	protected:
		CSocketAPI m_socketAPI;			//socket�������
		bool bListening;				//�Ƿ����ڼ���
		vector<TCHAR*> m_vecAllowIP;	//����Ŀͻ���IP
		SOCKADDR_IN m_socketAddr;		//socket addr

	protected:
		//************************************
		// Method:    ָ��IP�Ƿ�����
		// Parameter: ip
		//************************************
		bool IsAllow(TCHAR* ip);

		//************************************
		// Method:    �յ�tcp�¼�����
		// Parameter: tcp�¼�
		//************************************
		void OnRecvTcpEvent(TcpEvt* pEvent);

	public:
		TcpServer();
		~TcpServer();

		//************************************
		// Method:    ���ü�����Ϣ
		//************************************
		void SetListenInfo(string ip, int port);

		//************************************
		// Method:    ��ʼ����
		//************************************
		bool Listen();

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
		// Method:    �ر�ָ���ͻ���
		// Parameter: �ͻ���SOCKET
		//************************************
		void CloseClient(SOCKET client);

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