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
		SOCKET m_socket;//socket,�����(�ͻ���)socket
		TCHAR m_strServerIP[20];//socket�����ķ����IP
		int m_nServerPort;//socket�����ķ���˶˿�
		LPTcpEventCallback m_lpCallback;//tcp�¼��ص�����ָ��

	protected:
		friend class CTcpEvtMgr;
		//************************************
		// Method:    �յ�tcp�¼�����
		// Parameter: tcp�¼�
		//************************************
		virtual void OnRecvTcpEvent(CTcpEvt* pEvent);

		//************************************
		// Method:    ��Զ˷�������
		// Returns:   �Ƿ�ɹ�
		// Parameter: socket
		// Parameter: ������ָ��
		// Parameter: �������ֽڳ���
		// Parameter: �Ƿ��첽,Ĭ���첽����
		// Parameter: ʵ�ʷ����ֽڳ���
		//************************************
		bool SendData(SOCKET socket, BYTE* pBuf, int len, bool asyncs = true, int* actualLen = NULL);

	public:
		CTcpService();
		~CTcpService();

		//************************************
		// Method:    ��ȡ���������socket
		//************************************
		SOCKET GetSocket();

		//************************************
		// Method:    ��ȡ�����IP
		//************************************
		TCHAR* GetServerIP();

		//************************************
		// Method:    ��ȡ����˶˿�
		//************************************
		int GetServerPort();

		//************************************
		// Method:    ע��tcp�¼��ص�����
		//************************************
		void RegTcpEventCallback(LPTcpEventCallback lpCallback);
	};
}