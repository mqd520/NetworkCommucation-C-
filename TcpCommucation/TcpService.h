#pragma once
#include "Def.h"
#include "Include/tc/Def1.h"
#include "Thread.h"
#include "SocketAPI.h"
#include "Include/tc/TcpEvt.h"
#include "TcpConnection.h"
#include "Include/tc/SocketTool.h"

namespace tc
{
	// tcp�������
	class TcpService
	{
	protected:
		SOCKET socket;			// ������socket
		string strIP;			// socket�����ķ����IP
		int nPort;				// socket�����ķ���˶˿�
		LPTcpEventCallback lpCallback;	// tcp�¼��ص�����ָ��
		void* pParam;					// �¼����Ӳ���

	protected:
		friend class TcpEvtMgr;
		//************************************
		// Method:    �յ�tcp�¼�����
		// Parameter: tcp�¼�
		//************************************
		virtual void OnRecvTcpEvent(TcpEvt* pEvent);

		//************************************
		// Method:    ��Զ˷�������
		// Returns:   �Ƿ�ɹ�
		// Parameter: ������ָ��
		// Parameter: �������ֽڳ���
		// Parameter: �Ƿ��첽,Ĭ���첽����
		// Parameter: ʵ�ʷ����ֽڳ���
		//************************************
		bool SendData(SOCKET socket, BYTE* pBuf, int len, bool asyncs = true, int* actualLen = NULL);

		//************************************
		// Method:    ֪ͨ������tcp�¼�
		// Parameter: tcp�¼�
		//************************************
		void DispatchTcpEvt(TcpEvt* pEvent);

	public:
		TcpService(string ip = "", int port = 0);
		~TcpService();

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
		// Method:    ע��tcp�¼��ص�����
		// Parameter: lpCallback:	�ص�����
		// Parameter: pParam:		���Ӳ���
		//************************************
		void RegTcpEventCallback(LPTcpEventCallback lpCallback, void* param);
	};
}