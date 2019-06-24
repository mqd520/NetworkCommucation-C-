#pragma once
#include "TcpEvt.h"

namespace tc
{
	// ���ӷ���˽���¼�
	class ConnectSrvResultEvt : public TcpEvt
	{
	public:
		//************************************
		// Method:    ���캯��
		// Parameter: tcp ������
		// Parameter: socket
		// Parameter: �����Ƿ�ɹ�
		//************************************
		ConnectSrvResultEvt(TcpService* pSrv, SOCKET socket, bool success);
		~ConnectSrvResultEvt();

	private:
		bool	bSuccess;		// �����Ƿ�ɹ�

	public:
		//************************************
		// Method:    ��ȡ���ӽ��
		//************************************
		bool	GetConnectResult();
	};
}