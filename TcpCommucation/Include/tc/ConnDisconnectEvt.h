#pragma once
#include "TcpEvt.h"

namespace tc
{
	// tcp���ӶϿ��¼�
	class ConnDisconnectEvt : public TcpEvt
	{
	public:
		ConnDisconnectEvt(TcpService* pSrv, SOCKET sendrecv = NULL);
		~ConnDisconnectEvt();

	private:
		string strIP;	// �Զ�IP
		int nPort;		// �Զ˶˿�

	public:
		//************************************
		// Method:    ��ȡ�Ͽ�ԭ��
		//************************************
		int GetReason();
		
		string GetPeerIp();

		int GetPeerPort();
	};
}