#pragma once
#include "TcpSrvEvt.h"

namespace NetworkCommunication
{
	//tcp���ӶϿ��¼�
	class CTcpDisconnectEvt : public CTcpSrvEvt
	{
	private:
		int m_nReason;//�Ͽ�ԭ��

	public:
		CTcpDisconnectEvt(int reason, CTcpService* pSrv, SOCKET sendrecv = NULL);
		~CTcpDisconnectEvt();

		//************************************
		// Method:    ��ȡ�¼�����
		//************************************
		int GetEvtType();

		//************************************
		// Method:    ��ȡ�Ͽ�ԭ��
		//************************************
		int GetReason();
	};
}