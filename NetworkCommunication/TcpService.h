#pragma once
#include "Thread.h"
#include "Def.h"
#include "SocketAPI.h"
#include "TcpEvt.h"

namespace NetworkCommunication
{
	///tcp����
	class CTcpService
	{
	protected:
		CSocketAPI m_socketAPI;//socket api
		int m_nSrvType;//��������
		SOCKET m_socket;//socket,�����(�ͻ���)socket
		TCHAR m_strLocalIP[20];//socket�����ı���IP
		int m_nLocalPort;//socket�����ı��ض˿�
		LPTcpEventCallback m_lpCallback;//tcp�¼��ص�����ָ��

	protected:
		friend class CTcpEvtMgr;
		//************************************
		// Method:    �յ�tcp�¼�����
		// Parameter: tcp�¼�
		//************************************
		void OnRecvTcpEvent(CTcpEvt* pEvent);

	public:
		CTcpService(int srvType);
		~CTcpService();

		//************************************
		// Method:    ��ȡtcp��������
		//************************************
		int GetSrvType();

		//************************************
		// Method:    ��ȡsocket
		//************************************
		SOCKET GetSocket();

		//************************************
		// Method:    ��ȡ����IP
		//************************************
		TCHAR* GetLocalIP();

		//************************************
		// Method:    ��ȡ���ض˿�
		//************************************
		int GetLocalPort();

		//************************************
		// Method:    ע��tcp�¼��ص�����
		//************************************
		void RegTcpEventCallback(LPTcpEventCallback lpCallback);
	};
}