#pragma once
#include "Include/tc/SocketTool.h"
#include "Def1.h"

namespace tc
{
	class TcpService;

	// tcp�����¼�����
	class TcpEvt
	{
	protected:
		TcpService* pTcpSrv;	// tcp�������
		SOCKET socket;			// ���������ڷ���(����)���ݵ�socket
		ETcpEvtType evtType;		// �¼�����
		int socketId;			// socket id

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
		ETcpEvtType GetEvtType();

		//************************************
		// Method:    ��ȡtcp�������
		//************************************
		TcpService* GetTcpSrv();

		//************************************
		// Method:    ��ȡ���ڷ���(����)���ݵ�socket id
		//************************************
		virtual int GetSendRecvSocketId();
	};
}