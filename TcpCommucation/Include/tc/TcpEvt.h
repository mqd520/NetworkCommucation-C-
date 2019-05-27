#pragma once
#include "SocketAPI.h"

namespace tc
{
	class CTcpService;

	//tcp�����¼�����
	class TcpEvt
	{
	protected:
		CTcpService* pTcpSrv;	// tcp�������
		SOCKET socket;			// ���������ڷ���(����)���ݵ�socket
		int evt;				// �¼�����

	public:
		//************************************
		// Method:    ���캯��
		// Parameter: ������tcp�������
		// Parameter: ���������ڷ���(����)���ݵ�socket
		//************************************
		TcpEvt(CTcpService* pSrv, SOCKET sendrecv = NULL);
		virtual ~TcpEvt();

		//************************************
		// Method:    ��ȡ�¼�����
		//************************************
		int GetEvtType();

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