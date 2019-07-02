#pragma once
#include "TcpEvt.h"

namespace tc
{
	// ���ӶϿ��¼�
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
		
		//************************************
		// Method:    ��ȡ�Զ�ip
		//************************************
		string GetPeerIp();

		//************************************
		// Method:    ��ȡ�Զ˶˿�
		//************************************
		int GetPeerPort();
	};
}