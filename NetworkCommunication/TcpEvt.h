#pragma once
#include "SocketAPI.h"

namespace NetworkCommunication
{
	class CTcpService;

	//tcp�����¼�����
	class CTcpEvt
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
		CTcpEvt(CTcpService* pSrv, SOCKET sendrecv = NULL);
		~CTcpEvt();

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