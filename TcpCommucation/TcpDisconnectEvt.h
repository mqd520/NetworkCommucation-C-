#pragma once
#include "TcpEvt.h"

namespace NetworkCommunication
{
	//tcp���ӶϿ��¼�
	class CTcpDisconnectEvt : public CTcpEvt
	{
	public:
		CTcpDisconnectEvt(CTcpService* pSrv, SOCKET sendrecv = NULL);
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