#pragma once
#include "Thread.h"
#include "Def.h"
#include "SocketAPI.h"
#include "TcpSrvEvt.h"

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
		friend class CTcpServiceMgr;
		//************************************
		// Method:    �յ�tcp�¼�����
		// Parameter: tcp�¼�
		//************************************
		void OnRecvTcpEvent(CTcpSrvEvt* pEvent);

		////************************************
		//// Method:    �յ��µĿͻ��������¼�����
		////************************************
		//virtual void OnRecvNewConnection(CTcpAction* pEvent);

		////************************************
		//// Method:    �յ��Զ������¼�����
		//// Parameter: �Զ�����
		////************************************
		//virtual bool OnRecvPeerData(PeerData* data);

		////************************************
		//// Method:    �Զ������ر������¼�����
		//// Parameter: �Զ�IP
		//// Parameter: �Զ˶˿�
		////************************************
		//virtual void OnPeerCloseConn(TCHAR* ip, int port);

		////************************************
		//// Method:    ���ͶԶ���������¼�����
		//// Parameter: �������ݽ��
		////************************************
		//virtual void OnSendPeerDataCompleted(SendPeerDataResult* result);

		////************************************
		//// Method:    ��������¼�����
		//// Parameter: �Զ�IP
		//// Parameter: �Զ˶˿�
		////************************************
		//virtual void OnNetError(TCHAR* ip, int port);

		////************************************
		//// Method:    �ܾ��¿ͻ��������¼�����
		//// Parameter: �Զ�IP
		//// Parameter: �Զ˶˿�
		////************************************
		//virtual void OnRefuseNewConn(TCHAR* ip, int port);

	public:
		CTcpService(int srvType);
		~CTcpService();

		//************************************
		// Method:    ���д����������߳�
		//************************************
		void Run();

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
		// Method:    ��Զ˷�������(ͬ��)
		// Returns:   �Ƿ�ɹ�
		// Parameter: socket
		// Parameter: ������ָ��
		// Parameter: �������ֽڳ���
		// Parameter: ʵ�ʷ����ֽڳ���
		//************************************
		bool SendData(SOCKET socket, BYTE buf[], int len, int* actualLen = NULL);

		//************************************
		// Method:    ��Զ˷�������(�첽)
		// Returns:   �Ƿ�ɹ�
		// Parameter: socket
		// Parameter: ������ָ��
		// Parameter: �������ֽڳ���
		// Parameter: ʵ�ʷ����ֽڳ���
		//************************************
		virtual void AsyncSendData(SOCKET socket, BYTE buf[], int len, int* actualLen = NULL);

		//************************************
		// Method:    ע��tcp�¼��ص�����
		//************************************
		void RegTcpEventCallback(LPTcpEventCallback lpCallback);
	};
}