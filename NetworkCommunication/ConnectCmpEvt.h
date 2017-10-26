#pragma once
#include "TcpEvt.h"

namespace NetworkCommunication
{
	//��������¼�
	class CConnectCmpEvt : public CTcpEvt
	{
	private:
		bool m_bSuccess;//�����Ƿ�ɹ�

	public:
		CConnectCmpEvt(CTcpService* pSrv, bool success);
		~CConnectCmpEvt();

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