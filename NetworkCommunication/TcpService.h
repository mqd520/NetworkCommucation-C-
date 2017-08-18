#pragma once
#include "Thread.h"
#include "Def.h"
#include "SocketAPI.h"

namespace NetworkCommunication
{
	///tcp����
	class CTcpService
	{
	protected:
		CSocketAPI m_socketAPI;
		int m_nSrvType;//��������
		SOCKET m_localSocket;//����socket
		char m_strLocalIP[20];//����socket����IP
		int m_nLocalPort;//����socket�����Ķ˿�

	private:
		void OnRecvNewConnection();

	public:
		~CTcpService();
		CTcpService(int srvType);

		// ��ȡtcp��������
		int GetSrvType();

		//************************************
		// Method:    ��ȡ�����socket����
		//************************************
		virtual ServerSocket GetServerSocketData();

		//************************************
		// Method:    ��ȡ����socket
		//************************************
		SOCKET GetLocalSocket();

		//************************************
		// Method:    ���յ��µĿͻ��������¼�����
		// Parameter: �����socket	
		// Parameter: �Զ�socket����
		//************************************
		virtual void OnRecvNewConnection(ServerSocket server, ServerClientSocket client);

		//************************************
		// Method:    �Զ������ر��¼�����
		// Parameter: �����socket	
		// Parameter: �Զ�socket����
		//************************************
		virtual void OnPeerCloseSocket(ServerClientSocket data);

		virtual bool OnRecvPeerData(PeerData* data);

		//************************************
		// Method:    ���ͶԶ���������¼�����
		// Parameter: ���ͽ��
		//************************************
		virtual void OnSendPeerDataCompleted(SendPeerDataResult result);

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
		void AsyncSendData(SOCKET client, BYTE buf[], int len, int* actualLen = NULL);
	};
}