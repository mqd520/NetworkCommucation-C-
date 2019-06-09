#pragma once
#include "Include/tc/SocketTool.h"
#include "Include/tc/Def1.h"

namespace tc
{
	class TcpService;

	// tcp�����¼�����
	class TcpEvt
	{
	protected:
		TcpService* pTcpSrv;	// tcp�������
		SOCKET socket;			// ���������ڷ���(����)���ݵ�socket
		ETcpEvt evt;			// �¼�����

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
		ETcpEvt GetEvtType();

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