#pragma once
#include "TcpEvt.h"

namespace tc
{
	// tcp���ӶϿ��¼�
	class ConnDisconnectEvt : public TcpEvt
	{
	public:
		ConnDisconnectEvt(CTcpService* pSrv, SOCKET sendrecv = NULL);
		~ConnDisconnectEvt();

		//************************************
		// Method:    ��ȡ�Ͽ�ԭ��
		//************************************
		int GetReason();
	};
}