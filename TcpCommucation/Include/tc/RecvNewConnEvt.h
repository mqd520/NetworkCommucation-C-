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
		string strClientIP;	// �ͻ���IP
		int nClientPort;	// �ͻ��˶˿�

	public:
		RecvNewConnEvt(TcpService* pSrv, SOCKET client);
		~RecvNewConnEvt();

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