#pragma once
#include "Include/tc/SocketTool.h"

namespace tc
{
	class TcpService;

	// tcp�����¼�����
	class TcpEvt
	{
	protected:
		TcpService* pTcpSrv;	// tcp�������
		SOCKET socket;			// ���������ڷ���(����)���ݵ�socket
		int evt;				// �¼�����: ETcpEvt

	public:
		//************************************
		// Method:    ���캯��
		// Parameter: ������tcp�������
		// Parameter: ���������ڷ���(����)���ݵ�socket
		//************************************
		TcpEvt(TcpService* pSrv, SOCKET sendrecv = NULL);
		virtual ~TcpEvt();

		//************************************
		// Method:    ��ȡ�¼�����
		//************************************
		int GetEvtType();

		//************************************
		// Method:    ��ȡtcp�������
		//************************************
		TcpService* GetTcpSrv();

		//************************************
		// Method:    ��ȡ���ڷ���(����)���ݵ�socket
		//************************************
		virtual SOCKET GetSendRecvSocket();
	};
}