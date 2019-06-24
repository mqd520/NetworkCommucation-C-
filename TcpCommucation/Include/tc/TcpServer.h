#pragma once
#include "SocketTool.h"
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
	public:
		TcpServer(string ip = "", int port = 0);
		virtual ~TcpServer();

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

	public:
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
		// Parameter: ������ָ��
		// Parameter: �������ֽڳ���
		//************************************
		void Send(int clientId, BYTE* pBuf, int len);

		//************************************
		// Method:    �ر�ָ���ͻ���
		// Parameter: clientId:	�ͻ���SOCKET
		// Parameter: b:	�Ƿ�������ӶϿ��¼�, Ĭ��: false
		//************************************
		void CloseClient(int clientId, bool b = false);

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