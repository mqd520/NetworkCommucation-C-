#pragma once
#include "Def.h"
#include "Include/tc/Def1.h"
#include "Thread.h"
#include "SocketAPI.h"
#include "Include/tc/TcpEvt.h"
#include "TcpConnection.h"

namespace tc
{
	///tcp����
	class CTcpService
	{
	protected:
		CSocketAPI m_socketAPI;			// socket api
		SOCKET m_socket;				// socket,�����(�ͻ���)socket
		TCHAR m_strServerIP[20];		// socket�����ķ����IP
		int m_nServerPort;				// socket�����ķ���˶˿�
		LPTcpEventCallback m_lpCallback;// tcp�¼��ص�����ָ��
		void* pParam;					// �¼����Ӳ���

	protected:
		friend class CTcpEvtMgr;
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
		// Parameter: lpCallback:	�ص�����
		// Parameter: pParam:		���Ӳ���
		//************************************
		void RegTcpEventCallback(LPTcpEventCallback lpCallback, void* param);
	};
}