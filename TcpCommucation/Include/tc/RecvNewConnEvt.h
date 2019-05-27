#pragma once
#include <string>
#include "TcpEvt.h"

using namespace std;

namespace tc
{
	// �յ��������¼�
	class RecvNewConnEvt : public TcpEvt
	{
	private:
		TCHAR strClientIP[20];	// �ͻ���IP
		int nClientPort;					// �ͻ��˶˿�
		bool bRecvConn;						// �Ƿ����������

	public:
		RecvNewConnEvt(CTcpService* pSrv, SOCKET client, TCHAR* ip, int port);
		~RecvNewConnEvt();

		//************************************
		// Method:    �ܾ�������
		//************************************
		void Refuse();

		//************************************
		// Method:    �Ƿ����������
		//************************************
		bool IsRecv();

		//************************************
		// Method:    ��ȡ�ͻ���IP
		//************************************
		string GetClientIP();

		//************************************
		// Method:    ��ȡ�ͻ��˶˿�
		//************************************
		int GetClientPort();
	};
}