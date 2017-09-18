#pragma once
#include "SocketAPI.h"

namespace NetworkCommunication
{
	class CTcpService;

	//tcp�����¼�����
	class CTcpSrvEvt
	{
	protected:
		CTcpService* m_pTcpSrv;//tcp�������
		SOCKET m_socket;//���������ڷ���(����)���ݵ�socket

	public:
		//************************************
		// Method:    ���캯��
		// Parameter: ������tcp�������
		// Parameter: ���������ڷ���(����)���ݵ�socket
		//************************************
		CTcpSrvEvt(CTcpService* pSrv, SOCKET sendrecv = NULL);
		~CTcpSrvEvt();

		//************************************
		// Method:    ��ȡ�¼�����
		//************************************
		virtual int GetEvtType();

		//************************************
		// Method:    ��ȡtcp�������
		//************************************
		CTcpService* GetTcpSrv();

		//************************************
		// Method:    ��ȡ���ڷ���(����)���ݵ�socket
		//************************************
		virtual SOCKET GetSendRecvSocket();
	};
}