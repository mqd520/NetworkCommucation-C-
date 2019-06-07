#pragma once
#include "SocketAPI.h"
#include "TcpService.h"
#include "Def.h"

using namespace std;

namespace tc
{
	//tcp����
	class CTcpConnection
	{
	protected:
		TcpService* m_pTcpSrv;//tcp�������
		SOCKET m_sendrecvSocket;//���ڷ���(����)���ݵ�socket
		BYTE* m_pAsyncSendBuf;//�첽���ͻ�����                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
		int m_nAsyncSendLen;//�첽�������ݳ���
		int m_nAsyncSendStatus;//�첽����״̬
		bool m_bCanAsyncSend;//ָʾ�����߳��Ƿ���Է�������
		NetAddress m_localAddress;//���ص�ַ
		NetAddress m_peerAddress;//�Զ˵�ַ

	protected:
		//************************************
		// Method:    �����ͽ��
		// Parameter: ���ͳɹ����
		//************************************
		virtual void ProcessSendResult(bool success);

	public:
		//************************************
		// Method:    ���캯��
		// Parameter: tcp�������
		// Parameter: ���ڷ���(����)���ݵ�socket
		//************************************
		CTcpConnection(TcpService* pSrv, SOCKET sendrecv);
		~CTcpConnection();

		//************************************
		// Method:    ��ȡ���ڷ���(����)���ݵ�socket
		// Returns:   socket
		//************************************
		SOCKET GetSendRecvSocket();

		//************************************
		// Method:    ��ȡ���ص�ַ
		//************************************
		NetAddress GetLocalAddress();

		//************************************
		// Method:    ��ȡ�Զ˵�ַ
		//************************************
		NetAddress GetPeerAddress();

		//************************************
		// Method:    ��ȡ������tcp�������
		// Returns:   tcp�������
		//************************************
		TcpService* GetTcpService();

		//************************************
		// Method:    �첽��������
		// Parameter: ������ָ��
		// Parameter: �������ֽڳ���
		// Parameter: ʵ�ʷ����ֽڳ���
		//************************************
		void SetAsyncSendData(BYTE* pBuf, int len, int* actualLen = NULL);

		//************************************
		// Method:    ��������
		// Returns:   �Ƿ�ɹ�
		// Parameter: ������ָ��
		// Parameter: �������ֽڳ���
		// Parameter: ʵ�ʷ����ֽڳ���
		//************************************
		bool SendData(BYTE* pBuf, int len, int* actualLen = NULL);

		//************************************
		// Method:    �ر�tcp����
		// Parameter: b:	�Ƿ�������ӶϿ��¼�, Ĭ��: false
		//************************************
		void Close(bool b = false);

		//************************************
		// Method:    �첽����
		//************************************
		void AsyncSendData();

		//************************************
		// Method:    �յ��Զ������¼�����
		//************************************
		virtual void OnRecvPeerData();

		//************************************
		// Method:    ���ӶϿ��¼�����
		//************************************
		virtual void OnConnDisconnect();

		//************************************
		// Method:    ��������¼�����
		//************************************
		virtual void OnNetError();
	};
}