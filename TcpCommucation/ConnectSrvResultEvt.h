#pragma once
#include "TcpEvt.h"

namespace tc
{
	//���ӷ���˽���¼�
	class CConnectSrvResultEvt : public CTcpEvt
	{
	private:
		bool m_bSuccess;//�����Ƿ�ɹ�

	public:
		CConnectSrvResultEvt(CTcpService* pSrv, bool success);
		~CConnectSrvResultEvt();

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