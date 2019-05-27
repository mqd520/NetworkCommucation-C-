#pragma once
#include "TcpEvt.h"

namespace tc
{
	// ���ӷ���˽���¼�
	class ConnectSrvResultEvt : public TcpEvt
	{
	private:
		bool bSuccess;	// �����Ƿ�ɹ�

	public:
		ConnectSrvResultEvt(CTcpService* pSrv, bool success);
		~ConnectSrvResultEvt();

		//************************************
		// Method:    ��ȡ���ӽ��
		//************************************
		bool GetConnectResult();
	};
}