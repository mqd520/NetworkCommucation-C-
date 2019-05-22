#pragma once
#include "TcpEvt.h"

namespace tc
{
	// ���ӷ���˽���¼���
	class ConnectSrvResultEvt : public CTcpEvt
	{
	private:
		bool bSuccess;	// �����Ƿ�ɹ�

	public:
		ConnectSrvResultEvt(CTcpService* pSrv, bool success);
		~ConnectSrvResultEvt();

		//************************************
		// Method:    ��ȡ�¼�����
		//************************************
		int GetEvtType();

		//************************************
		// Method:    ��ȡ���ӽ��
		//************************************
		bool GetConnectResult();
	};
}