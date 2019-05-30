#pragma once
#include "Include/tc/SocketTool.h"
#include "../../TcpConnectionMgr.h"
#include "../../Def.h"
#include "../../TcpService.h"
#include <vector>

using namespace std;

namespace tc
{
	// tcp�������
	class TcpServer : public TcpService
	{
	protected:
		bool bListening;				// �Ƿ����ڼ���
		vector<string> vecAllowIP;		// ����Ŀͻ���IP
		SOCKADDR_IN socketAddr;			// socket addr

	protected:
		//************************************
		// Method:    ָ��IP�Ƿ�����
		// Parameter: ip
		//************************************
		bool IsAllow(string ip);

		//************************************
		// Method:    �յ�tcp�¼�����
		// Parameter: tcp�¼�
		//************************************
		void OnRecvTcpEvent(TcpEvt* pEvent);

	public:
		TcpServer(string ip = "", int port = 0);
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
		void AddAllowIP(string ip);

		//************************************
		// Method:    �Ƴ�ָ��������IP
		// Parameter: ip
		//************************************
		void RemoveAllowIP(string ip);

		//************************************
		// Method:    �����������IP, ��ʾ��������IP
		//************************************
		void ClearAllowIP();
	};
}