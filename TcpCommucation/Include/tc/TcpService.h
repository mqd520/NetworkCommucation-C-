#pragma once
#include "Def.h"
#include "Thread.h"
#include "SocketAPI.h"
#include "TcpEvt.h"
#include "RecvNewConnEvt.h"
#include "ConnDisconnectEvt.h"
#include "RecvPeerDataEvt.h"
#include "ConnectSrvCplEvt.h"

namespace tc
{
	// tcp����������
	class TcpService
	{
	public:
		TcpService(string ip = "", int port = 0);
		virtual ~TcpService();

	protected:
		SOCKET socket;				// ������socket
		string strIP;				// socket�����ķ����IP
		int nPort;					// socket�����ķ���˶˿�
		Fun2 fun;					// tcp�¼��ص�����ָ��
		void* pParam1;				// �¼����Ӳ���1
		void* pParam2;				// �¼����Ӳ���2
		ETcpSrvType tcpSrvType;		// tcp srv type

	protected:
		friend class TcpEvtMgr;

		//************************************
		// Method:    tcp�¼�����
		// Parameter: pEvt: tcp�¼�
		//************************************
		virtual void OnTcpEvt(TcpEvt* pEvt);

		//************************************
		// Method:    �յ��������¼�����
		// Parameter: pEvt: tcp�¼�
		//************************************
		virtual void OnRecvNewConnection(RecvNewConnEvt* pEvt);

		//************************************
		// Method:    ���ӶϿ��¼�����
		// Parameter: pEvt: tcp�¼�
		//************************************
		virtual void OnConnDisconnect(ConnDisconnectEvt* pEvt);

		//************************************
		// Method:    �յ��Զ������¼�����
		// Parameter: pEvt: tcp�¼�
		//************************************
		virtual void OnRecvPeerData(RecvPeerDataEvt* pEvt);

		//************************************
		// Method:    ���ӷ��������¼�����
		// Parameter: pEvt: tcp�¼�
		//************************************
		virtual void OnConnectSrvCpl(ConnectSrvCplEvt* pEvt);

		//************************************
		// Method:    ��Զ˷�������
		// Parameter: ������ָ��
		// Parameter: �������ֽڳ���
		//************************************
		virtual void SendData(SOCKET socket, BYTE* pBuf, int len);

		//************************************
		// Method:    ֪ͨ������tcp�¼�
		// Parameter: tcp�¼�
		//************************************
		virtual void DispatchTcpEvt(TcpEvt* pEvt);

	public:
		//************************************
		// Method:    ��ȡtcp srv type
		//************************************
		ETcpSrvType GetTcpSrvType();

		//************************************
		// Method:    ��ȡ������socket
		//************************************
		SOCKET GetSocket();

		//************************************
		// Method:    ��ȡ�����ķ����IP
		//************************************
		string GetIP();

		//************************************
		// Method:    ��ȡ�����ķ���˶˿�
		//************************************
		int GetPort();

		//************************************
		// Method:    �˳�
		//************************************
		virtual void Exit();

		//************************************
		// Method:    ע��tcp�¼��ص�����
		// Parameter: lpCallback:	�ص�����
		// Parameter: pParam1:		���Ӳ���1
		// Parameter: pParam1:		���Ӳ���2
		//************************************
		virtual void RegTcpEventCallback(Fun2 fun, void* pParam1 = NULL, void* pParam2 = NULL);
	};
}